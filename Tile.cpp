#include "Tile.hpp"

Tile::Tile()
{
    this->isNull = true;
    this->value = EMPTY;
    this->isOperator = false;
    this->isSelected = false;
}

Tile::Tile(float xPos, float yPos, float width, Font font)
{
    this->isNull = true;
    this->value = EMPTY;
    this->startXPos = xPos;
    this->startYPos = yPos;
    this->font = font;
    isOperator = false;
    this->type = OPERATOR;
    this->state = ON_RACK;
    this->isSelected = false;
    this->tds = STATIC;
    this->setStep = true;
    this->stepsTaken = 0;
    int beige = 0xE6C194;
    bgColor = Color(beige >> 16, (beige >> 8) & 0xFF, beige & 0xFF);
    this->textColor = bgColor;
    isOperator = true;
}

Tile::Tile(char value, float xPos, float yPos, float width, Font font)
{
    this->startXPos = xPos;
    this->startYPos = yPos;
    this->value = value;
    this->font = font;
    this->type = IS_OPERAND(value) ? OPERAND : value == '=' ? EQUAL_SIGN : OPERATOR;
    this->isNull = false;
    this->state = ON_RACK;
    this->isSelected = false;
    this->tds = STATIC;
    this->setStep = true;
    this->stepsTaken = 0;
    this->visuals = TileVisual(xPos, yPos, width, width, 10, new char[2]{value, '\0'}, font, true);
    string s = string(new char[2]{value, '\0'});
    Text t(s, font, width);
    this->visuals.gen_text(t);
    int beige = 0xE6C194;
    bgColor = Color(beige >> 16, (beige >> 8) & 0xFF, beige & 0xFF);
    Color purple = Color(128, 0, 128, 255);
    switch (type)
    {
    case OPERAND:
        this->textColor = purple;
        isOperator = false;
        break;
    case OPERATOR:
        this->textColor = Color::Red;
        isOperator = true;
        break;
    case EQUAL_SIGN:
        this->textColor = Color::Black;
        isOperator = true;
    }
    this->visuals.set_text_color(this->textColor);
    this->visuals.set_bg_color(bgColor);
}

Tile *Tile::select_tile()
{
    if (!isSelected && value != EMPTY)
    {
        isSelected = true;
        visuals.set_alpha(MAX_ALPHA / 3);
        state = IS_SELECTED;
        return this;
    }
    return NULL;
}

void Tile::deselect_tile()
{
    isSelected = false;
    visuals.set_alpha(MAX_ALPHA);
    state = ON_RACK;
}

void Tile::place_tile()
{
    state = ON_BOARD_TEMP;
}

bool Tile::is_selected()
{
    return isSelected;
}

float Tile::get_xPos()
{
    return visuals.get_position().x;
}

float Tile::get_yPos()
{
    return visuals.get_position().y;
}

float Tile::get_width()
{
    return visuals.get_width();
}

void Tile::draw(RenderWindow *window, Vector2f mousePos, Vector2f screenPos, Vector2f boardPos)
{
    switch (tds)
    {
    case STATIC:
        break;
    case MOUSE_POS:
        visuals.set_position(mousePos - screenPos + Vector2f(X_OFFSET, Y_OFFSET));
        break;
    case TILE_RACK_POS:
        if (setStep)
        {
            step = (Vector2f(startXPos, startYPos) - visuals.get_position()) / NUM_OF_STEPS;
            setStep = false;
        }
        visuals.set_position(visuals.get_position() + step);
        if (++stepsTaken == NUM_OF_STEPS)
        {
            stepsTaken = 0;
            visuals.set_position(startXPos, startYPos);
            tds = STATIC;
            setStep = true;
        }
        break;

    case BOARD_POS:
        if (setStep)
        {
            step = (boardPos - visuals.get_position()) / NUM_OF_STEPS;
            setStep = false;
        }
        visuals.set_position(visuals.get_position() + step);
        if (++stepsTaken == NUM_OF_STEPS)
        {
            stepsTaken = 0;
            visuals.set_position(boardPos);
            tds = STATIC;
            setStep = true;
        }
    }
    printf("Tile::draw0\n");
    visuals.draw(window);
    printf("Tile::draw1\n");
}

bool Tile::is_null()
{
    return isNull;
}

char Tile::get_value()
{
    return value;
}

void Tile::set_state(TileState _state)
{
    state = _state;
    if (isOperator)
        deselect_tile();
}

TileState Tile::get_state()
{
    return state;
}

Color Tile::get_textColor()
{
    return textColor;
}

bool Tile::operator!=(Tile tile)
{
    float xPos = get_xPos(), yPos = get_yPos();
    return value != tile.value || xPos != tile.get_xPos() || yPos != tile.get_yPos();
}

void Tile::set_isSelected(bool isSelected)
{
    this->isSelected = isSelected;
}

bool Tile::is_operator()
{
    return isOperator;
}

Font Tile::get_font()
{
    return font;
}

void Tile::set_TileDrawState(TileDrawState tds)
{
    this->tds = tds;
}