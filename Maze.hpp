#ifndef MAZE_H
#define MAZE_H

#include "Util.hpp"
#include "RoundedRectangle.hpp"
#include <random>

class Maze
{
private:
    size_t columnLen;
    LinkedList *columns;
    LinkedList *displayColumn;
    int xPos;
    int yPos;
    int width;

public:
    Maze(size_t columnLen);
    void display_matrix(RenderWindow *window);
    void gen_row();
    bool **to_matrix(size_t *width, size_t *height);
    int get_width();
    int get_height();

private:
    void update_display();
};
#endif
