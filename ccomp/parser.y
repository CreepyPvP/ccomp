%{
    #include <stdio.h>
    #include "parser.hpp"
    #include "ast.hpp"

    int yylex(void);
    void yyerror(const char*);

    static Program prog;
%}

%glr-parser
%left '+' '-'
%left '*' '/'

%token NUM
%define api.value.type {int}

%%
input:
    expr;

expr:
    expr '+' expr { $$ = prog.createOpExpr($1, 0, $3); } |
    expr '-' expr { $$ = prog.createOpExpr($1, 1, $3); } |
    expr '*' expr { $$ = prog.createOpExpr($1, 2, $3); } |
    expr '/' expr { $$ = prog.createOpExpr($1, 3, $3); } |
    NUM;

%%

int yylex (void) {
    const char* input = "4+4";
    static int index = 0;
    char c = input[index];
    if (c) {
        ++index;
        char numValue = c - '0';
        if (numValue <= 9 && numValue >= 0) {
            yylval = prog.createNumLiteral(numValue);
            return NUM;
        }
        return c;
    }
    return YYEOF;
}

void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}
