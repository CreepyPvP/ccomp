#include <stdio.h>
#include "lexer.hpp"

struct Parser {
    Lexer* lexer;
    Token currentToken;
    Token peekToken;

    void parseProgram();
    void next();
    Token expect(int type);

    void parseFunction(Token returnIdent, Token nameIdent);
};

void Parser::parseProgram() {
    currentToken = lexer->nextToken();
    peekToken = lexer->nextToken();
    while (currentToken.type != TOKEN_EOF) {
        switch (currentToken.type) {
            case TOKEN_IDENT: {
                Token typeIdent = currentToken;
                expect(TOKEN_IDENT);
                Token nameIdent = currentToken;

                if (peekToken.type == TOKEN_LPAREN) {
                    parseFunction(typeIdent, nameIdent);
                } else if (peekToken.type == TOKEN_SEMICOLON) {
                    // parse global variable here
                }
                break;
            }
            default: {
                next();
            }
        };
    }
}

void Parser::next() {
    currentToken = peekToken;
    peekToken = lexer->nextToken();
}

Token Parser::expect(int type) {
    if (peekToken.type != type) {
        printf("expected type: %d, got type %d", type, peekToken.type);
    }
    next();
}

void parseFunction(Token returnIdent, Token nameIdent) {
    next();
}

int main() {
    const char* input = "int main() {\nint test = 69;\n}";
    Lexer lexer;
    lexer.input = (char*) input;
    lexer.index = 0;
    lexer.currentLine = 0;
    lexer.idents.capacity = 100;
    lexer.idents.init();

    Parser parser;
    parser.lexer = &lexer;

    parser.parseProgram();
}
