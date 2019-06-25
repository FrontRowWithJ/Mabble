#ifndef BOARDTILE_H
#define BOARDTILE_H

#include "Util.hpp"
#include "Tile.hpp"
#include "RoundedRectangle.hpp"

typedef enum
{
  TILE_EMPTY,
  TILE_FULL_TEMP,
  TILE_FULL_PERM
} BoardTileState;
typedef enum
{
  A,
  B,
  C,
  D
} Quadrant;
//? This class defines the behavior of the Tiles on the board
class BoardTile
{
private:
  float width;
  float xPos;
  float yPos;
  bool isCenter;
  float radius;
  BoardTileState state; //determines wether or not the selected pieces on the board are changeable
  Color textColor;
  Color bgColor;
  Color originalColor;
  RoundedRectangle bg;
  Font textFont;
  Text bgText;
  Tile nullTile = Tile();
  Tile *tile = &nullTile;
  bool isTextGenerated;
  char value;

public:
  BoardTile();
  BoardTile(float width, float xpos, float ypos, Color textColor, Color bgColor, const char *fontName, bool isCenter);
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
  void set_bgColor(Color bgColor);
  void update_text(char value, Color textColor);
  bool is_center();
  char get_value();
  void set_tile(Tile *tile);
  Tile *get_tile();
  void set_tile_to_null();
  bool is_empty();
  void revert_bgColor();
  Vector2f get_position();
  void set_quadrant_radius(float radius, Quadrant q);

private:
  void update_text_position();
  void gen_text();
};

#endif