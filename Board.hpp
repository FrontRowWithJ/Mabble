#ifndef BOARD_H
#define BOARD_H

#ifndef UTIL_H
#include "Util.hpp"
#endif

#ifndef EVAL_H
#include "Eval.hpp"
#endif

#define IS_EQUALS(V1, V2) \
    V1.i == V2.i &&V1.j == V2.j
#define IS_BOARD_POS_EQUAL(X, Y) \
    X.pos.i == Y.pos.i &&X.pos.j == Y.pos.j &&X.dir == Y.dir
class Board
{
  public:
    typedef enum
    {
        RIGHT,
        DOWN
    } Direction;

    typedef struct
    {
        Position pos;
        Direction dir;
        string value;
    } Equation;

    typedef struct
    {
        char value;
        bool canPlace;
        bool canRemove;
        bool hasChecked;
    } Square;

  public:
    Square **table;
    size_t width;

  public:
    Board(size_t width);                                                                                        //
    void place_piece(char piece, int i, int j, LinkedList placedPieces);                                        //
    void check_players_turn(LinkedList placedPieces, Equation *boardEquations, size_t len, evalResult_t *code); //
    string gen_incorrect_statement_string(LinkedList incorrectEquatioins);
    Position get_equation_begin_pos(Direction d, int i, int j);
    string get_equation_as_string(Position p, Direction d);
    bool is_idle(LinkedList placedPieces);
    bool is_same_line(LinkedList placedPieces);
    bool is_player_equations_valid(LinkedList equations, LinkedList equationResults, LinkedList placedPieces);
    LinkedList remove_valid_equations(LinkedList equations, LinkedList equationResult);
    int get_min_i(LinkedList placedPieces);
    int get_min_j(LinkedList placedPieces);
    int get_max_i(LinkedList placedPieces);
    int get_max_j(LinkedList placedPieces);
    void set_to_cant_remove(LinkedList placedPieces);
    void get_statements(int i, int j, Position *vector_list, size_t *vector_len);
    void clear_board();
    void uncheck_board();
    void print_vector_list(Position *list, size_t vector_len);
    Position *filter_vector(Position *vector_list, size_t vector_len, size_t *new_len);
    Equation *to_array(LinkedList llist, size_t *arrayLen);
    Equation *gen_board_equation(Position *listOfPositions, size_t vector_len, size_t *equationLen);
    Equation get_equation(Equation *equations, size_t len, int i, int j);
};
#endif