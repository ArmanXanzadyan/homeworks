#include "evaluator.hpp"
#include <stdexcept>


static int evaluate_add(const Node* node, const std::unordered_map<std::string, int>& vars)
{
    return evaluate(node->left.get(), vars) + evaluate(node->right.get(), vars);
}

static int evaluate_sub(const Node* node, const std::unordered_map<std::string, int>& vars)
{
    return evaluate(node->left.get(), vars) - evaluate(node->right.get(), vars);
}

static int evaluate_mul(const Node* node, const std::unordered_map<std::string, int>& vars)
{
    return evaluate(node->left.get(), vars) * evaluate(node->right.get(), vars);
}

static int evaluate_div(const Node* node, const std::unordered_map<std::string, int>& vars)
{
    int right = evaluate(node->right.get(), vars);
    if (right == 0) throw std::runtime_error("Division by zero");
    return evaluate(node->left.get(), vars) / right;
}

static int evaluate_val(const Node* node)
{
    return node->value;
}

static int evaluate_var(const Node* node, const std::unordered_map<std::string, int>& vars)
{
    auto it = vars.find(node->var);
    if (it == vars.end()) throw std::runtime_error("Undefined variable: " + node->var);
    return it->second;
}

int evaluate(const Node* tree, const std::unordered_map<std::string, int>& vars)
{
    if (!tree) throw std::runtime_error("Null node in AST");

    switch (tree->type)
    {
        case NodeType::ADD: return evaluate_add(tree, vars);
        case NodeType::SUB: return evaluate_sub(tree, vars);
        case NodeType::MUL: return evaluate_mul(tree, vars);
        case NodeType::DIV: return evaluate_div(tree, vars);
        case NodeType::VAL: return evaluate_val(tree);
        case NodeType::VAR: return evaluate_var(tree, vars);
    }

    return 0;
}
