pub mod function;

use std::{collections::HashMap, fmt::Display, mem::discriminant, ops::Deref, rc::Rc};

#[derive(Debug, Clone, PartialEq, Default)]
pub enum LangType {
    #[default]
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
    Variable(Rc<LangType>),
    Map(Rc<LangType>, Rc<LangType>),
    MapItem(Rc<LangType>, Rc<LangType>),
    Enumeration(Rc<Vec<String>>),
    Composite(Rc<HashMap<String, Rc<LangType>>>),
    Alias(String, Rc<LangType>),
    Generic(String),
    Function(function::FunctionType),
}

impl LangType {
    pub fn skip_alias(&self) -> Rc<LangType> {
        let mut lang_type = self;
        while let Self::Alias(_, alias_type) = lang_type {
            lang_type = alias_type;
        }
        lang_type.clone().into()
    }

    pub fn is_numeric(&self) -> bool {
        matches!(
            self.skip_alias().deref(),
            LangType::Nat | LangType::Nat0 | LangType::Int | LangType::Real
        )
    }

    pub fn is_set_like(&self) -> bool {
        matches!(
            self.skip_alias().deref(),
            LangType::Set(_) | LangType::List(_) | LangType::Map(_, _)
        )
    }

    pub fn variable_type(&self) -> Rc<LangType> {
        match self.skip_alias().deref() {
            LangType::Variable(t) => match t.deref() {
                LangType::Set(t) | LangType::List(t) => t.clone(),
                _ => t.clone(),
            },
            _ => self.clone().into(),
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
                format!("composed of {} end;", s)
            }
            LangType::Alias(_, t) => t.expanded_type(),
            _ => self.to_string(),
        }
    }

    pub fn infer(&self, actual: Rc<LangType>) -> HashMap<String, Rc<LangType>> {
        let mut map = HashMap::new();
        if let LangType::Generic(name) = self {
            map.insert(name.clone(), actual);
        } else if discriminant(self) == discriminant(actual.deref()) {
            self.infer_directly(actual, &mut map);
        } else if discriminant(self) == discriminant(&actual.skip_alias()) {
            self.infer_directly(actual.skip_alias(), &mut map);
        }
        map
    }

    fn infer_directly(&self, actual: Rc<LangType>, map: &mut HashMap<String, Rc<LangType>>) {
        match (self, actual.deref()) {
            (LangType::Set(t1), LangType::Set(t2)) => {
                map.extend(t1.infer(t2.clone()));
            }
            (LangType::List(t1), LangType::List(t2)) => {
                map.extend(t1.infer(t2.clone()));
            }
            (LangType::Map(k1, v1), LangType::Map(k2, v2)) => {
                map.extend(k1.infer(k2.clone()));
                map.extend(v1.infer(v2.clone()));
            }
            _ => (),
        }
    }

    pub fn specialize(&self, map: &HashMap<String, Rc<LangType>>) -> Rc<LangType> {
        match self {
            LangType::Generic(name) => map.get(name).unwrap_or(&Rc::new(LangType::Unknown)).clone(),
            LangType::Set(t) => LangType::Set(t.specialize(map)).into(),
            LangType::List(t) => LangType::List(t.specialize(map)).into(),
            LangType::Map(k, v) => LangType::Map(k.specialize(map), v.specialize(map)).into(),
            LangType::MapItem(k, v) => {
                LangType::MapItem(k.specialize(map), v.specialize(map)).into()
            }
            LangType::Alias(_, t) => t.skip_alias().specialize(map),
            _ => self.clone().into(),
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
            LangType::Variable(t) => write!(f, "{}", t),
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
            LangType::Alias(name, _) => write!(f, "{}", name),
            LangType::Generic(name) => write!(f, "{}", name),
            LangType::Function(func) => write!(f, "function{}", func),
        }
    }
}
