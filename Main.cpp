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
//int xpos = mouse.x - window.x + x_offset
//int ypos = mouse.y - window.y + y_offset
int main(int argc, char **argv)
{
    bool *isTurn = new bool[1]{true};
    Font f;
    f.loadFromFile("GeosansLight.ttf");
    Player *p1 = new Player(10, screenHeight - 60 - 10, 300, 60, 0.8, "Noob2", f, *isTurn);
    Player *p2 = new Player(screenWidth - 300 - 10, screenHeight - 60 - 10, 300, 60, 0.8, "Noob2", f, !*isTurn);
    RenderWindow *window = new RenderWindow(VideoMode(screenWidth, screenHeight), "Mabble", Style::Close);
    Event e;
    Mouse m;
    Color c = Color(0xE6, 0xC1, 0x94, 0xFF);
    Board b = Board(500, 25, screenWidth / 2 - 250, 30, f, Color::Red, c);
    CheckButton cb = CheckButton(70, 20, screenWidth / 2 - 35, 600, f, 10 + 150, screenHeight - 60 - 10 - 60);
    LinkedList<TileData> *list = new LinkedList<TileData>();
    while (window->isOpen())
    {
        window->clear(Color::White);
        while (window->pollEvent(e))
        {
            switch (e.type)
            {
            case Event::Closed:
                window->close();
                break;
            case Event::MouseButtonPressed:
                Vector2i mousePos = m.getPosition();
                Vector2i screenPos = window->getPosition();
                if (e.mouseButton.button == Mouse::Left)
                {
                    if (*isTurn)
                        b.set_selected_tile(p1->select_tile(mousePos.x, mousePos.y, screenPos.x, screenPos.y));
                    else
                        b.set_selected_tile(p2->select_tile(mousePos.x, mousePos.y, screenPos.x, screenPos.y));
                    if (b.place_tile(mousePos.x, mousePos.y, screenPos.x, screenPos.y, list))
                        b.print_list(list);
                    cb.check(mousePos.x, mousePos.y, screenPos.x, screenPos.y, b, list, p1, p2, isTurn, screenWidth, screenHeight);
                }
                else if (e.mouseButton.button == Mouse::Right)
                {
                    if (*isTurn)
                        b.clear_selected_tile(p1->deselect_tile(mousePos.x, mousePos.y, screenPos.x, screenPos.y));
                    else
                        b.clear_selected_tile(p2->deselect_tile(mousePos.x, mousePos.y, screenPos.x, screenPos.y));
                    if (b.remove_tile(mousePos.x, mousePos.y, screenPos.x, screenPos.y, list))
                        b.print_list(list);
                }
                else if (m.isButtonPressed(e.mouseButton.button))
                {
                    p1->get_tile_rack()->is_tile_pressed(mousePos, screenPos);
                }
                break;
            }
        }
        printf("oof0\n");
        p1->draw(window);
        p2->draw(window);
        b.draw(window);
        cb.draw(window);
        window->display();
    }
}