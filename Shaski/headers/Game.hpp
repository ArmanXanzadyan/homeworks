#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include <vector>

class Game
{
public:
    Game();
    void reset();

    bool hasCaptureFrom(const int row, const int col) const;
    bool makeMove(const int x1, const int y1, const int x2, const int y2);
    std::vector<int> getPossibleNumbers(const int row, const int col) const;
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

