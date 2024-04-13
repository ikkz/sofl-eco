mod context;
mod diagnostic;
mod symbol_manager;
pub mod type_manager;
mod type_node;
mod utils;

use std::{cell::RefCell, rc::Rc};

use crate::context::Context;
use anyhow::Result;
use tree_sitter::{Parser, TreeCursor};

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
        let result = super::typed_syntax_tree(source_code.to_string());
        assert!(result.is_ok());
    }
}
