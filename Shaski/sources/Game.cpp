#include "../headers/Game.hpp"
#include <cmath>

Game::Game()
    : p1_('w',"White"),
      p2_('b',"Black"),
      current_(&p1_) {}

void Game::reset() {
    board_.init();
    current_ = &p1_;
}

std::vector<int> Game::getPossibleNumbers(int row,int col) const {
    std::vector<int> moves;
    char me = board_.getCell(row,col);
    if(me != current_->getSymbol() || me == ' ') return moves;

    int cur = row*8 + col;
    int stepDirs[2], eatDirs[2];

    if(me=='w'){ stepDirs[0]=-7; stepDirs[1]=-9; eatDirs[0]=-14; eatDirs[1]=-18; }
    else { stepDirs[0]=7; stepDirs[1]=9; eatDirs[0]=14; eatDirs[1]=18; }

    // capture moves
    for(int i=0;i<2;++i){
        int op = cur + stepDirs[i];
        int nw = cur + eatDirs[i];
        if(op<0||op>=64||nw<0||nw>=64) continue;
        int orow=op/8,ocol=op%8;
        int nrow=nw/8,ncol=nw%8;
        if(abs(ocol-col)!=1 || abs(ncol-col)!=2) continue;
        char enemy = board_.getCell(orow,ocol);
        if(enemy!=' ' && enemy!=me && board_.getCell(nrow,ncol)==' ')
            moves.push_back(nw);
    }
    if(!moves.empty()) return moves;

    // normal moves
    for(int i=0;i<2;++i){
        int nw = cur + stepDirs[i];
        if(nw<0||nw>=64) continue;
        int nrow=nw/8,ncol=nw%8;
        if(abs(ncol-col)!=1) continue;
        if(board_.getCell(nrow,ncol)==' ')
            moves.push_back(nw);
    }
    return moves;
}

bool Game::hasAnyCapture() const {
    for(int r=0;r<8;++r)
        for(int c=0;c<8;++c)
            if(board_.getCell(r,c)==current_->getSymbol())
                if(!getPossibleNumbers(r,c).empty())
                    return true;
    return false;
}

bool Game::makeMove(int x1,int y1,int x2,int y2){
    char piece = board_.getCell(x1,y1);
    if(piece!=current_->getSymbol()) return false;

    int from = x1*8+y1;
    int to = x2*8+y2;
    bool isCapture = abs(to-from) > 9;

    if(hasAnyCapture() && !isCapture) return false;

    if(isCapture){
        int er=(x1+x2)/2, ec=(y1+y2)/2;
        board_.setCell(er,ec,' ');
    }

    board_.setCell(x1,y1,' ');
    board_.setCell(x2,y2,piece);
    switchPlayer();
    return true;
}

bool Game::isGameOver() const {
    for(int r=0;r<8;++r)
        for(int c=0;c<8;++c)
            if(board_.getCell(r,c)==current_->getSymbol())
                if(!getPossibleNumbers(r,c).empty())
                    return false;
    return true;
}

char Game::winner() const { return (current_==&p1_)?p2_.getSymbol():p1_.getSymbol(); }

const Board& Game::getBoard() const { return board_; }
char Game::currentPlayer() const { return current_->getSymbol(); }
void Game::switchPlayer() { current_ = (current_==&p1_)?&p2_:&p1_; }

