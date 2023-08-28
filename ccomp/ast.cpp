#include "ast.hpp"
#include <stdio.h>

void Program::print() {
    for (int i = 0; i < expressions.size(); ++i) {
        auto expr = expressions[i];
        printf("Expr %d\n", i);
        switch (expr.type) {
            case EXPRESSION_OP: {
                printf(
                    "\tleft: %d\n\tright: %d\n\top: %d\n", 
                    expr.val.opExpr.left,
                    expr.val.opExpr.right,
                    expr.val.opExpr.op
                );
                break;
            }
            case EXPRESSION_NUM_LITERAL: {
                printf("\tnum: %d\n", expr.val.numLiteral);
            };
        }
        printf("\n");
    }
}

ExprRef Program::createExpr(Expr expr) {
    ExprRef index = expressions.size();
    expressions.push_back(expr);
    return index;
}

Expr* Program::getExpr(ExprRef ref) {
    return &expressions[ref];
}

ExprRef Program::createOpExpr(ExprRef left, Op op, ExprRef right) {
    Expr expr;
    expr.type = EXPRESSION_OP;
    expr.val.opExpr.left = left;
    expr.val.opExpr.right = right;
    expr.val.opExpr.op = op;
    return createExpr(expr);
}

ExprRef Program::createNumLiteral(int num) {
    Expr expr;
    expr.type = EXPRESSION_NUM_LITERAL;
    expr.val.numLiteral = num;
    return createExpr(expr);
}
