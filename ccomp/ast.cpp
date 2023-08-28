#include "ast.hpp"

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
