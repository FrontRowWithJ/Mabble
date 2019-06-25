#ifndef MAZE_H
#define MAZE_H

#include "Util.hpp"
#include "RoundedRectangle.hpp"
#include "MazeTile.hpp"
#include "LinkedList.hpp"
#include <random>

#ifndef SYMBOLS
#define SYMBOLS "0123456789-+/*="
#endif

#ifndef NUM_OF_SYMBOLS
#define NUM_OF_SYMBOLS 15
#endif

class Maze
{
private:
    typedef struct MazeRect
    {
        RoundedRectangle *rect;
        int len;
    } RectArray;

    typedef struct TextStruct
    {
        Text *texts;
        int len;
    } TextArray;

    size_t columnLen;
    size_t screenWidth;
    size_t screenHeight;
    LinkedList<bool *> *columns;
    LinkedList<RectArray> *displayColumn;
    LinkedList<TextArray> *textColumns;
    float xPos;
    float yPos;
    float width;
    float panSpeed;
    float threshold;
    float startPos;
    LinkedList<RoundedRectangle *>::Node *displayPos;
    LinkedList<bool *>::Node *valPos;
    bool oof = false;
    bool *nextColumn;
    bool *prevColumn;
    float currXPos;
    const char *symbol;
    const char *fontName;

public:
    Maze();
    Maze(size_t columnLen, size_t screenWidth, size_t screenHeight, const char *fontName);
    int get_width();
    int get_height();
    void draw(RenderWindow *window);

private:
    void gen_column_visuals();
    void gen_column();
    void gen_text_column();
    static void delete_rect(void *val);
    static void delete_bool(void *val);
    static void delete_RectArray(void *val);
    static void delete_text(void *val);
};
#endif