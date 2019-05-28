#ifndef MAZE_H
#define MAZE_H

#include "Util.hpp"
#include "RoundedRectangle.hpp"
#include "MazeTile.hpp"
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
    Font f;
    Node * displayPos;
    Node *valPos;
    bool oof = false;
    bool *nextColumn;
    const char *symbol;
public:
    Maze();
    Maze(size_t columnLen, size_t screenWidth, size_t screenHeight, Font f);
    void display_matrix(RenderWindow *window);
    int get_width();
    int get_height();

private:
    void update_display();
    void gen_column();
    void update_tile_corners();
    static void delete_rect(void *val);
    static void delete_bool(void *val);
};
#endif