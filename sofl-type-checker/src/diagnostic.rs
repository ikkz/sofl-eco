#[derive(Debug)]
pub enum Level {
    Error,
    Warning,
    Info,
}

#[derive(Debug)]
pub struct Diagnostic {
    pub range: tree_sitter::Range,
    pub level: Level,
    pub message: String,
}
