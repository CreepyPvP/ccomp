#include "lexer.hpp"

static int pow(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

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
                return result;
            } else if (isNumber()) {
                result.type = TOKEN_NUMBER;
                result.value = readNumber();
                return result;
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
