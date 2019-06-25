#ifndef BOARD_H
#define BOARD_H

#include "BoardTile.hpp"
#include "Util.hpp"
#include "Eval.hpp"
#include "LinkedList.hpp"

#define IS_EQUALS(V1, V2) \
  V1.i == V2.i &&V1.j == V2.j
#define IS_BOARD_POS_EQUAL(X, Y) \
  X.pos.i == Y.pos.i &&X.pos.j == Y.pos.j &&X.dir == Y.dir
typedef struct MabbleTile
{
  int i;
  int j;
  char value;
  bool operator==(struct MabbleTile rhs);
  char *c_str();
} TileData;
class Board
{
private:
  BoardTile **table;
  float width;
  int rowLen;
  float xPos;
  float yPos;
  Tile nullTile = Tile();

public:
  Board(float width, int rowLen, float xPos, float yPos, const char *fontName, Color textColor, Color bgColor);
  void place_tile(LinkedList<TileData> *placedTiles, Tile *selectedTile, int i, int j);
  void remove_tile(LinkedList<TileData> *placedTiles, int i, int j);
  void clear_board();
  void draw(RenderWindow *window);
  void print_list(LinkedList<TileData> *list);
  BoardTile **get_table();
  float get_width();
  Vector2f get_position();
  int get_rowLen();

private:
  void gen_board(const char *fontName, Color textColor, Color bgColor);
  void set_radii(int i, int j);
  void update_tile_radii(BoardTile *t0, BoardTile *t1, Quadrant a, Quadrant b, Quadrant c, Quadrant d);
  void unset_radii(int i, int j);
};
#endif
