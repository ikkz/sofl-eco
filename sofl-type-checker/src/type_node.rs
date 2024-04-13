use crate::context::Context;
use crate::diagnostic::Diagnostic;
use crate::symbol_manager::Symbol;
use crate::type_manager::LangType;
use crate::utils::collect_kind;
use crate::{diagnostic, utils::collect_when};
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
    } = ctx.deref_mut();

    let node = cursor.node();
    if node.is_error() {
        diagnostics.push(Diagnostic {
            level: diagnostic::Level::Error,
            range: node.range(),
            message: "Syntax error".to_string(),
        });
        return;
    }

    let node_type: Option<LangType> = match node.kind() {
        "type_identifier" => {
            if let Some(child) = node.child(0) {
                match symbol_manager.resolve_symbol(node, child.utf8_text(&source_bytes).unwrap()) {
                    Some(Symbol::Type(lang_type)) => lang_type.deref().clone().into(),
                    Some(Symbol::Variable(lang_type)) => {
                        let lang_type = lang_type.skip_alias().deref().clone();
                        match lang_type {
                            LangType::Set(inner) | LangType::List(inner) => {
                                inner.deref().clone().into()
                            }
                            _ => lang_type.into(),
                        }
                    }
                    _ => LangType::Unknown.into(),
                }
            } else {
                LangType::Unknown.into()
            }
        }
        // types
        "int" => LangType::Int.into(),
        "real" => LangType::Real.into(),
        "string" => LangType::String.into(),
        "char" => LangType::Char.into(),
        "bool" => LangType::Bool.into(),
        "primitive_type" => node
            .child(0)
            .map(|child| {
                type_manager
                    .node_type(child.id())
                    .unwrap_or_else(|| match child.utf8_text(&source_bytes).unwrap() {
                        "nat" => LangType::Nat.into(),
                        "nat0" => LangType::Nat0.into(),
                        _ => LangType::Unknown.into(),
                    })
                    .deref()
                    .clone()
            })
            .unwrap_or_default()
            .into(),
        "enumeration_type" => LangType::Enumeration(
            collect_kind(&mut node.walk(), "identifier")
                .iter()
                .map(|n| n.utf8_text(&source_bytes).unwrap().into())
                .collect::<Vec<_>>()
                .into(),
        )
        .into(),
        "set_type" => {
            if let Some(child) = node.child(2) {
                LangType::Set(
                    type_manager
                        .node_type(child.id())
                        .unwrap_or_default()
                        .into(),
                )
                .into()
            } else {
                LangType::Set(LangType::Unknown.into()).into()
            }
        }
        "list_type" => {
            if let Some(child) = node.child(2) {
                LangType::List(
                    type_manager
                        .node_type(child.id())
                        .unwrap_or_default()
                        .into(),
                )
                .into()
            } else {
                LangType::List(LangType::Unknown.into()).into()
            }
        }
        "map_type" => {
            if let (Some(key), Some(value)) = (node.child(1), node.child(3)) {
                LangType::Map(
                    type_manager.node_type(key.id()).unwrap_or_default().into(),
                    type_manager
                        .node_type(value.id())
                        .unwrap_or_default()
                        .into(),
                )
                .into()
            } else {
                LangType::Map(LangType::Unknown.into(), LangType::Unknown.into()).into()
            }
        }
        "composite_type" => LangType::Composite(
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
        )
        .into(),
        "type_definition_item" => {
            if let (Some(identifier), Some(lang_type)) = (node.child(0), node.child(2)) {
                let name: String = { identifier.utf8_text(&source_bytes).unwrap().into() };
                let lang_type = type_manager.node_type(lang_type.id()).unwrap_or_default();
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
                nodes.iter().for_each(|n| {
                    let name: String = n.utf8_text(&source_bytes).unwrap().into();
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
            if let (Some(name), Some(lang_type)) = (node.child(1), node.child(3)) {
                let name: String = name.utf8_text(&source_bytes).unwrap().into();
                let lang_type = type_manager.node_type(lang_type.id()).unwrap_or_default();
                symbol_manager.add_symbol(
                    &node.parent().unwrap().parent().unwrap(),
                    &name,
                    Symbol::Variable(lang_type),
                );
            } else {
                diagnostics.push(Diagnostic {
                    level: diagnostic::Level::Error,
                    range: node.range(),
                    message: "Invalid external item".to_string(),
                });
            }
            None
        }
        // expressions
        "list_expression" => {
            if let Some(Some(Some(result))) = node.child_by_field_name("items").map(|items| {
                items
                    .child(0)
                    .map(|first| type_manager.node_type(first.id()))
            }) {
                LangType::List(result.clone()).into()
            } else {
                LangType::List(LangType::Unknown.into()).into()
            }
        }
        "map_item" => {
            let key = node.child_by_field_name("key");
            let value = node.child_by_field_name("value");
            if let (Some(key), Some(value)) = (key, value) {
                let key_type = type_manager.node_type(key.id());
                let value_type = type_manager.node_type(value.id());
                LangType::MapItem(key_type.unwrap_or_default(), value_type.unwrap_or_default())
                    .into()
            } else {
                LangType::Unknown.into()
            }
        }
        "map_expression" => {
            let unknown: Option<LangType> =
                LangType::MapItem(LangType::Unknown.into(), LangType::Unknown.into()).into();
            if let Some(first) = node.child(1) {
                match first.kind() {
                    "map_item" => {
                        if let LangType::MapItem(key, value) = type_manager
                            .node_type(first.id())
                            .clone()
                            .unwrap_or_default()
                            .deref()
                        {
                            LangType::Map(key.clone(), value.clone()).into()
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
                        .deref()
                        .clone()
                        .into(),
                    _ => LangType::Unknown.into(),
                }
            } else {
                LangType::Unknown.into()
            }
        }
        "binary_expression" => {
            if let (Some(left), Some(operator), Some(right)) =
                (node.child(0), node.child(1), node.child(2))
            {
                let left_type = type_manager.node_type(left.id()).unwrap_or_default();
                let right_type = type_manager.node_type(right.id()).unwrap_or_default();
                if left_type.deref() != right_type.deref() {
                    diagnostics.push(Diagnostic {
                        level: diagnostic::Level::Error,
                        range: node.range(),
                        message: "Type mismatch".to_string(),
                    })
                }
                match operator.kind() {
                    "+" | "-" | "*" | "/" | "div" | "rem" | "mod" => {
                        left_type.deref().clone().into()
                    }
                    "or" | "=>" | "<=>" | "=" | "<>" | "<" | "<=" | ">" | ">=" | "inset"
                    | "notinset" | "and" => LangType::Bool.into(),
                    _ => LangType::Unknown.into(),
                }
            } else {
                LangType::Unknown.into()
            }
        }
        "reference_expression" => {
            if node.child_count() == 1 {
                let child = node.child(0).unwrap();
                let name = child.utf8_text(&source_bytes).unwrap();
                if let Some(Symbol::Variable(lang_type)) = symbol_manager.resolve_symbol(node, name)
                {
                    lang_type.deref().clone().into()
                } else {
                    LangType::Unknown.into()
                }
            } else if let (Some(refer), Some(id)) = (node.child(0), node.child(2)) {
                let left_type = type_manager.node_type(refer.id()).unwrap_or_default();
                if let LangType::Composite(fields) = left_type.skip_alias().deref() {
                    let name: String = id.utf8_text(&source_bytes).unwrap().into();
                    let field_type = fields.get(&name);
                    if field_type.is_none() {
                        diagnostics.push(Diagnostic {
                            range: node.range(),
                            level: diagnostic::Level::Warning,
                            message: format!("Field {} not found", name),
                        });
                    }
                    field_type
                        .cloned()
                        .unwrap_or_default()
                        .deref()
                        .clone()
                        .into()
                } else {
                    LangType::Unknown.into()
                }
            } else {
                LangType::Unknown.into()
            }
        }
        "modify_expression" => {
            if let Some(refer) = node.child(2) {
                type_manager
                    .node_type(refer.id())
                    .unwrap_or_default()
                    .deref()
                    .clone()
                    .into()
            } else {
                LangType::Unknown.into()
            }
        }
        "quantified_expression" => LangType::Bool.into(),
        "function_expression" => {
            let fn_name = node.child(0);
            let args_node = node.child(2);
            if let Some(fn_name) = fn_name {
                let str_name = fn_name.utf8_text(&source_bytes).unwrap();
                let args = if let Some(args_node) = args_node {
                    collect_when(&mut args_node.walk(), |node| {
                        node.kind().ends_with("expression")
                    })
                } else {
                    vec![]
                };
                let first_type = args.get(0).map(|node| {
                    type_manager
                        .node_type(node.id())
                        .unwrap_or_default()
                        .deref()
                        .clone()
                });
                match str_name {
                    "abs" | "bound" | "floor" | "power" => {
                        args.iter().for_each(|arg| {
                            let arg_type = type_manager.node_type(arg.id());
                            if arg_type.is_none() || !arg_type.unwrap().skip_alias().is_numeric() {
                                diagnostics.push(Diagnostic {
                                    level: diagnostic::Level::Warning,
                                    range: arg.range(),
                                    message: "Invalid argument type".to_string(),
                                });
                            }
                        });
                        first_type
                    }
                    "union" | "inter" | "diff" | "dunion" | "dinter" => first_type,
                    "len" => LangType::Nat.into(),
                    _ => {
                        let fn_type = type_manager.node_type(fn_name.id());
                        if let Some(fn_type) = fn_type {
                            if let LangType::Map(_, value) = fn_type.skip_alias().deref() {
                                value.deref().clone().into()
                            } else {
                                diagnostics.push(Diagnostic {
                                    level: diagnostic::Level::Warning,
                                    range: fn_name.range(),
                                    message: "Invalid function type".to_string(),
                                });
                                LangType::Unknown.into()
                            }
                        } else {
                            diagnostics.push(Diagnostic {
                                level: diagnostic::Level::Warning,
                                range: node.range(),
                                message: "Function not found".to_string(),
                            });
                            LangType::Unknown.into()
                        }
                    }
                }
            } else {
                diagnostics.push(Diagnostic {
                    level: diagnostic::Level::Error,
                    range: node.range(),
                    message: "Invalid function expression".to_string(),
                });
                LangType::Unknown.into()
            }
        }

        _ => None,
    };
    if let Some(lang_type) = node_type {
        println!(
            "{:<30} {:?}",
            node.utf8_text(&source_bytes).unwrap(),
            lang_type
        );
        type_manager.set_node_type(node.id(), lang_type.into());
    }
}
