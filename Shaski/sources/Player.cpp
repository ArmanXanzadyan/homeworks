#include "../headers/Player.hpp"

Player::Player(const char symbol, const std::string& name)
    : symbol_(symbol), name_(name) {}

char
Player::getSymbol() const
{
    return symbol_;
}

const std::string&
Player::getName() const
{
    return name_;
}

