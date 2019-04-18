#include "TileRack.hpp"

TileRack::TileRack(float xPos, float yPos, float width, float height, float fgScale)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    fgScale = abs(fgScale);
    this->fgScale = fgScale > 1 ? 1 : fgScale;
}

void TileRack::gen_tiles(char *operands)
{
    int i = 0;
    float tileWidth = (width * fgScale) / NUM_OF_TILES;
    float xOffset = 0;
    Font font;
    font.loadFromFile("GeosansLight.ttf");
    Vector2f pos = visuals[1].getPosition(), dim = visuals[1].getSize();
    float yOffset = (dim.y - tileWidth) / 2;
    for (; i < NUM_OF_OPERANDS; i++)
    {
        tiles[i] = Tile(operands[i], pos.x + xOffset, pos.y + yOffset, tileWidth, font, OPERAND);
        tiles[i].gen_tile_visuals();
        tiles[i].gen_text();
        xOffset += tileWidth;
    }
    char operators[4] = {'+', '-', '/', '*'};
    for (; i < NUM_OF_OPERANDS + NUM_OF_OPERATORS; i++)
    {
        tiles[i] = Tile(operators[i - NUM_OF_OPERANDS], pos.x + xOffset, pos.y + yOffset, tileWidth, font, OPERATOR);
        tiles[i].gen_tile_visuals();
        tiles[i].gen_text();
        xOffset += tileWidth;
    }
    tiles[i] = Tile('=', pos.x + xOffset, pos.y + yOffset, tileWidth, font, EQUAL_SIGN);
    tiles[i].gen_tile_visuals();
    tiles[i].gen_text();
}

void TileRack::gen_visuals()
{
    numOfVisuals = 0;
    RectangleShape bg(Vector2f(width, height));
    bg.setPosition(Vector2f(xPos, yPos));
    int beigeHex = 0xE6C194;
    Color beige = Color(beigeHex >> 16, (beigeHex >> 8) & 0xFF, beigeHex & 0xFF);
    bg.setFillColor(Color(beige.r * 0.6, beige.g * 0.6, beige.b * 0.6, 255));
    bg.setOutlineColor(Color::Black);
    bg.setOutlineThickness(1);
    numOfVisuals++;

    RectangleShape fg(Vector2f(width * fgScale, height * fgScale));
    float xOffset = width * (1.f - fgScale) / 2;
    float yOffset = height * (1.f - fgScale) / 2;
    fg.setPosition(Vector2f(xPos + xOffset, yPos + yOffset));
    fg.setFillColor(Color(255, 165, 0, 255));
    numOfVisuals++;

    visuals = new RectangleShape[numOfVisuals];
    visuals[0] = bg;
    visuals[1] = fg;
}

void TileRack::draw(RenderWindow *window)
{
    for (int i = 0; i < numOfVisuals; i++)
        window->draw(visuals[i]);
    for (int i = 0; i < NUM_OF_TILES; i++)
        tiles[i].draw(window);
}

Tile *TileRack::select_tile(float mouseX, float mouseY, float screenX, float screenY)
{
    float x = mouseX - screenX + X_OFFSET;
    float y = mouseY - screenY + Y_OFFSET;
    float width = tiles->get_width();
    float tileXpos = tiles->get_xpos();
    float tileYpos = tiles->get_ypos();
    x -= tileXpos;
    x /= width;
    if (y >= tileYpos && y < tileYpos + width && x >= 0 && x < NUM_OF_TILES && tiles[(int)x].get_state() != ON_BOARD_TEMP && tiles[(int)x].get_state() != ON_BOARD_PERM && !is_tile_selected())
    {
        return tiles[(int)x].select_tile();
    }
    return NULL;
}

bool TileRack::is_tile_selected()
{
    for (int i = 0; i < NUM_OF_TILES; i++)
        if (tiles[i].is_selected())
            return true;
    return false;
}

bool TileRack::deselect_tile(float mouseX, float mouseY, float screenX, float screenY)
{
    float x = mouseX - screenX + X_OFFSET;
    float y = mouseY - screenY + Y_OFFSET;
    float width = tiles->get_width();
    float tileXpos = tiles->get_xpos();
    float tileYpos = tiles->get_ypos();
    x -= tileXpos;
    x /= width;
    if (y >= tileYpos && y < tileYpos + width && x >= 0 && x < NUM_OF_TILES && tiles[(int)x].get_state() != ON_BOARD_PERM && tiles[(int)x].get_state() != ON_BOARD_TEMP && is_tile_selected())
    {
        printf("state: %d\n", tiles[(int)x].get_state());
        tiles[(int)x].deselect_tile();
        return true;
    }
    return false;
}
