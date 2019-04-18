#ifndef BOARD_H
#define BOARD_H

#ifndef BOARDTILE_H
#include "BoardTile.hpp"
#endif

#ifndef UTIL_H
#include "Util.hpp"
#endif

#ifndef EVAL_H
#include "Eval.hpp"
#endif

#ifndef TILERACK_H
#include "TileRack.hpp"
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
        DOWN,
    } Direction;

    typedef struct
    {
        Position pos;
        Direction dir;
        string value;
    } Equation;

    typedef struct
    {
        int i;
        int j;
        char value;
    } TileData;

  private:
    BoardTile **table;
    float width;
    int rowWidth;
    float xPos;
    float yPos;
    Tile nullTile = Tile();
    Tile *selectedTile;

  public:
    Board(float width, int rowWidth, float xPos, float yPos, Font font, Color textColor, Color bgColor);
    bool place_tile(float mouseX, float mouseY, float screenX, float screenY, LinkedList *placedTiles);
    bool remove_tile(float mouseX, float mouseY, float screenX, float screenY, LinkedList *placedTiles);
    //* checkBoard
    void check_players_turn(LinkedList *placedPieces, Equation *boardEquations, int len, evalResult_t *code);
    void clear_board();
    void draw(RenderWindow *window);
    void set_selected_tile(Tile *selectedTile);
    void clear_selected_tile(bool canClear);
    static int compare(void *a, void *b);
    static char *to_string(void *a);
    void print_list(LinkedList *list);
    BoardTile **get_table();

  private:
    void gen_board(Font font, Color textColor, Color bgColor);
};
#endif
