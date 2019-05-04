#include "BoardTile.hpp"

BoardTile::BoardTile()
{
}

BoardTile::BoardTile(float width, float xPos, float yPos, Font font, Color textColor, Color bgColor, bool isCenter)
{
    this->width = width;
    this->xPos = xPos;
    this->yPos = yPos;
    this->font = font;
    this->textColor = textColor;
    this->bgColor = isCenter ? Color::Green : bgColor;
    this->isCenter = isCenter;
    this->value = EMPTY;
    state = TILE_EMPTY;
    tileText.setFillColor(textColor);
    tileText.setFont(font);
}

void BoardTile::draw(RenderWindow *window)
{
    for (int i = 0; i < numOfVisuals; i++)
        window->draw(visuals[i]);
    window->draw(tileText);
}

void BoardTile::gen_visuals()
{
    numOfVisuals = 0;
    RectangleShape bg(Vector2f(width, width));
    bg.setFillColor(bgColor);
    bg.setPosition(Vector2f(xPos, yPos));
    bg.setOutlineColor(Color::Black);
    bg.setOutlineThickness(1);
    numOfVisuals++;
    visuals = new RectangleShape[numOfVisuals];
    visuals[0] = bg;
}

BoardTileState BoardTile::get_state()
{
    return state;
}

void BoardTile::set_state(BoardTileState state)
{
    this->state = state;
    if (state == TILE_FULL_PERM)
        visuals[0].setOutlineThickness(2);
}

float BoardTile::get_width()
{
    return width;
}

void BoardTile::set_width(float width)
{
    this->width = width;
}

float BoardTile::get_xPos()
{
    return xPos;
}

void BoardTile::set_xPos(float xPos)
{
    this->xPos = xPos;
}

float BoardTile::get_yPos()
{
    return yPos;
}

void BoardTile::set_yPos(float yPos)
{
    this->yPos = yPos;
}

void BoardTile::gen_text()
{
    tileText.setFont(font);
    tileText.setFillColor(textColor);
    tileText.setCharacterSize(width);
}

void BoardTile::update_text(char value, Color textColor)
{
    this->value = value;
    tileText.setString(new char[2]{value, '\0'});
    tileText.setFillColor(textColor);
    FloatRect lb = tileText.getLocalBounds();
    tileText.setOrigin(lb.left - xPos - (width - lb.width) / 2.f, lb.top - yPos - (width - lb.height) / 2.f);
}

bool BoardTile::is_center()
{
    return isCenter;
}

char BoardTile::get_value()
{
    return value;
}

void BoardTile::set_tile(Tile *tile)
{
    this->tile = tile;
}

Tile *BoardTile::get_tile()
{
    return tile;
}

void BoardTile::set_tile_to_null()
{
    tile = &nullTile;
}