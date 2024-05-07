use crate::lang_type::LangType;
use std::{collections::HashMap, rc::Rc};
use tree_sitter::Node;

#[derive(Clone, Debug)]
pub enum Symbol {
    Type(Rc<LangType>),
    Variable(Rc<LangType>),
    Function(Rc<LangType>),
}

pub type SymbolTable = HashMap<String, Symbol>;

#[derive(Debug)]
pub struct SymbolManager {
    symbols: HashMap<usize, SymbolTable>,
    predefined_symbols: SymbolTable,
}

impl SymbolManager {
    pub fn new(predefined_symbols: SymbolTable) -> Self {
        SymbolManager {
            symbols: HashMap::new(),
            predefined_symbols,
        }
    }

    pub fn add_symbol(&mut self, node: &Node, name: &str, symbol: Symbol) {
        let node_id = node.id();

        self.symbols
            .entry(node_id)
            .or_default()
            .insert(name.into(), symbol);
    }

    pub fn resolve_symbol(&self, from: Node, name: &str) -> Option<&Symbol> {
        let mut node = Some(from);
        while node.is_some() {
            let _node = node.unwrap();
            if let Some(symbol_table) = self.symbols.get(&_node.id()) {
                if let Some(symbol) = symbol_table.get(name) {
                    return Some(symbol);
                }
            }
            node = node.unwrap().parent();
        }
        self.predefined_symbols.get(name)
    }

    pub fn node_symbols(&self, node: &Node) -> Option<&SymbolTable> {
        self.symbols.get(&node.id())
    }
}
