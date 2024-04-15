use crate::context::Context;
use crate::diagnostic::{self, Diagnostic};
use crate::symbol_manager::Symbol;
use crate::type_manager::LangType;
use crate::types::TypeDetail;
use crate::utils::collect_kind;
use itertools::Itertools;
use std::cell::RefCell;
use std::{
    collections::HashMap,
    ops::{Deref, DerefMut},
    rc::Rc,
};
use tree_sitter::TreeCursor;

pub fn type_node(cursor: &TreeCursor, ctx: Rc<RefCell<Context>>) {
    let mut ctx = ctx.borrow_mut();
    let Context {
        source_bytes,
        symbol_manager,
        type_manager,
        diagnostics,
        source: _,
        collect_types,
    } = ctx.deref_mut();

    let node = cursor.node();
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
                match symbol_manager.resolve_symbol(node, child.utf8_text(&source_bytes).unwrap()) {
                    Some(Symbol::Type(lang_type)) => lang_type.into(),
                    Some(Symbol::Variable(lang_type)) => match lang_type.deref().clone() {
                        LangType::Set(_) | LangType::List(_) => {
                            Rc::new(LangType::Variable(lang_type)).into()
                        }
                        _ => lang_type.into(),
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
                    match child.utf8_text(&source_bytes).unwrap() {
                        "nat" => Rc::new(LangType::Nat).into(),
                        "nat0" => Rc::new(LangType::Nat0).into(),
                        _ => unknown.into(),
                    }
                })
            })
            .unwrap_or_default()
            .into(),
        "enumeration_type" => Rc::new(LangType::Enumeration(
            collect_kind(&mut node.walk(), "identifier")
                .iter()
                .map(|n| n.utf8_text(&source_bytes).unwrap().into())
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
                        .get(0)
                        .unwrap()
                        .utf8_text(&source_bytes)
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
        "type_definition_item" => {
            if let (Some(identifier), Some(lang_type)) = (node.child(0), node.child(2)) {
                let name: String = { identifier.utf8_text(&source_bytes).unwrap().into() };
                let lang_type = type_manager.node_type(lang_type.id()).unwrap_or_default();
                collect_types.push(TypeDetail {
                    range: identifier.range().into(),
                    source: identifier.utf8_text(&source_bytes).unwrap().to_string(),
                    type_str: lang_type.to_string(),
                    type_expanded: lang_type.expanded_type(),
                });
                symbol_manager.add_symbol(
                    &node.parent().unwrap().parent().unwrap(),
                    &name,
                    Symbol::Type(LangType::Alias(name.clone(), lang_type).into()),
                );
            }
            None
        }
        "variable_definition_item" => {
            if let (Some(identifier), Some(lang_type)) = (node.child(0), node.child(2)) {
                let name: String = { identifier.utf8_text(&source_bytes).unwrap().into() };
                let lang_type = type_manager.node_type(lang_type.id()).unwrap_or_default();
                collect_types.push(TypeDetail {
                    range: identifier.range().into(),
                    source: identifier.utf8_text(&source_bytes).unwrap().to_string(),
                    type_str: lang_type.to_string(),
                    type_expanded: lang_type.expanded_type(),
                });
                symbol_manager.add_symbol(
                    &node.parent().unwrap().parent().unwrap(),
                    &name,
                    Symbol::Variable(lang_type),
                );
            }
            None
        }
        "parameter_item" => {
            let mut nodes = node.named_children(&mut node.walk()).collect::<Vec<_>>();
            let lang_type = nodes
                .pop()
                .map(|n| type_manager.node_type(n.id()).unwrap_or_default());
            if let Some(lang_type) = lang_type {
                let lang_type = lang_type.variable_type();
                nodes.iter().for_each(|n| {
                    let name: String = n.utf8_text(&source_bytes).unwrap().into();
                    collect_types.push(TypeDetail {
                        range: n.range().into(),
                        source: n.utf8_text(&source_bytes).unwrap().to_string(),
                        type_str: lang_type.to_string(),
                        type_expanded: lang_type.expanded_type(),
                    });
                    symbol_manager.add_symbol(
                        &node.parent().unwrap().parent().unwrap(),
                        &name,
                        Symbol::Variable(lang_type.clone()),
                    );
                });
            }
            None
        }
        "ext_item" => {
            if let (Some(name_node), Some(lang_type)) = (node.child(1), node.child(3)) {
                let name: String = name_node.utf8_text(&source_bytes).unwrap().into();
                let lang_type = type_manager.node_type(lang_type.id()).unwrap_or_default();
                collect_types.push(TypeDetail {
                    range: name_node.range().into(),
                    source: name_node.utf8_text(&source_bytes).unwrap().to_string(),
                    type_str: lang_type.to_string(),
                    type_expanded: lang_type.expanded_type(),
                });
                symbol_manager.add_symbol(
                    &node.parent().unwrap().parent().unwrap(),
                    &name,
                    Symbol::Variable(lang_type),
                );
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
        "list_expression" => Rc::new(
            if let Some(Some(Some(result))) = node.child_by_field_name("items").map(|items| {
                items
                    .child(0)
                    .map(|first| type_manager.node_type(first.id()))
            }) {
                LangType::List(result)
            } else {
                LangType::List(unknown)
            },
        )
        .into(),
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
                {
                    diagnostics.push(Diagnostic {
                        level: diagnostic::Level::Warning,
                        range: node.range().into(),
                        message: format!(
                            "操作符 {} 的左类型 {} 和右类型 {} 不匹配",
                            operator.kind(),
                            left_type.to_string(),
                            right_type.to_string(),
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
                let name = child.utf8_text(&source_bytes).unwrap();
                if let Some(Symbol::Variable(lang_type)) = symbol_manager.resolve_symbol(node, name)
                {
                    lang_type.into()
                } else {
                    unknown.into()
                }
            } else if let (Some(refer), Some(id)) = (node.child(0), node.child(2)) {
                let left_type = type_manager.node_type(refer.id()).unwrap_or_default();
                if let LangType::Composite(fields) = left_type.skip_alias().deref() {
                    let name: String = id.utf8_text(&source_bytes).unwrap().into();
                    let field_type = fields.get(&name);
                    if field_type.is_none() {
                        diagnostics.push(Diagnostic {
                            range: node.range().into(),
                            level: diagnostic::Level::Warning,
                            message: format!("类型 {} 没有成员 {}", left_type.to_string(), name),
                        });
                    }
                    let field_type = field_type.cloned().unwrap_or_default();
                    collect_types.push(TypeDetail {
                        range: id.range().into(),
                        source: id.utf8_text(&source_bytes).unwrap().to_string(),
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
                let str_name = fn_name.utf8_text(&source_bytes).unwrap();
                let args = if expr_list.is_some_and(|n| n.kind() == "expression_list") {
                    let expr_list = expr_list.unwrap();
                    expr_list
                        .named_children(&mut expr_list.walk())
                        .collect::<Vec<_>>()
                } else {
                    vec![]
                };
                let first_type = args
                    .get(0)
                    .map(|node| type_manager.node_type(node.id()).unwrap_or_default());
                match str_name {
                    "abs" | "bound" | "floor" | "power" => {
                        args.iter().for_each(|arg| {
                            let arg_type = type_manager.node_type(arg.id());
                            if arg_type.is_none() || !arg_type.unwrap().skip_alias().is_numeric() {
                                diagnostics.push(Diagnostic {
                                    level: diagnostic::Level::Warning,
                                    range: arg.range().into(),
                                    message: "参数类型错误".to_string(),
                                });
                            }
                        });
                        first_type
                    }
                    "union" | "inter" | "diff" | "dunion" | "dinter" => first_type,
                    "len" => Rc::new(LangType::Nat).into(),
                    _ => {
                        let fn_type = type_manager.node_type(fn_name.id());
                        if let Some(fn_type) = fn_type {
                            if let LangType::Map(_, value) = fn_type.skip_alias().deref() {
                                value.clone().into()
                            } else {
                                diagnostics.push(Diagnostic {
                                    level: diagnostic::Level::Warning,
                                    range: fn_name.range().into(),
                                    message: "函数类型错误".to_string(),
                                });
                                unknown.into()
                            }
                        } else {
                            diagnostics.push(Diagnostic {
                                level: diagnostic::Level::Warning,
                                range: node.range().into(),
                                message: "未找到函数定义".to_string(),
                            });
                            unknown.into()
                        }
                    }
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
        type_manager.set_node_type(node.id(), lang_type.clone().into());
        collect_types.push(TypeDetail {
            range: node.range().into(),
            source: node.utf8_text(&source_bytes).unwrap().to_string(),
            type_str: lang_type.to_string(),
            type_expanded: lang_type.expanded_type(),
        });
    }
}
