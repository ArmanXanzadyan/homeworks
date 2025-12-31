#pragma once
#include <cstddef>
#include <utility>

class Board {
public:
    static const int SIZE = 8;

    Board();
    void init();
    void print() const;
    void setCell(size_t row, size_t col, char value);
    char getCell(size_t row, size_t col) const;

private:
    std::pair<char, int> board_[SIZE][SIZE];
};

