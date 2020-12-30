use cytosol_syntax::{InfixOperator, PrefixOperator};
use id_arena::Id;

pub type TypeId = Id<Type>;

pub enum Type {
    Int,
    String,
    Atom(AtomId),
}

pub type AtomId = Id<Atom>;

pub struct Atom {
    pub name: Identifier,
    pub field_names: Vec<Identifier>,
    pub fields: Vec<TypeId>,
}

pub type FieldIndex = usize;

pub enum Product {
    Enzyme {
        quantity: usize,
        enzyme: EnzymeId,
    },
    Atom {
        quantity: usize,
        atom: AtomId,
        arguments: Vec<ExpressionId>,
    },
}

pub enum Bind {
    None,
    Quantity(usize),
    Named(Identifier),
}

pub enum BindType {
    Atom(AtomId),
    Enzyme(EnzymeId),
}

pub type EnzymeId = Id<Enzyme>;

pub struct Enzyme {
    pub name: Identifier,
    pub binds: Vec<(Bind, BindType)>,
    pub products: Vec<Product>,
}

pub type ExternId = Id<Extern>;

pub struct Extern {
    pub name: Identifier,
    pub parameters: Vec<TypeId>,
}

pub type GeneId = Id<Gene>;

pub struct Gene {
    pub binds: Vec<(Bind, BindType)>,
    pub body: Vec<GeneStatementId>,
}

pub type GeneStatementId = Id<GeneStatement>;

pub enum GeneStatement {
    Call {
        ext: ExternId,
        arguments: Vec<ExpressionId>,
    },
    Express(Product),
}

pub type ExpressionId = Id<Expression>;

pub type Identifier = String;

#[derive(Debug, Clone)]
pub enum Expression {
    IntegerLiteral(usize),
    StringLiteral(String),
    Variable(Identifier),
    FieldAccess {
        base: ExpressionId,
        field: FieldIndex,
    },
    PrefixOp {
        op: PrefixOperator,
        expr: ExpressionId,
    },
    InfixOp {
        op: InfixOperator,
        args: [ExpressionId; 2],
    },
}
