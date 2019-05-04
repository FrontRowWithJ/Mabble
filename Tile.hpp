#ifndef TILE_H
#define TILE_H

#include "Util.hpp"
#define IS_OPERAND(X) \
  (X - CHARACTER_OFFSET) >= 0 && (X - CHARACTER_OFFSET) < 10
// This class defines the behavior of a Mabble Tile
//? Each rack contains 10 board pieces (5 operands, 4 operators and 1 equal sign);
//! Each piece will have functionality s.t when clicked upon their value will be saved as a global variable
//! When the user clicks the board with again that globally saved piece will be assigned to the board
//! and the piece that the user moved to the board will no longer be able to be selected until the user removes that piece from the board (by right clicking)

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
    RectangleShape *visuals;
    size_t numOfVisuals;
    float xPos;
    float yPos;
    float width;
    bool isNull;
    Color outLineColor = Color::Black;
    Font font;
    Text text;
    Color bgColor;
    //! This property is defined by the subclass:
    Color textColor; //depending on the type of value
  public:
    // The font object is passed to the user so as to avoid creating multiple uneccessary font objects
    Tile();
    Tile(float xPos, float yPos, float width, Font font);
    Tile(char value, float xPos, float yPos, float width, Font font);
    void gen_tile_visuals();
    void gen_text();
    Tile *select_tile();
    void deselect_tile();
    void place_tile();
    Text get_text();
    RectangleShape *get_rectangles();
    size_t get_numOfVisuals();
    bool is_selected();
    float get_xpos();
    float get_ypos();
    void draw(RenderWindow *window);
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
};
#endif