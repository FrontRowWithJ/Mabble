#include "Tile.hpp"

Tile::Tile()
{
    this->isNull = true;
    this->value = EMPTY;
    this->isOperator = false;
    this->isSelected = false;
}

Tile::Tile(float xPos, float yPos, float width, const char *fontName)
{
    this->isNull = true;
    this->value = EMPTY;
    this->startXPos = xPos;
    this->startYPos = yPos;
    isOperator = false;
    this->type = OPERATOR;
    this->state = ON_RACK;
    this->isSelected = false;
    tp = STATIC;
    this->canSetStep = true;
    this->stepsTaken = 0;
    this->bgColor = Color::White;
    this->textColor = bgColor;
    isOperator = true;
    this->fontName = fontName;
    textFont.loadFromFile(fontName);
    this->boardPos = Vector2i(-1, -1);
}

Tile::Tile(char value, float xPos, float yPos, float width, const char *fontName) : Tile(xPos, yPos, width, fontName)
{
    this->isNull = false;
    this->value = value;
    this->type = IS_OPERAND(value) ? OPERAND : value == '=' ? EQUAL_SIGN : OPERATOR;
    this->bg = RoundedRectangle(xPos, yPos, width, width, 10, 7);
    switch (type)
    {
    case OPERAND:
        this->textColor = Color(0x270F36FF);
        isOperator = false;
        break;
    case OPERATOR:
        this->textColor = Color(0xC76B98FF);
        isOperator = true;
        break;
    case EQUAL_SIGN:
        this->textColor = Color(0xFCC3a3FF);
        isOperator = true;
    }
    bg.setFillColor(bgColor);
}

Tile *Tile::select_tile()
{
    if (!isSelected && value != EMPTY)
    {
        isSelected = true;
        tp = MOUSE_POS;
        return this;
    }
    return NULL;
}

void Tile::deselect_tile()
{
    isSelected = false;
    state = ON_RACK;
    tp = TILE_RACK_POS;
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
    return bg.getPosition().x;
}

float Tile::get_yPos()
{
    return bg.getPosition().y;
}

Vector2f Tile::get_positon()
{
    return bg.getPosition();
}

Vector2f Tile::get_size()
{
    return bg.get_size();
}

float Tile::get_width()
{
    return bg.get_width();
}

void Tile::draw(RenderWindow *window, Vector2f mousePos, Vector2f screenPos)
{
    switch (tp)
    {
    case STATIC:
        break;
    case MOUSE_POS:
        set_position(mousePos - screenPos + Vector2f(X_OFFSET, Y_OFFSET) - bg.get_width() / 2);
        break;
    case TILE_RACK_POS:
        if (canSetStep)
        {
            step = (Vector2f(startXPos, startYPos) - bg.getPosition()) / NUM_OF_STEPS;
            canSetStep = false;
        }
        set_position(bg.getPosition() + step);
        if (++stepsTaken == NUM_OF_STEPS)
        {
            deselect_tile();
            stepsTaken = 0;
            set_position(Vector2f(startXPos, startYPos));
            tp = STATIC;
            canSetStep = true;
        }
        break;
    case BOARD_POS:
        if (canSetStep)
        {
            step = (boardCoords - bg.getPosition()) / NUM_OF_STEPS;
            canSetStep = false;
        }
        set_position(bg.getPosition() + step);
        if (++stepsTaken == NUM_OF_STEPS)
        {
            stepsTaken = 0;
            bg.setPosition(boardCoords);
            tp = STATIC;
            canSetStep = true;
        }
    }
    window->draw(bg);
    window->draw(tileText);
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
    // if (isOperator)
    //     deselect_tile();
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

void Tile::set_position_to_tileRack()
{
    tp = TILE_RACK_POS;
}

void Tile::set_position_to_board(Vector2f boardCoords)
{
    this->boardCoords = boardCoords;
    tp = BOARD_POS;
}

Color Tile::get_bgColor()
{
    return bgColor;
}

const char *Tile::get_fontName()
{
    return fontName;
}

void Tile::gen_visuals()
{
    char str[2] = {value, '\0'};
    tileText = Text(str, textFont, bg.get_size().x);
    tileText.setFillColor(textColor);
    FloatRect lb = tileText.getLocalBounds();
    tileText.setOrigin(lb.left, lb.top);
    tileText.setPosition(bg.getPosition() + (bg.get_size() - Vector2f(lb.width, lb.height)) / 2);
}

void Tile::set_position(Vector2f pos)
{
    bg.setPosition(pos);
    FloatRect lb = tileText.getLocalBounds();
    Vector2f tileSize(lb.width, lb.height);
    tileText.setPosition(pos + (bg.get_size() - tileSize) / 2.f);
}

void Tile::set_to_start_position()
{
    set_position(Vector2f(startXPos, startYPos));
}

void Tile::set_boardPos(Vector2i boardPos)
{
    this->boardPos = boardPos;
}

Vector2i Tile::get_boardPos()
{
    return boardPos;
}