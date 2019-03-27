#ifndef BOARD_H
#define BOARD_H
#endif

#ifndef UTIL_H
#include "Util.h"
#endif

#ifndef EVAL_H
#include "Eval.h"
#endif

#ifndef BOARDCHECKER_H
#include "BoardChecker.h"
#endif

#ifndef SQUARE
#define SQUARE
typedef struct BoardSquare
{
    char value;
    boolean canPlace;
    boolean canRemove;
    boolean hasChecked;
} Square;
#endif

#ifndef BOARD
#define BOARD
typedef struct MabbleBoard
{
    Square **table;
    size_t width;
} Board;
#endif

void place_piece(char piece, Board board, int i, int j, LinkedList placedPieces);
Board init_board(size_t width);
void check_players_turn(LinkedList placedPieces, Board board, Line *boardLines, size_t len, evalResult_t *code);
Position get_equation_begin_pos(Board board, Direction d, int i, int j);
char *get_equation(Board board, Position p, Direction d);
boolean is_idle(Board board, LinkedList placedPieces);
boolean is_player_equations_valid(Board board, LinkedList *equations, LinkedList *equationResults, LinkedList *placedPieces);
LinkedList remove_valid_equations(LinkedList *equations, LinkedList *equationResult);
int get_min_i(LinkedList placedPieces);
int get_min_j(LinkedList placedPieces);
int get_max_i(LinkedList placedPieces);
int get_max_j(LinkedList placedPieces);
void setToCantRemove(LinkedList placedPieces, Board board);