pub mod context;
mod lang_type;
mod type_node;
mod types;
mod utils;

use std::{cell::RefCell, collections::HashMap, rc::Rc};

use crate::context::Context;
use context::symbol_manager::SymbolTable;
use serde::Serialize;
use tree_sitter::Parser;

#[derive(Serialize, Debug)]
pub struct EvaluateResult {
    diagnostics: Vec<context::diagnostic::Diagnostic>,
    type_details: Vec<types::TypeDetail>,
}

pub fn evaluate_type(
    source_code: String,
    symbols: context::symbol_manager::SymbolTable,
) -> EvaluateResult {
    let ctx = Rc::new(RefCell::new(Context::new(source_code.clone(), symbols)));
    let mut parser = Parser::new();
    parser
        .set_language(&tree_sitter_sofl::language())
        .expect("Error loading SOFL language");
    let tree = parser.parse(source_code, None).unwrap();

    let mut cursor = tree.walk();
    type_node::traverse(&mut cursor, ctx.clone());
    let ctx = ctx.borrow_mut();
    EvaluateResult {
        diagnostics: ctx.diagnostics.clone(),
        type_details: ctx.collect_types.clone(),
    }
}

pub fn collect_symbols(source_code: String) -> SymbolTable {
    let ctx = Rc::new(RefCell::new(Context::new(
        source_code.clone(),
        HashMap::new(),
    )));
    let mut parser = Parser::new();
    parser
        .set_language(&tree_sitter_sofl::language())
        .expect("Error loading SOFL language");
    let tree = parser.parse(source_code, None).unwrap();

    let mut cursor = tree.walk();
    type_node::traverse(&mut cursor, ctx.clone());
    let ctx = ctx.borrow_mut();
    ctx.symbol_manager
        .node_symbols(&tree.root_node())
        .unwrap_or(&HashMap::new())
        .clone()
}

#[cfg(test)]
mod tests {

    #[test]
    fn test_typed_syntax_tree() {
        let source_code = r#"
module ATM;
type
    TA = int;
    TB = string;
    TC = {<A>, <B>, <C>};
    TD = set of TA;
    TE = list of TB;
    TF = composed of
      name: TB;
      props: TD;
      props1: int;
      props2: string;
    end;
var
        mp: map int to TF;
process Withdraw()
pre abs(1) = 0
post true
end_process;
        "#;
        super::evaluate_type(source_code.to_string(), std::collections::HashMap::new());
    }
}
