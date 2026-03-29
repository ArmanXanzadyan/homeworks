#pragma once

#include <memory>
#include <string>

enum class NodeType {
    ADD,
    SUB,
    MUL,
    DIV,
    VAL,
    VAR
};

struct Node {
    NodeType type;
    int value;
    std::string var;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(int v) : type(NodeType::VAL), value(v) {}
    explicit Node(std::string v) : type(NodeType::VAR), value(0), var(std::move(v)) {}
    Node(NodeType t, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : type(t), value(0), left(std::move(l)), right(std::move(r)) {}
};
