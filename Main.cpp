#include "Util.hpp"
#include "TileRack.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "CheckButton.hpp"
#include "Player.hpp"

const unsigned int screenWidth = 700;
const unsigned int screenHeight = 700;
using namespace std;
using namespace sf;
typedef struct
{
    int xPos;
    int yPos;
    Color c;
} Square;
int main(int argc, char **argv)
{
    bool *isTurn = new bool[1]{true};
    int n = 0;
    Player *p1 = new Player(10, screenHeight - 60 - 10, 300, 60, 0.8, "Noob2", "lunchds.ttf", *isTurn);
    Player *p2 = new Player(screenWidth - 300 - 10, screenHeight - 60 - 10, 300, 60, 0.8, "Noob2", "lunchds.ttf", !*isTurn);
    RenderWindow *window = new RenderWindow(VideoMode(screenWidth, screenHeight), "Mabble", Style::Close);
    Event e;
    Mouse m;
    Color c = Color(0xE6, 0xC1, 0x94, 0xFF);
    const char *fontName = "lunchds.ttf";
    Board b = Board(500, 25, screenWidth / 2 - 250, 30, fontName, Color::Red, c);
    CheckButton cb = CheckButton(70, 20, screenWidth / 2 - 35, 600, fontName, 10 + 150, screenHeight - 60 - 10 - 60);
    LinkedList<TileData> *list = new LinkedList<TileData>();
    Tile *selectedTile;
    while (window->isOpen())
    {
        Vector2f mousePos = Vector2f(m.getPosition());
        Vector2f screenPos = Vector2f(window->getPosition());
        window->clear(Color::White);
        while (window->pollEvent(e))
        {
            switch (e.type)
            {
            case Event::Closed:
                window->close();
                break;
            case Event::MouseButtonPressed:
                if (e.mouseButton.button == Mouse::Left)
                {
                    if (*isTurn)
                        selectedTile = p1->select_tile(mousePos, screenPos);
                    else
                        selectedTile = p2->select_tile(mousePos, screenPos);
                    cb.check(mousePos.x, mousePos.y, screenPos.x, screenPos.y, b, list, p1, p2, isTurn, screenWidth, screenHeight);
                }
                break;
            case Event::MouseButtonReleased:
                p1->snap_tile_to_board(&b, list);
                p2->snap_tile_to_board(&b, list);
                break;
            }
        }
        b.draw(window);
        cb.draw(window);
        p1->draw(window, mousePos, screenPos);
        p2->draw(window, mousePos, screenPos);
        window->display();
    }
}