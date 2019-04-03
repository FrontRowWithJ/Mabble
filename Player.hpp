#ifndef PLAYER_H
#define PLAYER_H

#ifndef UTIL_H
#include "Util.hpp"
#endif

#ifndef BOARD_H
#include "Board.hpp"
#endif

#define PIECE_COUNT 10
#define TOTAL_PIECES 100

class Player
{
  public:
    typedef struct
    {
        bool isPlaced;
        char value;
    } Piece;

  public:
    bool isTurn;
    int numOfTurns;
    long score;
    LinkedList placedPieces;
    Board::Equation *equations;
    Piece currentPieces[PIECE_COUNT];
    Piece pieceBag[TOTAL_PIECES];

  public:
    LinkedList getPlacedPieces();
};
#endif