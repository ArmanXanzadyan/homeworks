#pragma once
#include <QMainWindow>
#include "BoardWidget.hpp"
#include "../headers/Game.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent=nullptr);

private:
    Game game_;
    BoardWidget* boardWidget_;
};

