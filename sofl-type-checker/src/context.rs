use crate::{diagnostic::Diagnostic, symbol_manager::SymbolManager, type_manager::TypeManager};

#[derive(Debug)]
pub struct Context {
    pub source: String,
    pub source_bytes: Vec<u8>,
    pub diagnostics: Vec<Diagnostic>,
    pub type_manager: TypeManager,
    pub symbol_manager: SymbolManager,
}

impl Context {
    pub fn new(source: String) -> Self {
        Context {
            symbol_manager: SymbolManager::new(),
            type_manager: TypeManager::new(),
            source_bytes: source.as_bytes().to_vec(),
            source,
            diagnostics: Vec::new(),
        }
    }
}
