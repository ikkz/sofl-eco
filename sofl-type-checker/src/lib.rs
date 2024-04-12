mod context;
mod diagnostic;
mod symbol_manager;
pub mod type_manager;
mod utils;

use std::{cell::RefCell, collections::HashMap, ops::Deref, rc::Rc};

use crate::context::Context;
use anyhow::Result;
use diagnostic::Diagnostic;
use itertools::Itertools;
use symbol_manager::Symbol;
use tree_sitter::{Parser, TreeCursor};
use type_manager::LangType;
use utils::collect_kind;

pub fn typed_syntax_tree(source_code: String) -> Result<()> {
    let ctx = Rc::new(RefCell::new(Context::new(source_code.clone())));
    let mut parser = Parser::new();
    parser.set_language(&tree_sitter_sofl::language())?;
    let tree = parser.parse(source_code, None).unwrap();

    let mut cursor = tree.walk();
    traverse(&mut cursor, ctx.clone());

    print!("{:?}", ctx.borrow().diagnostics);
    Ok(())
}

fn traverse(cursor: &mut TreeCursor, ctx: Rc<RefCell<Context>>) {
    if cursor.goto_first_child() {
        traverse(cursor, ctx.clone());
        while cursor.goto_next_sibling() {
            traverse(cursor, ctx.clone());
        }
        cursor.goto_parent();
    }
    visit(cursor, ctx.clone());
}

fn visit(cursor: &TreeCursor, ctx: Rc<RefCell<Context>>) {
    let mut ctx = ctx.borrow_mut();
    let node = cursor.node();
    let node_type: Option<LangType> = match node.kind() {
        "type_identifier" => {
            if let Some(child) = node.child(0) {
                match ctx
                    .symbol_manager
                    .resolve_symbol(node, child.utf8_text(&ctx.source_bytes).unwrap())
                {
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
                ctx.type_manager
                    .node_type(child.id())
                    .unwrap_or_else(|| match child.utf8_text(&ctx.source_bytes).unwrap() {
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
                .map(|n| n.utf8_text(&ctx.source_bytes).unwrap().into())
                .collect::<Vec<_>>()
                .into(),
        )
        .into(),
        "set_type" => {
            if let Some(child) = node.child(2) {
                LangType::Set(
                    ctx.type_manager
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
                    ctx.type_manager
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
                    ctx.type_manager
                        .node_type(key.id())
                        .unwrap_or_default()
                        .into(),
                    ctx.type_manager
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
                        .utf8_text(&ctx.source_bytes)
                        .unwrap()
                        .into();
                    let lang_type = pair
                        .get(1)
                        .map(|node| ctx.type_manager.node_type(node.id()).unwrap_or_default())
                        .unwrap_or_default();
                    (name, lang_type)
                })
                .collect::<HashMap<_, _>>()
                .into(),
        )
        .into(),
        "type_definition_item" => {
            if let (Some(identifier), Some(lang_type)) = (node.child(0), node.child(2)) {
                let name: String = { identifier.utf8_text(&ctx.source_bytes).unwrap().into() };
                let lang_type = ctx
                    .type_manager
                    .node_type(lang_type.id())
                    .unwrap_or_default();
                ctx.symbol_manager.add_symbol(
                    &node.parent().unwrap().parent().unwrap(),
                    &name,
                    Symbol::Type(LangType::Alias(name.clone(), lang_type).into()),
                );
            }
            None
        }
        "variable_definition_item" => {
            if let (Some(identifier), Some(lang_type)) = (node.child(0), node.child(2)) {
                let name: String = { identifier.utf8_text(&ctx.source_bytes).unwrap().into() };
                let lang_type = ctx
                    .type_manager
                    .node_type(lang_type.id())
                    .unwrap_or_default();
                ctx.symbol_manager.add_symbol(
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
                .map(|n| ctx.type_manager.node_type(n.id()).unwrap_or_default());
            if let Some(lang_type) = lang_type {
                nodes.iter().for_each(|n| {
                    let name: String = n.utf8_text(&ctx.source_bytes).unwrap().into();
                    ctx.symbol_manager.add_symbol(
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
                let name: String = name.utf8_text(&ctx.source_bytes).unwrap().into();
                let lang_type = ctx
                    .type_manager
                    .node_type(lang_type.id())
                    .unwrap_or_default();
                ctx.symbol_manager.add_symbol(
                    &node.parent().unwrap().parent().unwrap(),
                    &name,
                    Symbol::Variable(lang_type),
                );
            } else {
                ctx.diagnostics.push(Diagnostic {
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
                    .map(|first| ctx.type_manager.node_type(first.id()))
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
                let key_type = ctx.type_manager.node_type(key.id());
                let value_type = ctx.type_manager.node_type(value.id());
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
                        if let LangType::MapItem(key, value) = ctx
                            .type_manager
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
                    "-" | "not" | "~" => ctx
                        .type_manager
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
                let left_type = ctx.type_manager.node_type(left.id()).unwrap_or_default();
                let right_type = ctx.type_manager.node_type(right.id()).unwrap_or_default();
                if left_type.deref() != right_type.deref() {
                    ctx.diagnostics.push(Diagnostic {
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
                let name = child.utf8_text(&ctx.source_bytes).unwrap();
                if let Some(Symbol::Variable(lang_type)) =
                    ctx.symbol_manager.resolve_symbol(node, name)
                {
                    lang_type.deref().clone().into()
                } else {
                    LangType::Unknown.into()
                }
            } else if let (Some(refer), Some(id)) = (node.child(0), node.child(2)) {
                let left_type = ctx.type_manager.node_type(refer.id()).unwrap_or_default();
                if let LangType::Composite(fields) = left_type.skip_alias().deref() {
                    let name: String = id.utf8_text(&ctx.source_bytes).unwrap().into();
                    let field_type = fields.get(&name);
                    if field_type.is_none() {
                        ctx.diagnostics.push(Diagnostic {
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
                ctx.type_manager
                    .node_type(refer.id())
                    .unwrap_or_default()
                    .deref()
                    .clone()
                    .into()
            } else {
                LangType::Unknown.into()
            }
        }

        _ => None,
    };
    if let Some(lang_type) = node_type {
        println!(
            "{:<30} {:?}",
            node.utf8_text(&ctx.source_bytes).unwrap(),
            lang_type
        );
        ctx.type_manager.set_node_type(node.id(), lang_type.into());
    }
}

mod tests {
    use super::*;

    #[test]
    fn test_typed_syntax_tree() {
        let source_code = r#"
module ATM;
type Account = composed of
    balance: real;
end;
process Withdraw(amount: real | account1: Account)
e_msg: string | cash: real
ext wr account_file: set of Account
pre account1 inset account_file and account1.balance >= amount
post (exists[x: account_file] x = account1 and x.balance >= amount and cash = amount)
        and account_file = union(diff(~account_file, {account1}), {modify(account1, balance -> account1.balance - amount)})
        or not exists[x: account_file] x = account1 and x.balance >= amount and e_msg = "The amount is too big"
end_process;
        "#;
        let result = typed_syntax_tree(source_code.to_string());
        assert!(result.is_ok());
    }
}
