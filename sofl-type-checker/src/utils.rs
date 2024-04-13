use tree_sitter::{Node, TreeCursor};

pub fn collect_kind<'a>(cursor: &mut TreeCursor<'a>, kind: &str) -> Vec<Node<'a>> {
    collect_when(cursor, |node| node.kind() == kind)
}

pub fn collect_when<'a>(cursor: &mut TreeCursor<'a>, when: impl Fn(Node) -> bool + Copy) -> Vec<Node<'a>> {
    let mut results = Vec::new();

    {
        let node = cursor.node();
        if when(node) {
            results.push(node);
        }
    }

    if cursor.goto_first_child() {
        results.extend(collect_when(cursor, when));

        while cursor.goto_next_sibling() {
            results.extend(collect_when(cursor, when));
        }

        cursor.goto_parent();
    }

    results
}
