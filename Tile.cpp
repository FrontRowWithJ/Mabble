#include "Tile.hpp"

Tile::Tile()
{
    this->isNull = true;
    this->value = EMPTY;
    isOperator = false;
    this->isSelected = false;
}

Tile::Tile(float xPos, float yPos, float width, Font font)
{
    this->isNull = true;
    this->value = EMPTY;
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->font = font;
    isOperator = false;
    this->type = OPERATOR;
    this->state = ON_RACK;
    this->isSelected = false;
    int beige = 0xE6C194;
    bgColor = Color(beige >> 16, (beige >> 8) & 0xFF, beige & 0xFF);
    this->textColor = bgColor;
    isOperator = true;
}

Tile::Tile(char value, float xPos, float yPos, float width, Font font)
{
    this->value = value;
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->font = font;
    this->type = IS_OPERAND(value) ? OPERAND : value == '=' ? EQUAL_SIGN : OPERATOR;
    this->isNull = false;
    this->state = ON_RACK;
    this->isSelected = false;
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
}

void Tile::gen_text()
{
    text.setFont(font);
    text.setFillColor(textColor);
    text.setString(new char[2]{value, '\0'});
    text.setCharacterSize(width);
    FloatRect lb = text.getLocalBounds();
    text.setOrigin(lb.left - xPos - (width - lb.width) / 2.f, lb.top - yPos - (width - lb.height) / 2.f);
}

Text Tile::get_text()
{
    return text;
}

RectangleShape *Tile::get_rectangles()
{
    return visuals;
}

Tile *Tile::select_tile()
{
    if (!isSelected && value != EMPTY)
    {
        isSelected = true;
        //reduce the opacity of the object
        for (int i = 0; i < numOfVisuals; i++)
        {
            Color fc = visuals[i].getFillColor();
            visuals[i].setFillColor(Color(fc.r, fc.g, fc.b, fc.a / 3));
        }
        text.setFillColor(Color(textColor.r, textColor.g, textColor.b, textColor.a / 3));
        state = IS_SELECTED;
        return this;
    }
    return NULL;
}

void Tile::deselect_tile()
{
    isSelected = false;
    for (int i = 0; i < numOfVisuals; i++)
    {
        Color fc = visuals[i].getFillColor();
        visuals[i].setFillColor(Color(fc.r, fc.g, fc.b, 255));
    }
    text.setFillColor(Color(textColor.r, textColor.g, textColor.b, 255));
    state = ON_RACK;
}

void Tile::place_tile()
{
    state = ON_BOARD_TEMP;
}

size_t Tile::get_numOfVisuals()
{
    return this->numOfVisuals;
}

bool Tile::is_selected()
{
    return isSelected;
}

float Tile::get_xpos()
{
    return xPos;
}

float Tile::get_ypos()
{
    return yPos;
}

float Tile::get_width()
{
    return width;
}

void Tile::gen_tile_visuals()
{
    RectangleShape bg(Vector2f(width, width));
    bg.setPosition(Vector2f(xPos, yPos));
    bg.setFillColor(bgColor);
    bg.setOutlineColor(Color::Black);
    bg.setOutlineThickness(1);
    numOfVisuals = 1;
    //adding the rectangles to the rectangle list
    visuals = new RectangleShape[numOfVisuals];
    visuals[0] = bg;
}

void Tile::draw(RenderWindow *window)
{
    for (int i = 0; i < numOfVisuals; i++)
        window->draw(visuals[i]);
    window->draw(text);
}

bool Tile::is_null()
{
    return isNull;
}

char Tile::get_value()
{
    return value;
}

void Tile::set_state(TileState state)
{
    this->state = state;
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
    return value != tile.value || xPos != tile.xPos || yPos != tile.yPos;
}

void Tile::set_isSelected(bool isSelected)
{
    this->isSelected = isSelected;
}

bool Tile::is_operator()
{
    return isOperator;
}

float Tile::get_xPos()
{
    return xPos;
}

float Tile::get_yPos()
{
    return yPos;
}

Font Tile::get_font()
{
    return font;
}