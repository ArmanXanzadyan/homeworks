#pragma once

 

#include <unordered_map>

#include <string>

 

bool parse_one_variable(const char* str, std::string& name, int& value);

std::unordered_map<std::string, int> parse_all_variables(int argc, char** argv);

 
