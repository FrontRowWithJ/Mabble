#include "Tile.hpp"

Tile::Tile()
{
    isNull = true;
    value = '\0';
    xpos = -1.f;
    ypos = -1.f;
}
Tile::Tile(char value, float xpos, float ypos, float width, Font font, TileType type)
{
    this->value = value;
    this->xpos = xpos;
    this->ypos = ypos;
    this->width = width;
    this->font = font;
    this->type = type;
    this->isNull = false;
    this->state = ON_RACK;
    Color purple = Color(128, 0, 128, 255);
    switch (type)
    {
    case OPERAND:
        this->textColor = purple;
        break;
    case OPERATOR:
        this->textColor = Color::Red;
        break;
    case EQUAL_SIGN:
        this->textColor = Color::White;
    }
}

void Tile::gen_text()
{
    text.setFont(font);
    text.setFillColor(textColor);
    text.setString(new char[2]{value, '\0'});
    text.setPosition(Vector2f(xpos + width / 5, ypos - width / 8));
    text.setCharacterSize(width);
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
    if (!isSelected)
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

size_t Tile::get_number_of_visuals()
{
    return this->numOfVisuals;
}

bool Tile::is_selected()
{
    return isSelected;
}

float Tile::get_xpos()
{
    return xpos;
}

float Tile::get_ypos()
{
    return ypos;
}

float Tile::get_width()
{
    return width;
}

void Tile::gen_tile_visuals()
{
    RectangleShape bg(Vector2f(width, width));
    bg.setPosition(Vector2f(xpos, ypos));
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
}

TileState Tile::get_state()
{
    return state;
}

Color Tile::get_text_color()
{
    return textColor;
}

bool Tile::operator!=(Tile tile)
{
    return value != tile.value || xpos != tile.xpos || ypos != tile.ypos;
}

void Tile::set_is_selected(bool isSelected)
{
    this->isSelected = isSelected;
}