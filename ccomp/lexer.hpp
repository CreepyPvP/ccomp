#pragma once

#include "IdentTable.hpp"

#define TOKEN_IDENT 0

#define TOKEN_EQ 1
#define TOKEN_PLUS 2
#define TOKEN_MINUS 3
#define TOKEN_LT 4
#define TOKEN_GT 5
#define TOKEN_NOT 6
#define TOKEN_ASTERISK 7
#define TOKEN_DIVIDE 8

#define TOKEN_LPAREN 10
#define TOKEN_RPAREN 11
#define TOKEN_LBRACKET 12
#define TOKEN_RBRACKET 13
#define TOKEN_SEMICOLON 14
#define TOKEN_COMMA 15

#define TOKEN_STRING 20
#define TOKEN_NUMBER 21

#define TOKEN_IF 30
#define TOKEN_RETURN 31

#define TOKEN_EOF 40

struct Token {
    char type;
    int line;
    int value;
    int index;
};

struct Lexer {
    char* input;
    int index;
    int currentLine;

    IdentTable idents;

    Token nextToken();
    int readIdent();
    int readNumber();

    bool isLetter();
    bool isNumber();
};

