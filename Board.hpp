#ifndef BOARD_H
#define BOARD_H

#include "BoardTile.hpp"
#include "Util.hpp"
#include "Eval.hpp"
#include "TileRack.hpp"
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
  BoardTile ***table;
  float width;
  int rowLen;
  float xPos;
  float yPos;
  Tile nullTile = Tile();
  Tile *selectedTile;

public:
  Board(float width, int rowLen, float xPos, float yPos, Font font, Color textColor, Color bgColor);
  bool place_tile(float mouseX, float mouseY, float screenX, float screenY, LinkedList<TileData> *placedTiles);
  bool remove_tile(float mouseX, float mouseY, float screenX, float screenY, LinkedList<TileData> *placedTiles);
  void clear_board();
  void draw(RenderWindow *window);
  void set_selected_tile(Tile *selectedTile);
  void clear_selected_tile(bool canClear);
  void print_list(LinkedList<TileData> *list);
  BoardTile ***get_table();
  float get_width();
  int get_rowLen();

private:
  void gen_board(Font font, Color textColor, Color bgColor);
};
#endif
