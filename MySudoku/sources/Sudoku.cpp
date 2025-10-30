#include "headers/Sudoku.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <filesystem> // C++17 required for path checks
#include <SFML/Graphics.hpp>
Sudoku::Sudoku()
{
    std::srand(std::time(0));
    init();
}
int
Sudoku::getRandomNumber() const
{
    return std::rand() % SIZE;
}
void
Sudoku::init()
{
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            grid_[i][j].first = 0;
            grid_[i][j].second = false;
        }
    }
}
int
Sudoku::getCellValue(const size_t row, const size_t col) const
{
    return grid_[row][col].first;
}
void
Sudoku::setCellValue(const size_t row, const size_t col, const int val)
{
    grid_[row][col].first = val;
}
void
Sudoku::printRow() const
{
    const size_t count = BLOCKS_IN_ROW - 1;
    for (size_t i = 0; i < count; ++i) {
        std::cout << "------+";
    }
    std::cout << "------\n";
}
void
Sudoku::print() const
{
    const size_t blockSize = 3;
    for (size_t i = 0; i < SIZE; ++i) {
        if (i % blockSize == 0 && i != 0) {
            printRow();
        }
        for (size_t j = 0; j < SIZE; ++j) {
            if (0 == j % blockSize && j != 0) {
                std::cout << "| ";
            }
            if (0 == grid_[i][j].first) { std::cout << ". "; continue; }
            std::cout << grid_[i][j].first << ' ';
        }

        std::cout << '\n';
    }
}
bool
Sudoku::isHorizontal(const size_t row, const int value) const
{
    for (size_t i = 0; i < SIZE; ++i) { if (grid_[row][i].first == value) return false; }
    return true;
}
bool
Sudoku::isVertical(const size_t col, const int value) const
{
    for (size_t i = 0; i < SIZE; ++i) { if (grid_[i][col].first == value) return false; }
    return true;
}
bool
Sudoku::isBlock(const size_t row, const size_t col, const int value) const
{
    const size_t startRow = (row / BLOCKS_IN_ROW) * BLOCKS_IN_ROW;
    const size_t startCol = (col / BLOCKS_IN_ROW) * BLOCKS_IN_ROW;
    for (size_t i = startRow; i < startRow + BLOCKS_IN_ROW; ++i) {
        for (size_t j = startCol; j < startCol + BLOCKS_IN_ROW; ++j) {
            if (grid_[i][j].first == value) return false;
        }
    }
    return true;
}
bool
Sudoku::isValid(const size_t row, const size_t col, const int number) const
{
    return isHorizontal(row, number)
        && isVertical(col, number)
        && isBlock(row, col, number);
}
int
Sudoku::getRightNumber(const size_t row, const size_t col) const
{
    int k = getRandomNumber() + 1;
    for (int attempts = 0; attempts < SIZE; ++attempts) {
        if (isValid(row, col, k)) return k;
        k = (k % SIZE) + 1;
    }
    return 0;
}
void
Sudoku::generateRandomSudoku(const int percent)
{
    const size_t count = SIZE * SIZE * (100 - percent) / 100;
    fillGrid(0, 0);
    for (size_t i = 0; i < count;) {
        const int row = getRandomNumber();
        const int column = getRandomNumber();
        if (grid_[row][column].first != 0) { grid_[row][column].first = 0; grid_[row][column].second = true; ++i; }
    }
}
bool
Sudoku::isFull() const
{
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            if (0 == grid_[i][j].first) return false;

        }
    }
    return true;
}
/*
bolor tvery voronw heto piti dnenq second = true;
*/
std::pair<int, int>
Sudoku::getPath() const
{
    std::cout << "Input (row, column): ";
    int row, column;
    std::cin >> row >> column;
    if (row < 1 || row > SIZE || column < 1 || column > SIZE) {
        std::cout << "Try again\n";
        getNumber();
    }
    return std::make_pair(row, column);
}
int
Sudoku::getNumber() const
{
    std::cout << "Input number: ";
    int k;
    std::cin >> k;
    return k;
}
bool
Sudoku::isValidSudoko() const
{
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            if (!isValid(i, j, grid_[i][j].first)) return false;
        }
    }
    return true;
}

