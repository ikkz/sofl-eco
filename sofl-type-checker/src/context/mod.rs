pub mod diagnostic;
pub mod symbol_manager;
pub mod type_manager;

use symbol_manager::*;
use type_manager::*;
use diagnostic::Diagnostic;

use crate::types::TypeDetail;

#[derive(Debug)]
pub struct Context {
    pub source: String,
    pub source_bytes: Vec<u8>,
    pub diagnostics: Vec<Diagnostic>,
    pub type_manager: TypeManager,
    pub symbol_manager: SymbolManager,
    pub collect_types: Vec<TypeDetail>,
}

impl Context {
    pub fn new(source: String, predefined_symbols: SymbolTable) -> Self {
        Context {
            symbol_manager: SymbolManager::new(predefined_symbols),
            type_manager: TypeManager::new(),
            source_bytes: source.as_bytes().to_vec(),
            source,
            diagnostics: Vec::new(),
            collect_types: Vec::new(),
        }
    }
}
