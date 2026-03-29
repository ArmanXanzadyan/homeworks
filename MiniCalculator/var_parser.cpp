#include "var_parser.hpp"

#include <cctype>

#include <iostream>

 

static bool
read_var_name(const char*& s, std::string& name)
{

    if (!std::isalpha(static_cast<unsigned char>(*s)) && *s != '_') return false;
    name.clear();
    while (*s && *s != '=') {
        name += *s;
        ++s;
    }
    return true;
}

static bool read_var_value(const char*& s, int& value)
{
    if (!std::isdigit(static_cast<unsigned char>(*s))) return false;
    value = 0;
    while (std::isdigit(static_cast<unsigned char>(*s))) {
        value = value * 10 + (*s - '0');
        ++s;
    }
    return true;
}


bool parse_one_variable(const char* str, std::string& name, int& value)
{
    const char* s = str;
    if (!read_var_name(s, name)) {
        std::cerr << "Invalid variable name in: " << str << "\n";
        return false;
    }
    if (*s != '=') {
        std::cerr << "Expected '=' in: " << str << "\n";
        return false;
    }
    ++s;
    if (!read_var_value(s, value)) {
        std::cerr << "Invalid variable value in: " << str << "\n";
        return false;
    }
    return true;
}

 

std::unordered_map<std::string, int> parse_all_variables(int argc, char** argv)
{
    std::unordered_map<std::string, int> vars;
    for (int i = 2; i < argc; ++i) {
        std::string name;
        int value;
        if (parse_one_variable(argv[i], name, value)) vars[std::move(name)] = value;
    }
    return vars;
}


