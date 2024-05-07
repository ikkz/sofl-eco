use crate::context::diagnostic::{self, Diagnostic};
use crate::context::symbol_manager::Symbol;
use crate::context::Context;
use crate::lang_type::{self, LangType};
use crate::types::TypeDetail;
use crate::utils::collect_kind;
use itertools::Itertools;
use std::cell::RefCell;
use std::{
    collections::HashMap,
    ops::{Deref, DerefMut},
    rc::Rc,
};
use tree_sitter::Node;
use tree_sitter::TreeCursor;

pub fn traverse(cursor: &mut TreeCursor, ctx: Rc<RefCell<Context>>) {
    let node = cursor.node();
    match node.kind() {
        "set_def_expression" => {
            ["binding", "exp", "cond"].iter().for_each(|field| {
                node.child_by_field_name(field).and_then(|field| {
                    traverse(&mut field.walk(), ctx.clone());
                    ().into()
                });
            });
            type_node(node, ctx.clone());
        }
        _ => {
            if cursor.goto_first_child() {
                traverse(cursor, ctx.clone());
                while cursor.goto_next_sibling() {
                    traverse(cursor, ctx.clone());
                }
                cursor.goto_parent();
            }
            type_node(cursor.node(), ctx.clone());
        }
    }
}
pub fn type_node(node: Node, ctx: Rc<RefCell<Context>>) {
    let mut ctx = ctx.borrow_mut();
    let Context {
        source_bytes,
        symbol_manager,
        type_manager,
        diagnostics,
        source: _,
        collect_types,
    } = ctx.deref_mut();

    if node.is_error() {
        diagnostics.push(Diagnostic {
            level: diagnostic::Level::Error,
            range: node.range().into(),
            message: "语法错误".to_string(),
        });
        return;
    }

    let unknown = Rc::new(LangType::Unknown);
    let node_type: Option<Rc<LangType>> = match node.kind() {
        "type_identifier" => {
            if let Some(child) = node.child(0) {
                match symbol_manager.resolve_symbol(node, child.utf8_text(source_bytes).unwrap()) {
                    Some(Symbol::Type(lang_type)) => lang_type.clone().into(),
                    Some(Symbol::Variable(lang_type)) => match lang_type.deref().clone() {
                        LangType::Set(_) | LangType::List(_) => {
                            Rc::new(LangType::Variable(lang_type.clone())).into()
                        }
                        _ => lang_type.clone().into(),
                    },
                    _ => unknown.into(),
                }
            } else {
                unknown.into()
            }
        }
        // types
        "int" => Rc::new(LangType::Int).into(),
        "real" => Rc::new(LangType::Real).into(),
        "string" => Rc::new(LangType::String).into(),
        "char" => Rc::new(LangType::Char).into(),
        "bool" => Rc::new(LangType::Bool).into(),
        "primitive_type" => node
            .child(0)
            .map(|child| {
                type_manager.node_type(child.id()).unwrap_or_else(|| {
                    match child.utf8_text(source_bytes).unwrap() {
                        "nat" => Rc::new(LangType::Nat),
                        "nat0" => Rc::new(LangType::Nat0),
                        _ => unknown,
                    }
                })
            })
            .unwrap_or_default()
            .into(),
        "enumeration_type" => Rc::new(LangType::Enumeration(
            collect_kind(&mut node.walk(), "identifier")
                .iter()
                .map(|n| n.utf8_text(source_bytes).unwrap().into())
                .collect::<Vec<_>>()
                .into(),
        ))
        .into(),
        "set_type" => Rc::new(LangType::Set(if let Some(child) = node.child(2) {
            type_manager.node_type(child.id()).unwrap_or_default()
        } else {
            unknown
        }))
        .into(),
        "list_type" => Rc::new(LangType::List(if let Some(child) = node.child(2) {
            type_manager.node_type(child.id()).unwrap_or_default()
        } else {
            unknown
        }))
        .into(),
        "map_type" => Rc::new(
            if let (Some(key), Some(value)) = (node.child(1), node.child(3)) {
                LangType::Map(
                    type_manager.node_type(key.id()).unwrap_or_default(),
                    type_manager.node_type(value.id()).unwrap_or_default(),
                )
            } else {
                LangType::Map(unknown.clone(), unknown)
            },
        )
        .into(),
        "composite_type" => Rc::new(LangType::Composite(
            node.named_children(&mut node.walk())
                .chunks(2)
                .into_iter()
                .map(|iter| {
                    let pair = iter.collect::<Vec<_>>();
                    let name = pair
                        .first()
                        .unwrap()
                        .utf8_text(source_bytes)
                        .unwrap()
                        .into();
                    let lang_type = pair
                        .get(1)
                        .map(|node| type_manager.node_type(node.id()).unwrap_or_default())
                        .unwrap_or_default();
                    (name, lang_type)
                })
                .collect::<HashMap<_, _>>()
                .into(),
        ))
        .into(),
        "function_definition_item" => {
            let mut cursor = node.walk();
            let arguments = node
                .children_by_field_name("parameter", &mut cursor)
                .map(|node| type_manager.node_type(node.id()).unwrap_or_default())
                .collect::<Vec<_>>();
            let return_type = node
                .child_by_field_name("return_type")
                .map(|node| type_manager.node_type(node.id()).unwrap_or_default())
                .unwrap_or_default();
            if let Some(name) = node
                .child_by_field_name("function_name")
                .map(|node| node.utf8_text(source_bytes).unwrap().to_string())
            {
                if let Some(Some(parent)) = node.parent().map(|p| p.parent()) {
                    symbol_manager.add_symbol(
                        &parent,
                        &name,
                        Symbol::Function(Rc::new(LangType::Function(
                            lang_type::function::FunctionType {
                                arguments,
                                return_type,
                                generics: symbol_manager.node_symbols(&node).map_or_else(
                                    std::vec::Vec::new,
                                    |table| {
                                        table
                                            .values()
                                            .filter_map(|symbol| {
                                                if let Symbol::Type(t) = symbol {
                                                    if matches!(t.deref(), LangType::Generic(_)) {
                                                        Some(t.clone())
                                                    } else {
                                                        None
                                                    }
                                                } else {
                                                    None
                                                }
                                            })
                                            .collect_vec()
                                    },
                                ),
                            },
                        ))),
                    )
                }
            }
            None
        }
        "type_definition_item" => {
            if let (Some(identifier), Some(lang_type)) = (node.child(0), node.child(2)) {
                let name: String = { identifier.utf8_text(source_bytes).unwrap().into() };
                let lang_type = type_manager.node_type(lang_type.id()).unwrap_or_default();
                collect_types.push(TypeDetail {
                    range: identifier.range().into(),
                    source: identifier.utf8_text(source_bytes).unwrap().to_string(),
                    type_str: lang_type.to_string(),
                    type_expanded: lang_type.expanded_type(),
                });
                if let Some(Some(parent)) = node.parent().map(|p| p.parent()) {
                    symbol_manager.add_symbol(
                        &parent,
                        &name,
                        Symbol::Type(LangType::Alias(name.clone(), lang_type).into()),
                    );
                }
            }
            None
        }
        "variable_definition_item" => {
            if let (Some(identifier), Some(lang_type)) = (node.child(0), node.child(2)) {
                let name: String = { identifier.utf8_text(source_bytes).unwrap().into() };
                let lang_type = type_manager.node_type(lang_type.id()).unwrap_or_default();
                collect_types.push(TypeDetail {
                    range: identifier.range().into(),
                    source: identifier.utf8_text(source_bytes).unwrap().to_string(),
                    type_str: lang_type.to_string(),
                    type_expanded: lang_type.expanded_type(),
                });
                if let Some(Some(parent)) = node.parent().map(|p| p.parent()) {
                    symbol_manager.add_symbol(&parent, &name, Symbol::Variable(lang_type));
                }
            }
            None
        }
        "generic_types" => {
            let parent = node.parent().unwrap();
            for id in collect_kind(&mut node.walk(), "identifier") {
                let generic_name = id.utf8_text(source_bytes).unwrap();
                let generic_type = LangType::Generic(generic_name.into());
                symbol_manager.add_symbol(&parent, generic_name, Symbol::Type(generic_type.into()));
            }
            None
        }
        "parameter_item" => {
            if let Some(Some(parent)) = node.parent().map(|p| p.parent()) {
                let mut nodes = node.named_children(&mut node.walk()).collect::<Vec<_>>();
                let lang_type = nodes
                    .pop()
                    .map(|n| type_manager.node_type(n.id()).unwrap_or_default());
                if let Some(lang_type) = lang_type {
                    let lang_type = lang_type.variable_type();
                    nodes.iter().for_each(|n| {
                        let name: String = n.utf8_text(source_bytes).unwrap().into();
                        collect_types.push(TypeDetail {
                            range: n.range().into(),
                            source: n.utf8_text(source_bytes).unwrap().to_string(),
                            type_str: lang_type.to_string(),
                            type_expanded: lang_type.expanded_type(),
                        });
                        symbol_manager.add_symbol(
                            &parent,
                            &name,
                            Symbol::Variable(lang_type.clone()),
                        );
                    });
                }
            }
            None
        }
        "ext_item" => {
            if let (Some(name_node), Some(lang_type)) = (node.child(1), node.child(3)) {
                let name: String = name_node.utf8_text(source_bytes).unwrap().into();
                let lang_type = type_manager.node_type(lang_type.id()).unwrap_or_default();
                collect_types.push(TypeDetail {
                    range: name_node.range().into(),
                    source: name_node.utf8_text(source_bytes).unwrap().to_string(),
                    type_str: lang_type.to_string(),
                    type_expanded: lang_type.expanded_type(),
                });
                if let Some(Some(parent)) = node.parent().map(|p| p.parent()) {
                    symbol_manager.add_symbol(&parent, &name, Symbol::Variable(lang_type));
                }
            } else {
                diagnostics.push(Diagnostic {
                    level: diagnostic::Level::Error,
                    range: node.range().into(),
                    message: "项目定义粗欧文".to_string(),
                });
            }
            None
        }
        // expressions
        "set_const_expression" => Rc::new(
            if let Some(Some(Some(result))) = node.child_by_field_name("items").map(|items| {
                items
                    .child(0)
                    .map(|first| type_manager.node_type(first.id()))
            }) {
                LangType::Set(result)
            } else {
                LangType::Set(unknown)
            },
        )
        .into(),
        "set_def_expression" => {
            let expr = node.child_by_field_name("exp");
            if let Some(expr) = expr {
                Rc::new(LangType::Set(
                    type_manager.node_type(expr.id()).unwrap_or_default(),
                ))
                .into()
            } else {
                diagnostics.push(Diagnostic {
                    level: diagnostic::Level::Error,
                    range: node.range().into(),
                    message: "集合定义错误".to_string(),
                });
                unknown.into()
            }
        }
        "map_item" => {
            let key = node.child_by_field_name("key");
            let value = node.child_by_field_name("value");

            if let (Some(key), Some(value)) = (key, value) {
                let key_type = type_manager.node_type(key.id());
                let value_type = type_manager.node_type(value.id());
                Rc::new(LangType::MapItem(
                    key_type.unwrap_or_default(),
                    value_type.unwrap_or_default(),
                ))
                .into()
            } else {
                unknown.into()
            }
        }
        "map_expression" => {
            let unknown: Option<Rc<LangType>> =
                Rc::new(LangType::MapItem(unknown.clone(), unknown)).into();
            if let Some(first) = node.child(1) {
                match first.kind() {
                    "map_item" => {
                        if let LangType::MapItem(key, value) = type_manager
                            .node_type(first.id())
                            .unwrap_or_default()
                            .deref()
                        {
                            Rc::new(LangType::Map(key.clone(), value.clone())).into()
                        } else {
                            unknown
                        }
                    }
                    _ => unknown,
                }
            } else {
                unknown
            }
        }
        "unary_expression" => {
            if let (Some(operator), Some(operand)) = (node.child(0), node.child(1)) {
                match operator.kind() {
                    "-" | "not" | "~" => type_manager
                        .node_type(operand.id())
                        .unwrap_or_default()
                        .into(),
                    _ => unknown.into(),
                }
            } else {
                unknown.into()
            }
        }
        "binary_expression" => {
            if let (Some(left), Some(operator), Some(right)) = (
                node.child_by_field_name("left"),
                node.child_by_field_name("operator"),
                node.child_by_field_name("right"),
            ) {
                let left_type = type_manager.node_type(left.id()).unwrap_or_default();
                let right_type = type_manager.node_type(right.id()).unwrap_or_default();
                if left_type.skip_alias().deref() != right_type.skip_alias().deref()
                    && !["inset", "notinset"].contains(&operator.kind())
                    && !(left_type.is_numeric() && right_type.is_numeric())
                {
                    diagnostics.push(Diagnostic {
                        level: diagnostic::Level::Warning,
                        range: node.range().into(),
                        message: format!(
                            "操作符 {} 的左类型 {} 和右类型 {} 不匹配",
                            operator.kind(),
                            left_type,
                            right_type,
                        ),
                    })
                }
                match operator.kind() {
                    "+" | "-" | "*" | "/" | "div" | "rem" | "mod" => left_type.into(),
                    "or" | "=>" | "<=>" | "=" | "<>" | "<" | "<=" | ">" | ">=" | "inset"
                    | "notinset" | "and" => Rc::new(LangType::Bool).into(),
                    _ => unknown.into(),
                }
            } else {
                unknown.into()
            }
        }
        "reference_expression" => {
            if node.child_count() == 1 {
                let child = node.child(0).unwrap();
                let name = child.utf8_text(source_bytes).unwrap();
                match symbol_manager.resolve_symbol(node, name) {
                    Some(Symbol::Variable(lang_type)) | Some(Symbol::Function(lang_type)) => {
                        lang_type.clone().into()
                    }
                    _ => unknown.into(),
                }
            } else if let (Some(refer), Some(id)) = (node.child(0), node.child(2)) {
                let left_type = type_manager.node_type(refer.id()).unwrap_or_default();
                if let LangType::Composite(fields) = left_type.skip_alias().deref() {
                    let name: String = id.utf8_text(source_bytes).unwrap().into();
                    let field_type = fields.get(&name);
                    if field_type.is_none() {
                        diagnostics.push(Diagnostic {
                            range: node.range().into(),
                            level: diagnostic::Level::Warning,
                            message: format!("类型 {} 没有成员 {}", left_type, name),
                        });
                    }
                    let field_type = field_type.cloned().unwrap_or_default();
                    collect_types.push(TypeDetail {
                        range: id.range().into(),
                        source: id.utf8_text(source_bytes).unwrap().to_string(),
                        type_str: field_type.to_string(),
                        type_expanded: field_type.expanded_type(),
                    });
                    field_type.into()
                } else {
                    unknown.into()
                }
            } else {
                unknown.into()
            }
        }
        "modify_expression" => {
            if let Some(refer) = node.child(2) {
                type_manager
                    .node_type(refer.id())
                    .unwrap_or_default()
                    .into()
            } else {
                unknown.into()
            }
        }
        "quantified_expression" => Rc::new(LangType::Bool).into(),
        "function_expression" => {
            let fn_name = node.child(0);
            let expr_list = node.child(2);
            if let Some(fn_name) = fn_name {
                let str_name = fn_name.utf8_text(source_bytes).unwrap();
                let args = if expr_list.is_some_and(|n| n.kind() == "expression_list") {
                    let expr_list = expr_list.unwrap();
                    expr_list
                        .named_children(&mut expr_list.walk())
                        .map(|node| type_manager.node_type(node.id()).unwrap_or_default())
                        .collect::<Vec<_>>()
                } else {
                    vec![]
                };

                if let Some(fn_type) = type_manager.node_type(fn_name.id()) {
                    match fn_type.skip_alias().deref() {
                        LangType::Map(_, value) => value.clone().into(),
                        LangType::Function(func) => {
                            if func.arguments.len() != args.len() {
                                diagnostics.push(Diagnostic {
                                    level: diagnostic::Level::Error,
                                    range: node.range().into(),
                                    message: format!(
                                        "函数 {} 参数数量不匹配，期望 {} 个，实际 {} 个",
                                        str_name,
                                        func.arguments.len(),
                                        args.len()
                                    ),
                                });
                            }
                            func.infer_return_type(args).into()
                        }
                        _ => unknown.into(),
                    }
                } else {
                    diagnostics.push(Diagnostic {
                        level: diagnostic::Level::Error,
                        range: node.range().into(),
                        message: format!("未找到函数 {}", str_name),
                    });
                    None
                }
            } else {
                diagnostics.push(Diagnostic {
                    level: diagnostic::Level::Error,
                    range: node.range().into(),
                    message: "错误的函数表达式".to_string(),
                });
                unknown.into()
            }
        }
        "bracketed_expression" => {
            if let Some(child) = node.child(1) {
                type_manager
                    .node_type(child.id())
                    .unwrap_or_default()
                    .into()
            } else {
                unknown.into()
            }
        }

        _ => None,
    };
    if let Some(lang_type) = node_type {
        type_manager.set_node_type(node.id(), lang_type.clone());
        collect_types.push(TypeDetail {
            range: node.range().into(),
            source: node.utf8_text(source_bytes).unwrap().to_string(),
            type_str: lang_type.to_string(),
            type_expanded: lang_type.expanded_type(),
        });
    }
}
