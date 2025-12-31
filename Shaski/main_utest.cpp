#include <gtest/gtest.h>
#include "headers/Game.hpp"

TEST(SudokuTest, PlayGUI)
{
Game game;

    while (true) {
        game.getBoard().print();

        int x1, y1, x2, y2;
        std::cout << "Player " << game.currentPlayer() << " move (fromX fromY toX toY): ";
        std::cin >> x1 >> y1 >> x2 >> y2;

        if (!game.makeMove(x1, y1, x2, y2))
            std::cout << "Invalid move!\n";
    }

}

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

