#ifndef TILE_H
#define TILE_H

#ifndef UTIL_H
#include "Util.hpp"
#endif
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
    bool isSelected = false;
    TileState state;
    TileType type;
    //The visual parts
    RectangleShape *visuals;
    size_t numOfVisuals;
    float xpos;
    float ypos;
    float width;
    bool isNull;
    // static int beige = 0xE6C194
    Color outLineColor = Color::Black;
    Font font;
    Text text;
    int beige = 0xE6C194;
    Color bgColor = Color(beige >> 16, (beige >> 8) & 0xFF, beige & 0xFF);
    //! This property is defined by the subclass:
    Color textColor; //depending on the type of value
  public:
    // The font object is passed to the user so as to avoid creating multiple uneccessary font objects
    Tile();
    Tile(char value, float xpos, float ypos, float width, Font font, TileType type);
    void gen_tile_visuals();
    void gen_text();
    Tile *select_tile();
    void deselect_tile();
    void place_tile();
    Text get_text();
    RectangleShape *get_rectangles();
    size_t get_number_of_visuals();
    bool is_selected();
    float get_xpos();
    float get_ypos();
    float get_width();
    void draw(RenderWindow *window);
    bool is_null();
    char get_value();
    void set_state(TileState state);
    TileState get_state();
    Color get_text_color();
    bool operator!=(Tile tile);
    void set_is_selected(bool isSelected);
};
#endif