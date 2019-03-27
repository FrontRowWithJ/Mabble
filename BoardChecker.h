#ifndef BOARDCHECKER_H
#define BOARDCHECKER_H
#endif

#ifndef UTIL_H
#include "Util.h"
#endif

#ifndef IS_EQUALS
#define IS_EQUALS(V1, V2) \
    V1.i == V2.i &&V1.j == V2.j
#endif

#ifndef SQUARE
#define SQUARE
typedef struct BoardSquare
{
    char value;
    boolean hasChecked;
    boolean canPlace;
    boolean canRemove;
} Square;
#endif

#ifndef DIRECTION
#define DIRECTION
typedef enum BoardDirection
{
    RIGHT,
    DOWN
} Direction;
#endif

#ifndef LINE
#define LINE
typedef struct BoardLine
{
    Position pos;
    Direction dir;
    char *value;
    size_t len;
} Line;
#endif

void get_statements(int i, int j, Square **matrix, size_t width, size_t height, Position *vector_list, size_t *vector_len);
void clear_board(Square **board, size_t width, size_t height);
void uncheck_board(Square **board, size_t width, size_t height);
void print_vector_list(Position *list, size_t vector_len);
Position *filter_vector(Position *vector_list, size_t vector_len, size_t *new_len);
Line *to_array(LinkedList *llist, size_t *arrayLen);
Line *gen_board_line(Square **board, size_t width, size_t height, Position *listOfPositions, size_t vector_len, size_t *lineLen);
Line get_line(Line *lines, size_t len, int i, int j);

#define IS_BOARD_POS_EQUAL(X, Y) \
    X.pos.i == Y.pos.i &&X.pos.j == Y.pos.j &&X.dir == Y.dir
    