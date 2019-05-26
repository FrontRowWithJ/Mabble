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
    float xPos;
    float yPos;
    float width;
    float panSpeed;
    float threshold;
    float startPos;
    Node * displayPos;
    Node *valPos;
    bool oof = false;
    bool *nextColumn;

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
    static void delete_rect(void *val);
    static void delete_bool(void *val);
};
#endif