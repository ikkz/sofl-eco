use crate::lang_type::LangType;
use std::{collections::HashMap, rc::Rc};
#[derive(Debug)]
pub struct TypeManager {
    types: HashMap<usize, Rc<LangType>>,
}

impl Default for TypeManager {
    fn default() -> Self {
        Self::new()
    }
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_display() {
        let lang_type = LangType::Map(Rc::new(LangType::Int), Rc::new(LangType::String));
        assert_eq!(format!("{}", lang_type), "map int to string");
    }
}
