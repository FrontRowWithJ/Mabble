#ifndef MAZE_H
#define MAZE_H

#include "Util.hpp"
#include "RoundedRectangle.hpp"
#include <random>

class Maze
{
private:
    int width;
    int height;
    bool **currGen;
    bool isSeedGen;
    RoundedRectangle **display;
public:
    Maze(int width, int height);
    void gen_seed();
    void sim_next_generation();
    void display_matrix(RenderWindow *window);
    int get_width();
    int get_height();
};
#endif
