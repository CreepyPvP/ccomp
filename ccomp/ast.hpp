#pragma once

#include <vector>

#define EXPRESSION_OP 0
#define EXPRESSION_NUM_LITERAL 1

typedef int ExprRef;
typedef unsigned char Op;

struct OpExpr {
    ExprRef left;
    ExprRef right;
    Op op;
};

union ExprVal {
    int numLiteral;
    OpExpr opExpr;
};

struct Expr {
    unsigned char type;
    ExprVal val;
};


struct Program {
    std::vector<Expr> expressions;

    ExprRef createExpr(Expr expr);
    Expr* getExpr(ExprRef ref);

    ExprRef createOpExpr(ExprRef left, Op op, ExprRef right);
    ExprRef createNumLiteral(int num);
};
