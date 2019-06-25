#include "BoardTile.hpp"

BoardTile::BoardTile()
{
}

BoardTile::BoardTile(float width, float xPos, float yPos, Color textColor, Color bgColor, const char *fontName, bool isCenter)
{
    this->width = width;
    this->xPos = xPos;
    this->yPos = yPos;
    this->textColor = textColor;
    this->bgColor = this->originalColor = isCenter ? Color::Green : bgColor;
    this->isCenter = isCenter;
    this->value = EMPTY;
    this->state = TILE_EMPTY;
    this->textFont.loadFromFile(fontName);
    this->isTextGenerated = false;
}

void BoardTile::draw(RenderWindow *window)
{
    window->draw(bg);
    if (isTextGenerated)
        window->draw(bgText);
}

void BoardTile::gen_visuals()
{
    bg = RoundedRectangle(xPos, yPos, width, width, 10, 7);
    bg.setOutlineThickness(1);
    bg.setFillColor(bgColor);
    bg.setOutlineColor(Color::Black);
}

void BoardTile::gen_text()
{
    bgText = Text();
    bgText.setFont(textFont);
    bgText.setCharacterSize(width);
    bgText.setFillColor(textColor);
    isTextGenerated = true;
}

BoardTileState BoardTile::get_state()
{
    return state;
}

void BoardTile::set_state(BoardTileState state)
{
    this->state = state;
    if (state == TILE_FULL_PERM)
        bg.setOutlineThickness(2);
}

float BoardTile::get_width()
{
    return width;
}

void BoardTile::set_width(float width)
{
    float widthDiff = width - this->width;
    this->width = width;
    bg.set_size(width, width);
    bgText.setPosition(bgText.getPosition() + widthDiff / 2);
}

float BoardTile::get_xPos()
{
    return xPos;
}

void BoardTile::set_xPos(float xPos)
{
    float xDiff = xPos - this->xPos;
    this->xPos = xPos;
    bg.setPosition(xPos, bg.getPosition().y);
    Vector2f pos = bgText.getPosition();
    bgText.setPosition(pos.x + xDiff, pos.y);
}

float BoardTile::get_yPos()
{
    return yPos;
}

void BoardTile::set_yPos(float yPos)
{
    float yDiff = yPos - this->yPos;
    this->yPos = yPos;
    bg.setPosition(bg.getPosition().x, yPos);
    Vector2f pos = bgText.getPosition();
    bgText.setPosition(pos.x, pos.y + yDiff);
}

void BoardTile::update_text(char value, Color textColor)
{
    this->value = value;
    this->textColor = textColor;
    if (!isTextGenerated)
        gen_text();
    char str[2] = {value, '\0'};
    bgText.setString(str);
    bgText.setFillColor(textColor);
    update_text_position();
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

bool BoardTile::is_empty()
{
    return state == TILE_EMPTY;
}

void BoardTile::set_bgColor(Color bgColor)
{
    this->bgColor = bgColor;
    bg.setFillColor(bgColor);
}

void BoardTile::revert_bgColor()
{
    set_bgColor(originalColor);
}

void BoardTile::update_text_position()
{
    FloatRect lb = bgText.getLocalBounds();
    bgText.setOrigin(lb.left, lb.top);
    Vector2f pos = bg.getPosition();
    Vector2f size = bg.get_size();
    bgText.setPosition(pos + (size - Vector2f(lb.width, lb.height)) / 2);
}

Vector2f BoardTile::get_position()
{
    return Vector2f(xPos, yPos);
}

void BoardTile::set_quadrant_radius(float radius, Quadrant q)
{
    switch (q)
    {
    case A:
        bg.set_radiusA(radius);
        break;
    case B:
        bg.set_radiusB(radius);
        break;
    case C:
        bg.set_radiusC(radius);
        break;
    case D:
        bg.set_radiusD(radius);
    }
}