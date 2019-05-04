#ifndef BOARDTILE_H
#define BOARDTILE_H

#include "Tile.hpp"
#include "Util.hpp"

typedef enum
{
  TILE_EMPTY,
  TILE_FULL_TEMP,
  TILE_FULL_PERM
} BoardTileState;
//? This class defines the behavior of the Tiles on the board
class BoardTile
{
private:
  float width;
  float xPos;
  float yPos;
  bool isCenter;
  BoardTileState state; //determines wether or not the selected pieces on the board are changeable
  Text tileText;
  Color textColor;
  Font font;
  Color bgColor;
  RectangleShape *visuals;
  int numOfVisuals;
  Tile nullTile = Tile();
  Tile *tile = &nullTile;
  char value;

public:
  BoardTile();
  BoardTile(float width, float xpos, float ypos, Font font, Color textColor, Color bgColor, bool isCenter);
  void gen_visuals();
  void draw(RenderWindow *window);
  BoardTileState get_state();
  void set_state(BoardTileState state);
  float get_width();
  void set_width(float width);
  float get_xPos();
  void set_xPos(float xPos);
  float get_yPos();
  void set_yPos(float yPos);
  void gen_text();
  void update_text(char value, Color textColor);
  bool is_center();
  char get_value();
  void set_tile(Tile *tile);
  Tile *get_tile();
  void set_tile_to_null();
};

#endif