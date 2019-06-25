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

void TileRack::gen_tiles(const char *operands, const char *fontName)
{
    int i = 0;
    float xOff = width * (1.f - fgScale) / 2;
    float tileWidth = (width - height - xOff) / NUM_OF_TILES;
    float xOffset = 0;
    Vector2f pos = visuals[1].getPosition(), dim = visuals[1].getSize();
    float yOffset = (dim.y - tileWidth) / 2;
    for (int i = 0; i < NUM_OF_TILES; i++)
    {
        tiles[i] = Tile(operands[i], pos.x + xOffset, pos.y + yOffset, tileWidth, fontName);
        tiles[i].gen_visuals();
        xOffset += tileWidth;
    }
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
    float xOffset = width * (1.f - fgScale) / 2;
    float yOffset = height * (1.f - fgScale) / 2;
    RectangleShape fg(Vector2f(width - height - xOffset, height * fgScale));
    fg.setPosition(Vector2f(xPos + xOffset / 2.f, yPos + yOffset));
    fg.setFillColor(Color(255, 165, 0, 255));
    numOfVisuals++;
    visuals = new RectangleShape[numOfVisuals];
    visuals[0] = bg;
    visuals[1] = fg;
}

void TileRack::draw(RenderWindow *window, Vector2f mousePos, Vector2f screenPos)
{
    for (int i = 0; i < numOfVisuals; i++)
        window->draw(visuals[i]);
    for (int i = 0; i < NUM_OF_TILES; i++)
        tiles[i].draw(window, mousePos, screenPos);
}

Tile *TileRack::select_tile(Vector2f mousePos, Vector2f screenPos)
{
    Vector2f pos = mousePos - screenPos + Vector2f(X_OFFSET, Y_OFFSET);
    for (int i = 0; i < NUM_OF_TILES; i++)
    {
        Vector2f tilePos = tiles[i].get_positon();
        Vector2f tileSize = tiles[i].get_size();
        if (pos >= tilePos && pos < (tilePos + tileSize))
            return tiles[i].select_tile();
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

bool TileRack::update_tile(int index, char value, bool isNull)
{
    if (index < 0 || index >= NUM_OF_TILES)
        return false;
    Tile t = tiles[index];
    TileState ts = t.get_state();
    if (ts == ON_RACK || t.is_selected())
        return false;
    if (isNull)
        tiles[index] = Tile(t.get_xPos(), t.get_yPos(), t.get_width(), t.get_fontName());
    else
        tiles[index] = Tile(value, t.get_xPos(), t.get_yPos(), t.get_width(), t.get_fontName());
    tiles[index].gen_visuals();
    return true;
}

void TileRack::snap_to_board(Board *gameBoard, LinkedList<TileData> *placedTiles)
{
    for (int index = 0; index < NUM_OF_TILES; index++)
    {
        if (tiles[index].is_selected())
        {
            Vector2f boardPos = gameBoard->get_position();
            Vector2f tileCenterPos = tiles[index].get_positon() + tiles[index].get_width() / 2;
            float w = gameBoard->get_width();
            Vector2f boardDim = Vector2f(w, w);
            float tableTileWidth = gameBoard->get_table()[0]->get_width();
            if (tileCenterPos >= boardPos && tileCenterPos < boardPos + boardDim)
            {
                tileCenterPos -= boardPos;
                tileCenterPos /= tableTileWidth;
                int i = (int)tileCenterPos.y;
                int j = (int)tileCenterPos.x;
                if (tiles[index].get_state() == ON_BOARD_TEMP)
                {
                    Vector2i bp = tiles[index].get_boardPos();
                    if (bp != Vector2i(i, j) && bp != Vector2i(-1, -1))
                        gameBoard->remove_tile(placedTiles, bp.x, bp.y);
                }
                gameBoard->place_tile(placedTiles, &tiles[index], i, j);
            }
            else
            {
                if (tiles[index].get_state() == ON_BOARD_TEMP)
                {
                    Vector2i bp = tiles[index].get_boardPos();
                    gameBoard->remove_tile(placedTiles, bp.x, bp.y);
                }
                else
                    tiles[index].deselect_tile();
            }
        }
    }
}

void TileRack::reset_TileRack_Position()
{
    for (int i = 0; i < NUM_OF_TILES; i++)
        tiles[i].set_to_start_position();
}