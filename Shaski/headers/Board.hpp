#pragma once
#include <cstddef>
#include <utility>

class Board
{
public:
    static const int SIZE = 8;

    Board();
    void init();
    void print() const;
    void setCell(const size_t row, const size_t col, const char value);
    char getCell(const size_t row, const size_t col) const;

private:
    std::pair<char, int> board_[SIZE][SIZE];
};

