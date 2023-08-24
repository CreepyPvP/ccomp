#include <stdio.h>
#include "./IdentTable.hpp"

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

static int pow(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

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

Token Lexer::nextToken() {
    while (input[index] == '\n' || input[index] == ' ') {
        ++index;
        if (input[index] == '\n') 
            ++currentLine;
    }

    Token result;
    result.index = index;
    result.line = currentLine;

    switch (input[index]) {
        case '=': {
            result.type = TOKEN_EQ;
            break;
        }
        case '+': {
            result.type = TOKEN_PLUS;
            break;
        }
        case '-': {
            result.type = TOKEN_MINUS;
            break;
        }
        case ';': {
            result.type = TOKEN_SEMICOLON;
            break;
        }
        case '(': {
            result.type = TOKEN_LPAREN;
            break;
        }
        case ')': {
            result.type = TOKEN_RPAREN;
            break;
        }
        case '{': {
            result.type = TOKEN_LBRACKET;
            break;
        }
        case '}': {
            result.type = TOKEN_RBRACKET;
            break;
        }
        case ',': {
            result.type = TOKEN_COMMA;
            break;
        }
        case 0: {
            result.type = TOKEN_EOF;
            return result;
        }
        default: {
            if (isLetter()) {
                result.type = TOKEN_IDENT;
                result.value = readIdent();
            } else if (isNumber()) {
                result.type = TOKEN_NUMBER;
                result.value = readNumber();
            }
        }
            
    };
    ++index;

    return result;
}

int Lexer::readIdent() {
    int startIndex = index;
    while (isLetter()) {
        ++index;
    }

    int length = index - startIndex;
    char* ident = input + startIndex;
    int identId = idents.insertOrLookup(ident, length);

    return identId;
};

int Lexer::readNumber() {
    int startIndex = index;
    while (isNumber()) {
        ++index;
    }

    int length = index - startIndex;
    int result = 0;
    for (int i = 0; i < length; ++i) {
        result += (input[startIndex + i] - 48) * pow(10, length - i - 1);
    }

    return result;
}

bool Lexer::isLetter() {
    char value = input[index];
    return (value >= 97 && value <= 122) || (value >= 65 && value <= 90);
};

bool Lexer::isNumber() {
    char value = input[index];
    return value >= 48 && index <= 57;
}

int main() {
    const char* input = "int main() {\nint test = 69;\n}";
    Lexer lexer;
    lexer.input = (char*) input;
    lexer.index = 0;
    lexer.currentLine = 0;
    lexer.idents.capacity = 100;
    lexer.idents.init();


    Token token = lexer.nextToken();
    while (token.type != TOKEN_EOF) {
        printf("%d\n", token.type);
        token = lexer.nextToken();
    }
}
