#include "Maze.hpp"
float xPos = 300;
Maze::Maze(int height, int width)
{
    srand(time(NULL));
    this->width = width;
    this->height = height;
    this->currGen = new bool *[height];
    this->display = new RoundedRectangle *[height];
    for (int i = 0; i < height; i++)
    {
        currGen[i] = new bool[width];
        display[i] = new RoundedRectangle[width];
    }
    this->isSeedGen = false;
    int xPos = -40;
    int yPos = 10;
    int w = 40;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            display[i][j] = RoundedRectangle(xPos + j * w, yPos + i * w, w, w, 10, 10, 10, 10, 7);
            display[i][j].set_fill_color(currGen[i][j] ? Color::Green : Color::Red);
            display[i][j].set_outline_color(currGen[i][j] ? Color::Green : Color::Red);
        }
    }
}

void Maze::display_matrix(RenderWindow *window)
{
    for (int i = 0; i < this->height; i++)
        for (int j = 0; j < this->width; j++)
        {
            display[i][j].set_position(display[i][j].get_xPos() - 1, display[i][j].get_yPos());
            display[i][j].set_fill_color(currGen[i][j] ? Color::Green : Color::Red);
            display[i][j].set_outline_color(currGen[i][j] ? Color::Green : Color::Red);
            display[i][j].draw(window);
        }
}

int main()
{
    Maze m(17, 100);
    m.gen_seed();
    int n = 1;
    RenderWindow *window = new RenderWindow(VideoMode(700, 700), "Window", Style::Close);
    Event e;
    while (window->isOpen())
    {
        while (window->pollEvent(e))
        {
            switch (e.type)
            {
            case Event::Closed:
                window->close();
                break;
            }
        }
        window->clear(Color::Black);
        m.sim_next_generation();
        m.display_matrix(window);
        window->display();
    }
}

int Maze::get_height()
{
    return height;
}

int Maze::get_width()
{
    return width;
}

void Maze::gen_seed()
{
    // if (!isSeedGen)
    // {
    //     int startAlive = rand() % (width * height);
    //     printf("startAlive: %d\n", startAlive);
    //     for (int i = 0; i < startAlive; i++)
    //     {
    //         int index = rand() % (width * height);
    //         while (currGen[index / height][index % width])
    //             index = rand() % (width * height);
    //         currGen[index / height][index % width] = true;
    //     }
    //     isSeedGen = true;
    // }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            currGen[i][j] = rand() % 3 == 0;
}

void Maze::sim_next_generation()
{
    bool **nextGen = new bool *[height];
    for (int i = 0; i < height; i++)
        nextGen[i] = new bool[width];
    int n = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int neighbour = 0;
            neighbour += i - 1 == -1 || j - 1 == -1 ? 0 : currGen[i - 1][j - 1] ? 1 : 0;
            neighbour += i - 1 == -1 ? 0 : currGen[i - 1][j] ? 1 : 0;
            neighbour += i - 1 == -1 || j + 1 == width ? 0 : currGen[i - 1][j + 1];
            neighbour += j - 1 == -1 ? 0 : currGen[i][j - 1] ? 1 : 0;
            neighbour += j + 1 == width ? 0 : currGen[i][j + 1] ? 1 : 0;
            neighbour += i + 1 == height || j - 1 == -1 ? 0 : currGen[i + 1][j - 1] ? 1 : 0;
            neighbour += i + 1 == height ? 0 : currGen[i + 1][j] ? 1 : 0;
            neighbour += i + 1 == height || j + 1 == width ? 0 : currGen[i + 1][j + 1] ? 1 : 0;
            nextGen[i][j] = currGen[i][j];
            if (neighbour == 3)
                nextGen[i][j] = true;
            if (neighbour == 0 || neighbour > 5)
                nextGen[i][j] = false;
        }
    }
    bool **oldGen = currGen;
    currGen = nextGen;
    delete[] oldGen;
}