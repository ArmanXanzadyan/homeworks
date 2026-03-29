#pragma once


#include "Node.hpp"

#include <unordered_map>

#include <string>


int evaluate(const Node* tree, const std::unordered_map<std::string, int>& vars);

 
