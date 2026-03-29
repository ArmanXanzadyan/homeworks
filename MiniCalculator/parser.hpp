#pragma once

 

#include "Node.hpp"

#include "Token.hpp"

#include <vector>

#include <memory>


std::unique_ptr<Node> parse(const std::vector<Token>& tokens);
