#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

#define X_OFFSET 2
#define Y_OFFSET 22
typedef struct
{
    int xPos;
    int yPos;
    Color c;
} Square;
int main(int argc, char **argv)
{
    int width = 675;
    int height = 675;
    string name = "Windows By Apple";
    RenderWindow window(VideoMode(width, height), name, Style::Close);
    sf::Event e;
    int w = 25;
    sf::Mouse m;
    Square **table = new Square *[w];
    RectangleShape **recs = new RectangleShape *[w];
    Mouse mouse;
    RectangleShape whiteSquare(Vector2f(w, w));
    whiteSquare.setFillColor(Color::White);
    whiteSquare.setOutlineColor(Color::Black);
    whiteSquare.setOutlineThickness(1.f);
    for (int i = 0; i < w; i++)
        table[i] = new Square[w];
    for (int i = 0; i < w; i++)
        recs[i] = new RectangleShape[w];
    for (int i = 0; i < w; i++)
        for (int j = 0; j < w; j++)
        {
            table[i][j] = (Square){w + i * w, w + j * w, Color(rand() % 255, rand() % 255, rand() % 255, 255)};
            RectangleShape rectangle(Vector2f(w, w));
            rectangle.setPosition(table[i][j].xPos, table[i][j].yPos);
            rectangle.setFillColor(table[i][j].c);
            rectangle.setOutlineColor(Color::Black);
            rectangle.setOutlineThickness(1.f);
            recs[i][j] = rectangle;
        }
    while (window.isOpen())
    {
        while (window.pollEvent(e))
        {
            switch (e.type)
            {
            case Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        window.clear(Color::White);
        Vector2i m = mouse.getPosition();
        Vector2i wi = window.getPosition();
        float xPos = m.x - wi.x + X_OFFSET;
        float yPos = m.y - wi.y + Y_OFFSET;
        float tableI = (xPos - w) / w;
        float tableJ = (yPos - w) / w;
        for (int i = 0; i < w; i++)
            for (int j = 0; j < w; j++)
                window.draw(recs[i][j]);
        if (tableI >= 0 && tableJ >= 0 && tableI < w && tableJ < w){
            whiteSquare.setPosition((float)table[(int)tableI][(int)tableJ].xPos, (float)table[(int)tableI][(int)tableJ].yPos);
            window.draw(whiteSquare);   
        }
        window.display();
    }
}