mod context;
mod diagnostic;
mod symbol_manager;
pub mod type_manager;
mod type_node;
mod types;
mod utils;
mod lang_type;

use std::{cell::RefCell, rc::Rc};

use crate::context::Context;
use serde::Serialize;
use tree_sitter::{Parser, TreeCursor};

#[derive(Serialize, Debug)]
pub struct EvaluateResult {
    diagnostics: Vec<diagnostic::Diagnostic>,
    type_details: Vec<types::TypeDetail>,
}

pub fn evaluate_type(source_code: String) -> EvaluateResult {
    let ctx = Rc::new(RefCell::new(Context::new(source_code.clone())));
    let mut parser = Parser::new();
    parser
        .set_language(&tree_sitter_sofl::language())
        .expect("Error loading SOFL language");
    let tree = parser.parse(source_code, None).unwrap();

    let mut cursor = tree.walk();
    traverse(&mut cursor, ctx.clone());
    let ctx = ctx.borrow_mut();
    EvaluateResult {
        diagnostics: ctx.diagnostics.clone(),
        type_details: ctx.collect_types.clone(),
    }
}

fn traverse(cursor: &mut TreeCursor, ctx: Rc<RefCell<Context>>) {
    if cursor.goto_first_child() {
        traverse(cursor, ctx.clone());
        while cursor.goto_next_sibling() {
            traverse(cursor, ctx.clone());
        }
        cursor.goto_parent();
    }
    type_node::type_node(cursor, ctx.clone());
}

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
        super::evaluate_type(source_code.to_string());
    }
}
