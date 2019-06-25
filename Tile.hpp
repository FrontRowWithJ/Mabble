#ifndef TILE_H
#define TILE_H

#include "Util.hpp"
#include "RoundedRectangle.hpp"

#ifndef IS_OPERAND
#define IS_OPERAND(X) \
	(X - CHARACTER_OFFSET) >= 0 && (X - CHARACTER_OFFSET) < 10
#endif

#ifndef NUM_OF_STEPS
#define NUM_OF_STEPS 30
#endif
// This class defines the behavior of a Mabble Tile
//? Each rack contains 10 board pieces (5 operands, 4 operators and 1 equal sign);
//! Each piece will have functionality s.t when clicked upon their value will be saved as a global variable
//! When the user clicks the board with again that globally saved piece will be assigned to the board
//! and the piece that the user moved to the board will no longer be able to be selected until the user removes that piece from the board (by right clicking)

using namespace vector_op;
typedef enum
{
	ON_RACK,
	ON_BOARD_TEMP,
	ON_BOARD_PERM
} TileState;

typedef enum
{
	OPERATOR,
	OPERAND,
	EQUAL_SIGN
} TileType;

class Tile
{
private:
	typedef enum
	{
		STATIC,
		MOUSE_POS,
		TILE_RACK_POS,
		BOARD_POS,
	} TilePosition;

private:
	char value;
	bool isSelected;
	bool isOperator;
	TileState state;
	TileType type;
	//The visual parts
	float startXPos;
	float startYPos;
	bool isNull;
	Color outLineColor = Color::Black;
	Color bgColor;
	Color textColor;
	Text tileText;
	Font textFont;
	RoundedRectangle bg;
	TilePosition tp;
	Vector2f step;
	Vector2f boardCoords;
	Vector2i boardPos;
	bool canSetStep;
	int stepsTaken;
	const char *fontName;

public:
	// The font object is passed to the user so as to avoid creating multiple uneccessary font objects
	Tile();
	Tile(float xPos, float yPos, float width, const char *fontName);
	Tile(char value, float xPos, float yPos, float width, const char *fontName);
	Tile *select_tile();
	void deselect_tile();
	void place_tile();
	RectangleShape *get_rectangles();
	bool is_selected();
	void draw(RenderWindow *window, Vector2f mousePos, Vector2f screenPos);
	bool is_null();
	char get_value();
	void set_state(TileState state);
	TileState get_state();
	Color get_textColor();
	Color get_bgColor();
	bool operator!=(Tile tile);
	void set_isSelected(bool isSelected);
	bool is_operator();
	float get_xPos();
	float get_yPos();
	float get_width();
	Vector2f get_positon();
	Vector2f get_size();
	void set_position_to_tileRack();
	void set_position_to_board(Vector2f boardCoords);
	const char *get_fontName();
	void gen_visuals();
	void set_to_start_position();
	void set_boardPos(Vector2i boardPos);
	Vector2i get_boardPos();

private:
	void set_position(Vector2f pos);
};
#endif