#pragma once

#include <string>

enum class TokenType {
    NUMBER,
    IDENTIFIER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    LPAREN,
    RPAREN,
    END
};

struct Token {
    TokenType type;
    int number;
    std::string name;

    explicit Token(TokenType t) : type(t), number(0) {}
    Token(TokenType t, int n) : type(t), number(n) {}
    Token(TokenType t, std::string s) : type(t), number(0), name(std::move(s)) {}
};