void
Sudoku::play()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Sudoku");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Font not found!" << std::endl;
        return;
    }

    const int cellSize = 600 / SIZE;
    sf::RectangleShape cell(sf::Vector2f(cellSize - 2.f, cellSize - 2.f));
    cell.setOutlineColor(sf::Color::Black);
    cell.setOutlineThickness(1.f);

    int selectedRow = -1;
    int selectedCol = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                selectedCol = event.mouseButton.x / cellSize;
                selectedRow = event.mouseButton.y / cellSize;
            }
            if (event.type == sf::Event::TextEntered && selectedRow >= 0 && selectedCol >= 0) {
                if (event.text.unicode >= '1' && event.text.unicode <= '9') {
                    const int number = event.text.unicode - '0';
                    if(isValid(selectedRow, selectedCol, number)) {
                        setCellValue(selectedRow, selectedCol, number);
                    }
                }
            }
        }
        window.clear(sf::Color(200, 200, 200));

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                cell.setPosition(j * cellSize + 1.f, i * cellSize + 1.f);
                cell.setFillColor(getCellValue(i, j) == 0 ? sf::Color(245, 245, 245) : sf::Color(220, 250, 255));
                if (i == selectedRow && j == selectedCol) {
                    cell.setFillColor(sf::Color(200, 200, 255));
                }

                window.draw(cell);

                int val = getCellValue(i, j);
                if (val != 0) {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(std::to_string(val));
                    text.setCharacterSize(40);
                    text.setFillColor(sf::Color::Black);
                    text.setPosition(j * cellSize + 18.f, i * cellSize + 5.f);
                    window.draw(text);
                }
            }
        }
        for (int i = 0; i <= SIZE; ++i) {
            const int thick = (i % 3 == 0) ? 3 : 1;
            sf::RectangleShape h(sf::Vector2f(600, thick));
            h.setPosition(0, i * cellSize);
            h.setFillColor(sf::Color::Black);
            window.draw(h);

            sf::RectangleShape v(sf::Vector2f(thick, 600));
            v.setPosition(i * cellSize, 0);
            v.setFillColor(sf::Color::Black);
            window.draw(v);
        }
        window.display();
        if (isFull() && isValidSudoko()) {
            std::cout << "Bravo you win!\n";
            window.close();
        }
    }
}

bool
Sudoku::fillGrid(const size_t row, const size_t col)
{
    if (row == SIZE) return true;
    const size_t nextRow = (col == SIZE - 1) ? row + 1 : row;
    const size_t nextCol = (col == SIZE - 1) ? 0 : col + 1;
    if (grid_[row][col].first != 0) return fillGrid(nextRow, nextCol);
    int numbers[SIZE];
    for (int i = 0; i < SIZE; ++i) numbers[i] = i + 1;
    for (int i = 0; i < SIZE; ++i) {
        const int j = std::rand() % SIZE;
        std::swap(numbers[i], numbers[j]);
    }

    for (int i = 0; i < SIZE; ++i) {
        const int num = numbers[i];
        if (isValid(row, col, num)) {
            grid_[row][col].first = num;
            if (fillGrid(nextRow, nextCol)) return true;
            grid_[row][col].first = 0;
        }
    }
    return false;
}
void
Sudoku::solveSudoko()
{
    fillGrid(0, 0);
}
/*
void
Sudoku::generateRandomSudoku()
{
    int k = getRandomNumber() + 1;
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            grid_[i][j].first = (k++ % SIZE) + 1;
        }
        k -= 3;
    }
}
void
Sudoku::generateRandomSudoku()
{
    int k = getRandomNumber() + 1;
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            grid_[i][j].first = (k++ % SIZE) + 1;
        }
        k -= 3;
    }
}
void
Sudoku::generateRandomSudoku1(const int percent)
{
///    assert(percent <= 70);
    const size_t count = SIZE * SIZE * percent / 100;
    for (size_t t = 0; t < count;) {
        const size_t row = getRandomNumber();
        const size_t col = getRandomNumber();
        const int num = getRandomNumber() + 1;
        if (grid_[row][col].first == 0 && isValid(row, col, num)) {
            grid_[row][col].first = num;
            ++t;
        }
    }
}
void
Sudoku::generateRandomSudoku2(const int percent)
{
    ///assert(percent <= 70);
    const size_t count = SIZE * SIZE * percent / 100;
    for (size_t t = 0; t < count;) {

        const size_t row = getRandomNumber();
        const size_t col = getRandomNumber();
        if (grid_[row][col].first == 0) {
            grid_[row][col].first = getRightNumber(row, col);
            ++t;
        }
    }
}
*/
