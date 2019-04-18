#ifndef TILERACK_H
#define TILERACK_H

#ifndef UTIL_H
#include "Util.hpp"
#endif

#ifndef TILE_H
#include "Tile.hpp"
#endif
#define NUM_OF_TILES 10
#define NUM_OF_OPERATORS 4
#define NUM_OF_OPERANDS 5
#define NUM_OF_EQUAL_SIGNS 1
//This class acts as the handler for each tile
class TileRack
{
private:
  float xPos;
  float yPos;
  float width;
  float height;
  float fgScale;
  Tile nullTile = Tile();
  RectangleShape *visuals;
  int numOfVisuals;
  Tile tiles[NUM_OF_TILES];
public:
  TileRack();
  TileRack(float xPos, float yPos, float width, float height, float fgScale);
  void gen_tiles(char *operands);
  void gen_visuals();
  void draw(RenderWindow *window);
  Tile *select_tile(float mouseX, float mouseY, float screenX, float screenY);
  bool deselect_tile(float mouseX, float mouseY, float screenX, float screenY);
  bool is_tile_selected();
};
#endif