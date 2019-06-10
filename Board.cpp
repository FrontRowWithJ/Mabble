#include "Board.hpp"

Board::Board(float width, int rowLen, float xPos, float yPos, Font font, Color textColor, Color bgColor)
{
    //boardWidth must be an odd number
    this->width = width;
    this->rowLen = rowLen % 2 == 1 ? rowLen : rowLen + 1;
    this->xPos = xPos;
    this->yPos = yPos;
    gen_board(font, textColor, bgColor);
}

bool Board::place_tile(float mouseX, float mouseY, float screenX, float screenY, LinkedList<TileData> *placedTiles)
{
    if (selectedTile != NULL)
    {
        float x = mouseX - screenX + X_OFFSET;
        float y = mouseY - screenY + Y_OFFSET;
        float width = table[0][0]->get_width();
        float xPos = table[0][0]->get_xPos();
        float yPos = table[0][0]->get_yPos();
        x -= xPos, y -= yPos;
        x /= width, y /= width;
        int i = (int)y, j = (int)x;
        TileData td = TileData();
        if (i >= 0 && i < rowLen && j >= 0 && j < rowLen)
        {
            switch (table[i][j]->get_state())
            {
            case TILE_EMPTY:
                table[i][j]->set_tile(selectedTile);
                table[i][j]->set_state(TILE_FULL_TEMP);
                selectedTile->set_state(ON_BOARD_TEMP);
                selectedTile->set_isSelected(false);
                table[i][j]->update_text(selectedTile->get_value(), selectedTile->get_textColor());
                td = (TileData){i, j, selectedTile->get_value()};
                placedTiles->insert(td);
                selectedTile = NULL;
                return true;
            case TILE_FULL_PERM:
                return false;
            case TILE_FULL_TEMP:
                Tile *t = table[i][j]->get_tile();
                t->deselect_tile();
                td = (TileData){i, j, t->get_value()};
                td.i = i;
                td.j = j;
                td.value = t->get_value();
                placedTiles->delete_node(td);
                table[i][j]->set_tile(selectedTile);
                selectedTile->set_state(ON_BOARD_TEMP);
                table[i][j]->update_text(selectedTile->get_value(), selectedTile->get_textColor());
                selectedTile->set_isSelected(false);
                td.value = selectedTile->get_value();
                placedTiles->insert(td);
                selectedTile = NULL;
                return true;
            }
        }
    }
    return false;
}

void Board::clear_board()
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < width; j++)
        {
            table[i][j]->set_tile_to_null();
            table[i][j]->set_state(TILE_EMPTY);
        }
}

void Board::gen_board(Font font, Color textColor, Color bgColor)
{
    table = new BoardTile **[rowLen];
    for (int i = 0; i < rowLen; i++)
        table[i] = new BoardTile *[rowLen];

    int yOffset = 0;
    for (int i = 0; i < rowLen; i++)
    {
        int xOffset = 0;
        for (int j = 0; j < rowLen; j++)
        {
            table[i][j] = new BoardTile(width / rowLen, xPos + xOffset, yPos + yOffset, font, textColor, bgColor, i == rowLen / 2 && j == rowLen / 2);
            xOffset += width / rowLen;
            table[i][j]->gen_visuals();
            table[i][j]->gen_text();
        }
        yOffset += width / rowLen;
    }
}

void Board::draw(RenderWindow *window)
{
    for (int i = 0; i < rowLen; i++)
        for (int j = 0; j < rowLen; j++)
            table[i][j]->draw(window);
}

void Board::set_selected_tile(Tile *selectedTile)
{
    if (selectedTile != NULL)
        this->selectedTile = selectedTile;
}

void Board::clear_selected_tile(bool canClear)
{
    if (canClear)
        selectedTile = NULL;
    // Find the boardTile associated with the selectedTile and clear it from the board
}

bool Board::remove_tile(float mouseX, float mouseY, float screenX, float screenY, LinkedList<TileData> *placedTiles)
{
    float x = mouseX - screenX + X_OFFSET;
    float y = mouseY - screenY + Y_OFFSET;
    float width = table[0][0]->get_width();
    float xPos = table[0][0]->get_xPos();
    float yPos = table[0][0]->get_yPos();
    x -= xPos, y -= yPos;
    x /= width, y /= width;
    int i = (int)y, j = (int)x;
    TileData td = TileData();
    if (i >= 0 && i < rowLen && j >= 0 && j < rowLen)
    {
        switch (table[i][j]->get_state())
        {
        case TILE_FULL_PERM:
            return false;
        case TILE_EMPTY:
            return false;
        case TILE_FULL_TEMP:
            Tile *t = table[i][j]->get_tile();
            t->deselect_tile();
            td = (TileData){i, j, t->get_value()};
            placedTiles->delete_node(td);
            table[i][j]->set_tile(NULL);
            table[i][j]->set_state(TILE_EMPTY);
            table[i][j]->update_text(EMPTY, Color::Black);
            return true;
        }
    }
    return false;
}

void Board::print_list(LinkedList<TileData> *list)
{
    list->print(NULL);
}

BoardTile ***Board::get_table()
{
    return table;
}

float Board::get_width()
{
    return width;
}

int Board::get_rowLen()
{
    return rowLen;
}

bool TileData::operator==(TileData rhs)
{
    return i == rhs.i && j == rhs.j && value == rhs.value;
}

char *TileData::c_str()
{
    return new char[2]{value, '\0'};
}