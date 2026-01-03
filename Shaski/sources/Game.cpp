#include "../headers/Game.hpp"
#include <cmath>

Game::Game()
    : p1_( 'w', "White" ),
      p2_( 'b', "Black" ),
      current_( &p1_ )
{}

void
Game::reset()
{
    board_.init();
    current_ = &p1_;
}

bool
Game::hasCaptureFrom( const int row, const int col ) const
{
    const char me = board_.getCell( row, col );
    if ( me != current_->getSymbol() ) return false;

    const int cur = row * 8 + col;
    int step[ 2 ], eat[ 2 ];

    if ( me == 'w' ) {
        step[ 0 ] = -7;
        step[ 1 ] = -9;
        eat[ 0 ]  = -14;
        eat[ 1 ]  = -18;
    } else {
        step[ 0 ] =  7;
        step[ 1 ] =  9;
        eat[ 0 ]  = 14;
        eat[ 1 ]  = 18;
    }

    for ( int i = 0; i < 2; ++i ) {
        const int op = cur + step[ i ];
        const int nw = cur + eat[ i ];

        if ( op < 0 || op >= 64 || nw < 0 || nw >= 64 ) continue;

        const int orow = op / 8;
        const int ocol = op % 8;
        const int nrow = nw / 8;
        const int ncol = nw % 8;

        if ( std::abs( ocol - col ) != 1 ||
             std::abs( ncol - col ) != 2 )
            continue;

        const char enemy = board_.getCell( orow, ocol );
        if ( enemy != ' ' &&
             enemy != me &&
             board_.getCell( nrow, ncol ) == ' ' )
            return true;
    }
    return false;
}

bool
Game::hasAnyCapture() const
{
    for ( int r = 0; r < 8; ++r )
        for ( int c = 0; c < 8; ++c )
            if ( hasCaptureFrom( r, c ) )
                return true;
    return false;
}

std::vector<int>
Game::getPossibleNumbers( const int row, const int col ) const
{
    std::vector<int> moves;

    const char me = board_.getCell( row, col );
    if ( me != current_->getSymbol() ) return moves;

    const int cur = row * 8 + col;
    int step[ 2 ], eat[ 2 ];

    if ( me == 'w' ) {
        step[ 0 ] = -7;
        step[ 1 ] = -9;
        eat[ 0 ]  = -14;
        eat[ 1 ]  = -18;
    } else {
        step[ 0 ] =  7;
        step[ 1 ] =  9;
        eat[ 0 ]  = 14;
        eat[ 1 ]  = 18;
    }

    for ( int i = 0; i < 2; ++i ) {
        const int op = cur + step[ i ];
        const int nw = cur + eat[ i ];

        if ( op < 0 || op >= 64 || nw < 0 || nw >= 64 ) continue;

        const int orow = op / 8;
        const int ocol = op % 8;
        const int nrow = nw / 8;
        const int ncol = nw % 8;

        if ( std::abs( ocol - col ) != 1 ||
             std::abs( ncol - col ) != 2 )
            continue;

        const char enemy = board_.getCell( orow, ocol );
        if ( enemy != ' ' &&
             enemy != me &&
             board_.getCell( nrow, ncol ) == ' ' )
            moves.push_back( nw );
    }

    if ( !moves.empty() ) return moves;
    if ( hasAnyCapture() ) return moves;

    for ( int i = 0; i < 2; ++i ) {
        const int nw = cur + step[ i ];
        if ( nw < 0 || nw >= 64 ) continue;

        const int nrow = nw / 8;
        const int ncol = nw % 8;

        if ( std::abs( ncol - col ) != 1 ) continue;

        if ( board_.getCell( nrow, ncol ) == ' ' )
            moves.push_back( nw );
    }
    return moves;
}

bool
Game::makeMove( const int x1,
                const int y1,
                const int x2,
                const int y2 )
{
    const char piece = board_.getCell( x1, y1 );
    if ( piece != current_->getSymbol() ) return false;

    const int from = x1 * 8 + y1;
    const int to   = x2 * 8 + y2;

    const bool capture = std::abs( to - from ) > 9;

    if ( hasAnyCapture() && !capture ) return false;

    if ( capture ) {
        const int er = ( x1 + x2 ) / 2;
        const int ec = ( y1 + y2 ) / 2;
        board_.setCell( er, ec, ' ' );
    }

    board_.setCell( x1, y1, ' ' );
    board_.setCell( x2, y2, piece );

    switchPlayer();
    return true;
}

const Board&
Game::getBoard() const
{
    return board_;
}

char
Game::currentPlayer() const
{
    return current_->getSymbol();
}

void
Game::switchPlayer()
{
    current_ = ( current_ == &p1_ ) ? &p2_ : &p1_;
}

bool
Game::isGameOver() const
{
    for ( int r = 0; r < 8; ++r ) {
        for ( int c = 0; c < 8; ++c ) {
            if ( board_.getCell( r, c ) == current_->getSymbol() ) {
                if ( !getPossibleNumbers( r, c ).empty() )
                    return false;
            }
        }
    }
    return true;
}

char
Game::winner() const
{
    return ( current_ == &p1_ )
             ? p2_.getSymbol()
             : p1_.getSymbol();
}

