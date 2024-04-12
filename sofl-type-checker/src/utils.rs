use tree_sitter::{Node, TreeCursor};

pub fn collect_kind<'a>(cursor: &mut TreeCursor<'a>, kind: &str) -> Vec<Node<'a>> {
    let mut results = Vec::new();

    {
        let node = cursor.node();
        if node.kind() == kind {
            results.push(node);
        }
    }

    if cursor.goto_first_child() {
        results.extend(collect_kind(cursor, kind));

        while cursor.goto_next_sibling() {
            results.extend(collect_kind(cursor, kind));
        }

        cursor.goto_parent();
    }

    results
}
