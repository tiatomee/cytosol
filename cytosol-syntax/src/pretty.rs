use pretty::RcDoc as Doc;

use crate::{
    AtomBinding, Enzyme, Expression, Extern, File, Gene, GeneStatement, Identifier, InfixOperator,
    Literal, PrefixOperator, Product, Quantified, Type,
};

pub fn pretty_print<T: ToDoc>(val: &T, width: usize) -> String {
    let doc = val.to_doc();
    let mut v = Vec::new();
    doc.render(width, &mut v).unwrap();
    String::from_utf8_lossy(&v).to_string()
}

pub trait ToDoc {
    fn to_doc(&self) -> Doc;
}

impl<T: ToDoc> ToDoc for Vec<T> {
    fn to_doc(&self) -> Doc {
        if self.is_empty() {
            Doc::text("()")
        } else {
            Doc::text("(")
                .append(Doc::line_().append(Doc::intersperse(
                    self.iter().map(|t| t.to_doc()),
                    Doc::line(),
                )))
                .nest(4)
                .group()
                .append(")")
        }
    }
}

impl ToDoc for File {
    fn to_doc(&self) -> Doc {
        Doc::text("(file")
            .append(
                Doc::line()
                    .append(self.genes.to_doc())
                    .append(Doc::hardline())
                    .append(self.enzymes.to_doc().group())
                    .append(Doc::hardline())
                    .append(self.externs.to_doc().group())
                    .nest(4)
                    .group(),
            )
            .append(Doc::text(")"))
    }
}
impl ToDoc for Identifier {
    fn to_doc(&self) -> Doc {
        Doc::text(&self.1)
    }
}
impl ToDoc for Extern {
    fn to_doc(&self) -> Doc {
        Doc::text("(extern")
            .append(
                Doc::line()
                    .append(self.name.to_doc())
                    .append(Doc::space())
                    .append(self.parameters.to_doc())
                    .nest(4)
                    .group(),
            )
            .append(Doc::text(")"))
    }
}
impl ToDoc for AtomBinding {
    fn to_doc(&self) -> Doc {
        if self.fields.is_empty() {
            self.name.to_doc()
        } else {
            Doc::text("(")
                .append(self.name.to_doc())
                .append(Doc::space())
                .append(self.fields.to_doc())
                .append(Doc::text(")"))
                .group()
        }
    }
}
impl ToDoc for Type {
    fn to_doc(&self) -> Doc {
        match self {
            Type::Int(_) => Doc::text("int"),
            Type::String(_) => Doc::text("string"),
        }
    }
}
impl ToDoc for Gene {
    fn to_doc(&self) -> Doc {
        Doc::text("(gene")
            .append(
                Doc::hardline()
                    .append(self.factors.to_doc())
                    .append(Doc::hardline())
                    .append(self.body.to_doc())
                    .nest(4)
                    .group(),
            )
            .append(Doc::text(")"))
            .group()
    }
}
impl<T: ToDoc> ToDoc for Quantified<T> {
    fn to_doc(&self) -> Doc {
        if let Some((_, n)) = &self.quantity {
            Doc::text("(")
                .append(Doc::as_string(n))
                .append(Doc::space())
                .append(self.value.to_doc())
                .append(Doc::text(")"))
                .group()
        } else {
            self.value.to_doc()
        }
    }
}
impl ToDoc for Enzyme {
    fn to_doc(&self) -> Doc {
        todo!()
    }
}
impl ToDoc for Product {
    fn to_doc(&self) -> Doc {
        todo!()
    }
}
impl ToDoc for GeneStatement {
    fn to_doc(&self) -> Doc {
        todo!()
    }
}
impl ToDoc for Expression {
    fn to_doc(&self) -> Doc {
        todo!()
    }
}
impl ToDoc for Literal {
    fn to_doc(&self) -> Doc {
        match self {
            Literal::Integer(_, i) => Doc::as_string(i),
            Literal::String(_, s) => Doc::text(format!("{:?}", s)),
        }
    }
}
impl ToDoc for PrefixOperator {
    fn to_doc(&self) -> Doc {
        match self {
            PrefixOperator::Neg => Doc::text("-"),
        }
    }
}
impl ToDoc for InfixOperator {
    fn to_doc(&self) -> Doc {
        match self {
            InfixOperator::Add => Doc::text("+"),
            InfixOperator::Sub => Doc::text("-"),
        }
    }
}

impl ToDoc for (Identifier, Type) {
    fn to_doc(&self) -> Doc {
        Doc::text("(")
            .append(
                self.0
                    .to_doc()
                    .append(Doc::space())
                    .append(self.1.to_doc())
                    .group(),
            )
            .append(")")
    }
}
