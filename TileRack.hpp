#ifndef TILERACK_H
#define TILERACK_H

#include "Util.hpp"
#include "Board.hpp"
#include "Tile.hpp"

#define NUM_OF_TILES 10
#define NUM_OF_OPERATORS 4
#define NUM_OF_OPERANDS 5
#define NUM_OF_EQUAL_SIGNS 1
//This class acts as the handler for each tile
using namespace vector_op;
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
	void gen_tiles(const char *operands, const char *fontName);
	void gen_visuals();
	void draw(RenderWindow *window, Vector2f mousePos, Vector2f screenPos);
	Tile *select_tile(Vector2f mousePos, Vector2f screenPos);
	bool is_tile_selected();
	bool update_tile(int index, char value, bool isNull);
	void snap_to_board(Board *gameBoard, LinkedList<TileData> *placedTiles);
	void reset_TileRack_Position();
};
#endif