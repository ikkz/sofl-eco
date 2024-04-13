use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug, Clone, Copy)]
pub struct Point {
    pub row: usize,
    pub column: usize,
}

#[derive(Serialize, Deserialize, Debug, Clone, Copy)]
pub struct Range {
    pub start_byte: usize,
    pub end_byte: usize,
    pub start_point: Point,
    pub end_point: Point,
}

impl From<tree_sitter::Range> for Range {
    fn from(range: tree_sitter::Range) -> Self {
        Range {
            start_byte: range.start_byte,
            end_byte: range.end_byte,
            start_point: Point {
                row: range.start_point.row,
                column: range.start_point.column,
            },
            end_point: Point {
                row: range.end_point.row,
                column: range.end_point.column,
            },
        }
    }
}

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct TypeDetail {
    pub range: Range,
    pub source: String,
    pub type_str: String,
    pub type_expanded: String,
}
