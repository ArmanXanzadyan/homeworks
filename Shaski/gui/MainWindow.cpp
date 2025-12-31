#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    boardWidget_ = new BoardWidget(&game_,this);
    setCentralWidget(boardWidget_);
    setWindowTitle("Shaski (Checkers)");
    setFixedSize(boardWidget_->size());
}

