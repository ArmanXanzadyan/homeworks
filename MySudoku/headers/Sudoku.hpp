#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <cstddef>
#include <cmath>
#include <utility>

const int SIZE = 9;
const int BLOCKS_IN_ROW = 3;

class Sudoku {
public:
    Sudoku();
    void print() const;
    bool isValid(const size_t row, const size_t col, const int num) const;
    void generateRandomSudoku();
    int getCellValue(const size_t row, const size_t col) const;
    void setCellValue(const size_t row, const size_t col, const int val);


    void play();
    void solveSudoko();
    void generateRandomSudoku(const int percent);
private:
    bool fillGrid(const size_t row, const size_t column);
    int getRandomNumber() const;
    void init();
    int getRightNumber(const size_t row, const size_t col) const;
    bool isHorizontal(const size_t row, const int value) const;
    bool isVertical(const size_t col, const int value) const;
    bool isBlock(const size_t row, const size_t col, const int value) const;
    void printRow() const;
    bool isFull() const;
    int getNumber() const;
    std::pair<int, int> getPath() const;
    bool isValidSudoko() const;
    /*void generateRandomSudoku1(const int percent);
    void generateRandomSudoku2(const int percent);
*/

private:
    std::pair<int, bool> grid_[SIZE][SIZE];
};

#endif // SUDOKU_HPP

