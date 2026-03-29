#include "tokenizer.hpp"
#include <cctype>
#include <iostream>

static void skip_whitespace(const char*& s) { while (*s == ' ' || *s == '\t') ++s; }

static Token read_number(const char*& s)
{
    int value = 0;
    while (std::isdigit(static_cast<unsigned char>(*s))) { value = value * 10 + (*s - '0'); ++s; }
    return Token(TokenType::NUMBER, value);
}

static Token read_identifier(const char*& s)
{
    std::string name;
    while (std::isalnum(static_cast<unsigned char>(*s)) || *s == '_') { name += *s; ++s; }
    return Token(TokenType::IDENTIFIER, std::move(name));
}

static TokenType char_to_token_type(char c)
{
    switch (c)
    {
        case '+': return TokenType::PLUS;
        case '-': return TokenType::MINUS;
        case '*': return TokenType::STAR;
        case '/': return TokenType::SLASH;
        case '(': return TokenType::LPAREN;
        case ')': return TokenType::RPAREN;
        default:  return TokenType::END;
    }
}

std::vector<Token> tokenize(const char* input)
{
    std::vector<Token> tokens;
    tokens.reserve(32);
    const char* s = input;

    while (*s)
    {
        skip_whitespace(s);
        if (!*s) break;

        if (std::isdigit(static_cast<unsigned char>(*s))) tokens.push_back(read_number(s));
        else if (std::isalpha(static_cast<unsigned char>(*s)) || *s == '_') tokens.push_back(read_identifier(s));
        else
        {
            TokenType tt = char_to_token_type(*s);
            if (tt == TokenType::END) { std::cerr << "Unexpected character: " << *s << "\n"; return {}; }
            tokens.emplace_back(tt);
            ++s;
        }
    }

    tokens.emplace_back(TokenType::END);
    return tokens;
}
