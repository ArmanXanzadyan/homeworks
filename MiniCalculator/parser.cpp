#include "parser.hpp"
#include <iostream>

static size_t pos;

static const Token& current(const std::vector<Token>& tokens) { return tokens[pos]; }
static void advance() { ++pos; }
static bool match(const std::vector<Token>& tokens, TokenType type) { if (current(tokens).type == type) { advance(); return true; } return false; }

static void report_error(const std::vector<Token>& tokens)
{
    if (current(tokens).type == TokenType::END) std::cerr << "Unexpected end of input\n";
    else std::cerr << "Unexpected token\n";
}

static std::unique_ptr<Node> parse_expression(const std::vector<Token>& tokens);
static std::unique_ptr<Node> parse_term(const std::vector<Token>& tokens);
static std::unique_ptr<Node> parse_factor(const std::vector<Token>& tokens);

static std::unique_ptr<Node> parse_factor(const std::vector<Token>& tokens)
{
    const Token& tok = current(tokens);
    if (tok.type == TokenType::NUMBER) { advance(); return std::make_unique<Node>(tok.number); }
    if (tok.type == TokenType::IDENTIFIER) { advance(); return std::make_unique<Node>(tok.name); }
    if (match(tokens, TokenType::LPAREN))
    {
        auto expr = parse_expression(tokens);
        if (!expr) return nullptr;
        if (!match(tokens, TokenType::RPAREN)) { std::cerr << "Expected ')'\n"; return nullptr; }
        return expr;
    }
    report_error(tokens);
    return nullptr;
}

static std::unique_ptr<Node> parse_term(const std::vector<Token>& tokens)
{
    auto left = parse_factor(tokens);
    if (!left) return nullptr;

    while (true)
    {
        NodeType op;
        if (current(tokens).type == TokenType::STAR) op = NodeType::MUL;
        else if (current(tokens).type == TokenType::SLASH) op = NodeType::DIV;
        else break;

        advance();
        auto right = parse_factor(tokens);
        if (!right) return nullptr;
        left = std::make_unique<Node>(op, std::move(left), std::move(right));
    }

    return left;
}

static std::unique_ptr<Node> parse_expression(const std::vector<Token>& tokens)
{
    auto left = parse_term(tokens);
    if (!left) return nullptr;

    while (true)
    {
        NodeType op;
        if (current(tokens).type == TokenType::PLUS) op = NodeType::ADD;
        else if (current(tokens).type == TokenType::MINUS) op = NodeType::SUB;
        else break;

        advance();
        auto right = parse_term(tokens);
        if (!right) return nullptr;
        left = std::make_unique<Node>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<Node> parse(const std::vector<Token>& tokens)
{
    pos = 0;
    auto tree = parse_expression(tokens);
    if (!tree) return nullptr;
    if (current(tokens).type != TokenType::END) { report_error(tokens); return nullptr; }
    return tree;
}
