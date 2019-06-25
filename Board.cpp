#include "Board.hpp"

Board::Board(float width, int rowLen, float xPos, float yPos, const char *fontName, Color textColor, Color bgColor)
{
    //boardWidth must be an odd number
    this->width = width;
    this->rowLen = rowLen % 2 == 1 ? rowLen : rowLen + 1;
    this->xPos = xPos;
    this->yPos = yPos;
    gen_board(fontName, textColor, bgColor);
}

void Board::place_tile(LinkedList<TileData> *placedTiles, Tile *selectedTile, int i, int j)
{
    TileData td;
    Vector2f boardCoords;
    Tile *t;
    switch (table[i][j].get_state())
    {
    case TILE_FULL_TEMP:
        t = table[i][j].get_tile();
        t->deselect_tile();
        td = (TileData){i, j, t->get_value()};
        placedTiles->delete_node(td);
        set_radii(i, j);
    case TILE_EMPTY:
        table[i][j].set_tile(selectedTile);
        table[i][j].set_state(TILE_FULL_TEMP);
        table[i][j].set_bgColor(selectedTile->get_bgColor());
        table[i][j].update_text(selectedTile->get_value(), selectedTile->get_textColor());
        selectedTile->set_state(ON_BOARD_TEMP);
        selectedTile->set_isSelected(false);
        selectedTile->set_boardPos(Vector2i(i, j));
        boardCoords = table[i][j].get_position() - (selectedTile->get_width() - table[i][j].get_width()) / 2;
        selectedTile->set_position_to_board(boardCoords);
        td = (TileData){i, j, selectedTile->get_value()};
        placedTiles->insert(td);
        set_radii(i, j);
        break;
    case TILE_FULL_PERM:
        selectedTile->deselect_tile();
    }
}

void Board::clear_board()
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < width; j++)
        {
            table[i][j].set_tile_to_null();
            table[i][j].set_state(TILE_EMPTY);
        }
}

void Board::gen_board(const char *fontName, Color textColor, Color bgColor)
{
    table = new BoardTile *[rowLen];
    for (int i = 0; i < rowLen; i++)
        table[i] = new BoardTile[rowLen];

    int yOffset = 0;
    for (int i = 0; i < rowLen; i++)
    {
        int xOffset = 0;
        for (int j = 0; j < rowLen; j++)
        {
            table[i][j] = BoardTile(width / rowLen, xPos + xOffset, yPos + yOffset, textColor, bgColor, fontName, i == rowLen / 2 && j == rowLen / 2);
            xOffset += width / rowLen;
            table[i][j].gen_visuals();
        }
        yOffset += width / rowLen;
    }
}

void Board::draw(RenderWindow *window)
{
    for (int i = 0; i < rowLen; i++)
        for (int j = 0; j < rowLen; j++)
            table[i][j].draw(window);
}

void Board::remove_tile(LinkedList<TileData> *placedTiles, int i, int j)
{
    switch (table[i][j].get_state())
    {
    case TILE_FULL_PERM:
        break;
    case TILE_EMPTY:
        break;
    case TILE_FULL_TEMP:
        Tile *t = table[i][j].get_tile();
        t->deselect_tile();
        TileData td = (TileData){i, j, t->get_value()};
        placedTiles->delete_node(td);
        table[i][j].set_tile(NULL);
        table[i][j].set_state(TILE_EMPTY);
        table[i][j].update_text(EMPTY, Color::Black);
        table[i][j].revert_bgColor();
        unset_radii(i, j);
    }
}

void Board::print_list(LinkedList<TileData> *list)
{
    list->print();
}

BoardTile **Board::get_table()
{
    return table;
}

float Board::get_width()
{
    return width;
}

Vector2f Board::get_position()
{
    return Vector2f(xPos, yPos);
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

void Board::set_radii(int i, int j)
{
    if (j + 1 < rowLen)
        update_tile_radii(&table[i][j], &table[i][j + 1], A, D, B, C);
    if (i - 1 >= 0)
        update_tile_radii(&table[i][j], &table[i - 1][j], A, B, C, D);
    if (j - 1 >= 0)
        update_tile_radii(&table[i][j], &table[i][j - 1], B, C, A, D);
    if (i + 1 < rowLen)
        update_tile_radii(&table[i][j], &table[i + 1][j], C, D, A, B);
}

typedef int __;
#define ___ (
#define ____ )
#define _____ {
#define ______ }
#define _______ return
#define ________ *
#define _________ ;
__ _ ___ __ _ ____
    _____
        _______ _ ________ _ _________
            ______ void
            Board::update_tile_radii(BoardTile *t0, BoardTile *t1, Quadrant a, Quadrant b, Quadrant c, Quadrant d)
{
    BoardTileState bt0 = t0->get_state(), bt1 = t1->get_state();
    if (bt0 != TILE_EMPTY && bt1 != TILE_EMPTY)
    {
        t0->set_quadrant_radius(0, a);
        t0->set_quadrant_radius(0, b);
        t1->set_quadrant_radius(0, c);
        t1->set_quadrant_radius(0, d);
        printf("%d\n", _(47));
    }
}

void Board::unset_radii(int i, int j)
{
    int _i, _j;
    table[i][j].set_quadrant_radius(10, A);
    table[i][j].set_quadrant_radius(10, B);
    table[i][j].set_quadrant_radius(10, C);
    table[i][j].set_quadrant_radius(10, D);
    _i = i - 1;
    _j = j;
    if (_j - 1 >= 0 && table[_i][_j - 1].get_state() == TILE_EMPTY)
        table[_i][_j].set_quadrant_radius(10, C);
    if (_j + 1 < rowLen && table[_i][_j + 1].get_state() == TILE_EMPTY)
        table[_i][_j].set_quadrant_radius(10, D);
    _i = i + 1;
    _j = j;
    if (_j - 1 >= 0 && table[_i][_j - 1].get_state() == TILE_EMPTY)
        table[_i][_j].set_quadrant_radius(10, B);
    if (_j + 1 < rowLen && table[_i][_j + 1].get_state() == TILE_EMPTY)
        table[_i][_j].set_quadrant_radius(10, D);
    _i = i;
    _j = j - 1;
    if (_i - 1 >= 0 && table[_i - 1][_j].get_state() == TILE_EMPTY)
        table[_i][_j].set_quadrant_radius(10, A);
    if (_i + 1 < rowLen && table[_i + 1][_j].get_state() == TILE_EMPTY)
        table[_i][_j].set_quadrant_radius(10, D);
    _i = i;
    _j = j + 1;
    if (_i - 1 >= 0 && table[_i - 1][_j].get_state() == TILE_EMPTY)
        table[_i][_j].set_quadrant_radius(10, B);
    if (_i + 1 < rowLen && table[_i + 1][_j].get_state() == TILE_EMPTY)
        table[_i][_j].set_quadrant_radius(10, C);
}
