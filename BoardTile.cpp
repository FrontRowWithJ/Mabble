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
    state = TILE_EMPTY;
    tileText.setPosition(xPos + width / 5.f, yPos - width / 8.f);
    tileText.setFillColor(textColor);
    tileText.setFont(font);
}

void BoardTile::set_text(char value, Color textColor)
{
    tileText.setFillColor(textColor);
    tileText.setString(new char[2]{value, '\0'});
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
}

Tile *BoardTile::get_tile()
{
    return tile;
}

void BoardTile::set_tile(Tile *tile)
{
    this->tile = tile;
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

void BoardTile::set_tile_to_null()
{
    tile = &nullTile;
}

void BoardTile::gen_text()
{
    tileText.setFont(font);
    tileText.setString("");
    tileText.setFillColor(textColor);
    tileText.setCharacterSize(width);
    tileText.setPosition(xPos + width / 5.f, yPos - width / 8.f);
}

void BoardTile::update_text(char value, Color textColor)
{
    tileText.setString(new char[2]{value, '\0'});
    tileText.setFillColor(textColor);
}

bool BoardTile::is_center()
{
    return isCenter;
}