#ifndef TILE_H
#define TILE_H

#include "Util.hpp"
#include "TileVisual.hpp"

#ifndef IS_OPERAND
#define IS_OPERAND(X) \
	(X - CHARACTER_OFFSET) >= 0 && (X - CHARACTER_OFFSET) < 10
#endif

#ifndef NUM_OF_STEPS
#define NUM_OF_STEPS 100
#endif
// This class defines the behavior of a Mabble Tile
//? Each rack contains 10 board pieces (5 operands, 4 operators and 1 equal sign);
//! Each piece will have functionality s.t when clicked upon their value will be saved as a global variable
//! When the user clicks the board with again that globally saved piece will be assigned to the board
//! and the piece that the user moved to the board will no longer be able to be selected until the user removes that piece from the board (by right clicking)

typedef enum
{
	STATIC,
	MOUSE_POS,
	TILE_RACK_POS,
	BOARD_POS
} TileDrawState;

typedef enum
{
	ON_RACK,
	ON_BOARD_TEMP,
	ON_BOARD_PERM,
	IS_SELECTED,
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
	char value;
	bool isSelected;
	bool isOperator;
	TileState state;
	TileType type;
	//The visual parts
	float startXPos;
	float startYPos;
	bool isNull;
	Font font;
	Color outLineColor = Color::Black;
	Color bgColor;
	Color textColor;
	TileVisual visuals;
	TileDrawState tds;
	Vector2f step;
	bool setStep;
	int stepsTaken;

public:
	// The font object is passed to the user so as to avoid creating multiple uneccessary font objects
	Tile();
	Tile(float xPos, float yPos, float width, Font font);
	Tile(char value, float xPos, float yPos, float width, Font font);
	Tile *select_tile();
	void deselect_tile();
	void place_tile();
	RectangleShape *get_rectangles();
	bool is_selected();
	void draw(RenderWindow *window, Vector2f mousePos, Vector2f screenPos, Vector2f newPos);
	bool is_null();
	char get_value();
	void set_state(TileState state);
	TileState get_state();
	Color get_textColor();
	bool operator!=(Tile tile);
	void set_isSelected(bool isSelected);
	bool is_operator();
	float get_xPos();
	float get_yPos();
	float get_width();
	Font get_font();
	void set_TileDrawState(TileDrawState tds);
};
#endif