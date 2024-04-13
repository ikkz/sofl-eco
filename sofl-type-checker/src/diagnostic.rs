use serde::Serialize;

#[derive(Serialize, Debug, Clone, Copy)]
pub enum Level {
    Error,
    Warning,
    Info,
}

#[derive(Serialize, Debug, Clone)]
pub struct Diagnostic {
    pub range: crate::types::Range,
    pub level: Level,
    pub message: String,
}
