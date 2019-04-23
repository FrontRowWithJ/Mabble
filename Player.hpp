#ifndef PLAYER_H
#define PLAYER_H

#include "Util.hpp"
#include "Board.hpp"

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
    Piece currentPieces[PIECE_COUNT];
    Piece pieceBag[TOTAL_PIECES];

  public:
    LinkedList getPlacedPieces();
};
#endif