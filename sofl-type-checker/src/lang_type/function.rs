use crate::lang_type::LangType;
use std::{collections::HashMap, fmt::Display, rc::Rc};

#[derive(Clone, Debug, PartialEq)]
pub struct FunctionType {
    pub generics: Vec<Rc<LangType>>,
    pub arguments: Vec<Rc<LangType>>,
    pub return_type: Rc<LangType>,
}

impl FunctionType {
    pub fn infer_return_type(&self, args: Vec<Rc<LangType>>) -> Rc<LangType> {
        self.return_type
            .specialize(&self.arguments.iter().zip(args.iter()).rev().fold(
                HashMap::new(),
                |mut map, (expect, actual)| {
                    map.extend(expect.infer(actual.clone()));
                    map
                },
            ))
    }
}

impl Display for FunctionType {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "({}) : {}",
            self.arguments
                .iter()
                .map(|t| t.to_string())
                .collect::<Vec<String>>()
                .join(", "),
            self.return_type
        )
    }
}
