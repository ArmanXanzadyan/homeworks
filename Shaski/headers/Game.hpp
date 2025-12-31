#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include <vector>

class Game
{
public:
    Game();
    void reset();

    bool makeMove(int x1, int y1, int x2, int y2);
    std::vector<int> getPossibleNumbers(int row, int col) const;
    bool hasAnyCapture() const;

    bool isGameOver() const;
    char winner() const;
    const Board& getBoard() const;
    char currentPlayer() const;

private:
    void switchPlayer();

private:
    Board board_;
    Player p1_, p2_;
    Player* current_;
};

