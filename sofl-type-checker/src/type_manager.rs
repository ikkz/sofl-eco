use std::{collections::HashMap, fmt::Display, ops::Deref, rc::Rc};

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

    pub fn is_numeric(&self) -> bool {
        match self.skip_alias().deref() {
            LangType::Nat | LangType::Nat0 | LangType::Int | LangType::Real => true,
            _ => false,
        }
    }

    pub fn is_set_like(&self) -> bool {
        match self.skip_alias().deref() {
            LangType::Set(_) | LangType::List(_) | LangType::Map(_, _) => true,
            _ => false,
        }
    }

    pub fn expanded_type(&self) -> String {
        match self {
            LangType::Set(t) => format!("set of {}", t.expanded_type()),
            LangType::List(t) => format!("list of {}", t.expanded_type()),
            LangType::Map(k, v) => format!("map {} to {}", k.expanded_type(), v.expanded_type()),
            LangType::MapItem(k, v) => format!("{} -> {}", k.expanded_type(), v.expanded_type()),
            LangType::Composite(fields) => {
                let mut s = String::new();
                for (i, (name, t)) in fields.iter().enumerate() {
                    if i > 0 {
                        s.push_str(", ");
                    }
                    s.push_str(&format!("{}: {}", name, t.expanded_type()));
                }
                format!("composed of {}", s)
            }
            LangType::Alias(name, t) => format!("{} = {}", name, t.expanded_type()),
            _ => self.to_string(),
        }
    }
}

impl Display for LangType {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            LangType::Unknown => write!(f, "unknown"),
            LangType::Nat => write!(f, "nat"),
            LangType::Nat0 => write!(f, "nat0"),
            LangType::Int => write!(f, "int"),
            LangType::Real => write!(f, "real"),
            LangType::String => write!(f, "string"),
            LangType::Char => write!(f, "char"),
            LangType::Bool => write!(f, "bool"),
            LangType::Set(t) => write!(f, "set of {}", t),
            LangType::List(t) => write!(f, "list of {}", t),
            LangType::Map(k, v) => write!(f, "map {} to {}", k, v),
            LangType::MapItem(k, v) => write!(f, "{} -> {}", k, v),
            LangType::Enumeration(e) => {
                let mut s = String::new();
                for (i, item) in e.iter().enumerate() {
                    if i > 0 {
                        s.push_str(", ");
                    }
                    s.push_str(&format!("<{}>", item));
                }
                write!(f, "{{{}}}", s)
            }
            LangType::Composite(fields) => {
                let mut s = String::new();
                for (i, (name, t)) in fields.iter().enumerate() {
                    if i > 0 {
                        s.push_str(", ");
                    }
                    s.push_str(&format!("{}: {}", name, t));
                }
                write!(f, "composed of {}", s)
            }
            LangType::Alias(name, t) => write!(f, "{} = {}", name, t),
        }
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_display() {
        let lang_type = LangType::Map(Rc::new(LangType::Int), Rc::new(LangType::String));
        assert_eq!(format!("{}", lang_type), "map int to string");
    }
}
