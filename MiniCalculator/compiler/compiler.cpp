#include "compiler.hpp"

#include <stdexcept>


static void compile_node(const Node* node, Program& prog)

{
    if (!node)
        throw std::runtime_error("Null node in AST during compilation");


    switch (node->type)
    {
        case NodeType::VAL: prog.emplace_back(OpCode::PUSH, node->value); break;    
        case NodeType::VAR: prog.emplace_back(OpCode::LOAD, node->var); break;
        case NodeType::ADD: compile_node(node->left.get(), prog); compile_node(node->right.get(), prog); prog.emplace_back(OpCode::ADD); break;
        case NodeType::SUB: compile_node(node->left.get(), prog); compile_node(node->right.get(), prog); prog.emplace_back(OpCode::SUB); break;
        case NodeType::MUL: compile_node(node->left.get(), prog); compile_node(node->right.get(), prog); prog.emplace_back(OpCode::MUL); break;
        case NodeType::DIV: compile_node(node->left.get(), prog); compile_node(node->right.get(), prog); prog.emplace_back(OpCode::DIV); break;
        default: throw std::runtime_error("Unknown node type during compilation");
    }
}


Program compile(const Node* tree)

{
    if (!tree)
        throw std::runtime_error("Null AST");

    Program prog;
    prog.reserve(64);

    compile_node(tree, prog);

    prog.emplace_back(OpCode::PRINT);
    prog.emplace_back(OpCode::HALT);

    return prog;
}

