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
        let mut map = HashMap::new();
        for (expect, actual) in self.arguments.iter().zip(args.iter()).rev() {
            expect.infer(actual.clone()).iter().for_each(|(k, v)| {
                map.insert(k.clone(), v.clone());
            });
        }
        self.return_type.specialize(&map)
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
