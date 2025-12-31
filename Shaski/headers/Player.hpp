#pragma once
#include <string>

class Player
{
public:
    Player(const char symbol, const std::string& name);

    char getSymbol() const;
    const std::string& getName() const;

private:
    char symbol_;
    std::string name_;
};

