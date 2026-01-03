#include "../headers/Board.hpp"
#include <iostream>

Board::Board() 
{
    init();
}

void
Board::init()
{
    int count = 0;
    for(int i = 0;i < SIZE; ++i) {
        for(int j = 0;j < SIZE; ++j) {
            board_[i][j].first = ' ';
            board_[i][j].second = ++count;
            if((i + j) % 2 == 1) {
                if(i < 3) board_[i][j].first = 'b';
                else if(i > 4) board_[i][j].first = 'w';
            }
        }
    }
}

void
Board::print() const
{
    std::cout<<"  0 1 2 3 4 5 6 7\n";
    for(int i = 0; i < SIZE; ++i) {
        std::cout<<i<<" ";
        for(int j = 0;j < SIZE; ++j){
            std::cout << board_[i][j].first << " ";
        }
        std::cout<<"\n";
    }
}

void
Board::setCell(const size_t row, const size_t col, const char value)
{
    board_[row][col].first = value;
}

char
Board::getCell(const size_t row, const size_t col) const
{
    return board_[row][col].first;
}

