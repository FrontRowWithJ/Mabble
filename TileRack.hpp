#ifndef TILERACK_H
#define TILERACK_H

#include "Util.hpp"
#include "Tile.hpp"

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
  RectangleShape *visuals;
  int numOfVisuals;
  Tile tiles[NUM_OF_TILES];
public:
  TileRack();
  TileRack(float xPos, float yPos, float width, float height, float fgScale);
  void gen_tiles(const char *operands);
  void gen_visuals();
  void draw(RenderWindow *window);
  Tile *select_tile(float mouseX, float mouseY, float screenX, float screenY);
  bool deselect_tile(float mouseX, float mouseY, float screenX, float screenY);
  bool is_tile_selected();
  bool update_tile(int index, char value, bool isNull);
  bool is_tile_pressed(Vector2i mousePos, Vector2i screenPos);
};
#endif