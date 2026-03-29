#pragma once

#include "instruction.hpp"

#include <unordered_map>

#include <string>


int execute(const Program& prog, const std::unordered_map<std::string, int>& vars);

