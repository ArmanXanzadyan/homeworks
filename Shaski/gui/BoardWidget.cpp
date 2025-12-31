#include "BoardWidget.hpp"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

BoardWidget::BoardWidget(Game* game,QWidget* parent)
    : QWidget(parent), game_(game),
      selectedRow_(-1), selectedCol_(-1)
{
    setFixedSize(Board::SIZE*CELL_SIZE,Board::SIZE*CELL_SIZE);
}

void BoardWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    for(int row=0;row<Board::SIZE;++row){
        for(int col=0;col<Board::SIZE;++col){
            QColor cellColor = ((row+col)%2==0)?QColor(180,180,180):QColor(100,100,100);
            painter.fillRect(col*CELL_SIZE,row*CELL_SIZE,CELL_SIZE,CELL_SIZE,cellColor);

            if(row==selectedRow_ && col==selectedCol_){
                painter.setBrush(QColor(0,255,0,120));
                painter.drawRect(col*CELL_SIZE,row*CELL_SIZE,CELL_SIZE,CELL_SIZE);
            }

            char piece = game_->getBoard().getCell(row,col);
            if(piece==' ') continue;

            if(piece=='w'){ painter.setBrush(QColor(255,255,200)); painter.setPen(QColor(150,150,150)); }
            else { painter.setBrush(Qt::black); painter.setPen(Qt::black); }

            painter.drawEllipse(col*CELL_SIZE+8,row*CELL_SIZE+8,CELL_SIZE-16,CELL_SIZE-16);
        }
    }
}

void BoardWidget::mousePressEvent(QMouseEvent* event){
    int col = event->pos().x()/CELL_SIZE;
    int row = event->pos().y()/CELL_SIZE;
    if(row<0||row>=8||col<0||col>=8) return;

    if(selectedRow_==-1){
        if(game_->getBoard().getCell(row,col)==game_->currentPlayer()){
            selectedRow_=row; selectedCol_=col;
        }
    } else {
        auto moves = game_->getPossibleNumbers(selectedRow_,selectedCol_);
        int target = row*8+col;
        for(int v:moves) if(v==target){
            game_->makeMove(selectedRow_,selectedCol_,row,col);
            break;
        }
        selectedRow_=selectedCol_=-1;
    }

    update();

    if(game_->isGameOver()){
        QString text = QString("Winner: %1").arg(game_->winner());
        QMessageBox::information(this,"Game Over",text);
        game_->reset();
        update();
    }
}

