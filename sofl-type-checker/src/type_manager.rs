use std::{collections::HashMap, rc::Rc};

#[derive(Debug, Clone, PartialEq)]
pub enum LangType {
    Unknown,
    Nat,
    Nat0,
    Int,
    Real,
    String,
    Char,
    Bool,
    Set(Rc<LangType>),
    List(Rc<LangType>),
    Map(Rc<LangType>, Rc<LangType>),
    MapItem(Rc<LangType>, Rc<LangType>),
    Enumeration(Rc<Vec<String>>),
    Composite(Rc<HashMap<String, Rc<LangType>>>),
    Alias(String, Rc<LangType>),
}

impl Default for LangType {
    fn default() -> Self {
        LangType::Unknown
    }
}

impl LangType {
    pub fn skip_alias(&self) -> Rc<LangType> {
        let mut lang_type = self;
        while let Self::Alias(_, alias_type) = lang_type {
            lang_type = alias_type;
        }
        return lang_type.clone().into();
    }
}

#[derive(Debug)]
pub struct TypeManager {
    types: HashMap<usize, Rc<LangType>>,
}

impl TypeManager {
    pub fn new() -> Self {
        TypeManager {
            types: HashMap::new(),
        }
    }

    pub fn set_node_type(&mut self, node_id: usize, lang_type: Rc<LangType>) {
        self.types.insert(node_id, lang_type);
    }

    pub fn node_type(&self, node_id: usize) -> Option<Rc<LangType>> {
        self.types.get(&node_id).cloned()
    }
}
