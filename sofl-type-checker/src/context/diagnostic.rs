use serde::Serialize;

#[derive(Serialize, Debug, Clone, Copy)]
pub enum Level {
    Error,
    Warning,
    #[allow(dead_code)]
    Info,
}

#[derive(Serialize, Debug, Clone)]
pub struct Diagnostic {
    pub range: crate::types::Range,
    pub level: Level,
    pub message: String,
}
