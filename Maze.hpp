#ifndef MAZE_H
#define MAZE_H

#include "Util.hpp"
#include "RoundedRectangle.hpp"
#include <random>

class Maze
{
private:
    size_t columnLen;
    size_t screenWidth;
    size_t screenHeight;
    LinkedList *columns;
    LinkedList *displayColumn;
    int xPos;
    int yPos;
    int width;
    float panSpeed;
    float threshold;
    float startPos;
    Node * displayPos;
    Node *valPos;
public:
    Maze(size_t columnLen, size_t screenWidth, size_t screenHeight);
    void display_matrix(RenderWindow *window);
    bool **to_matrix(size_t *width, size_t *height);
    int get_width();
    int get_height();

private:
    void update_display();
    void gen_row();
    void update_tile_corners();
};
#endif
