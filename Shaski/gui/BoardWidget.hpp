#pragma once
#include <QWidget>
#include "../headers/Game.hpp"

class BoardWidget : public QWidget {
    Q_OBJECT
public:
    static const int CELL_SIZE = 50;

    BoardWidget(Game* game, QWidget* parent=nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    Game* game_;
    int selectedRow_;
    int selectedCol_;
};

