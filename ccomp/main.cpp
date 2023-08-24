#include <stdio.h>
#include <vector>
#include "lexer.hpp"

struct Statement {

};

struct Function {
    int ident;
    int returnIdent;
    Statement statement;
};

struct Program {
    std::vector<Function> functions;
};

struct Parser {
    Lexer* lexer;
    Token currentToken;
    Token peekToken;

    Program parseProgram();
    void next();
    void expect(int type);

    Function parseFunction(Token returnIdent, Token nameIdent);
};

Program Parser::parseProgram() {
    Program prog;
    currentToken = lexer->nextToken();
    peekToken = lexer->nextToken();
    while (currentToken.type != TOKEN_EOF) {
        switch (currentToken.type) {
            case TOKEN_IDENT: {
                Token typeIdent = currentToken;
                expect(TOKEN_IDENT);
                Token nameIdent = currentToken;

                if (peekToken.type == TOKEN_LPAREN) {
                    Function func = parseFunction(typeIdent, nameIdent);
                    prog.functions.push_back(func);
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

    return prog;
}

void Parser::next() {
    currentToken = peekToken;
    peekToken = lexer->nextToken();
}

void Parser::expect(int type) {
    if (peekToken.type != type) {
        printf("expected type: %d, got type %d\n", type, peekToken.type);
    }
    next();
}

Function Parser::parseFunction(Token returnIdent, Token nameIdent) {
    Function func;
    func.ident = nameIdent.value;
    func.returnIdent = returnIdent.value;
    next();
    // LPAREN is current token here
    while (peekToken.type != TOKEN_RPAREN) {
        next();
    }
    next();
    // RPAREN is current Token

    // parse block statement here

    return func;
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

    Program prog = parser.parseProgram();
    printf("Function count: %d\n", prog.functions.size());
}
