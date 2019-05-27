#ifndef MAZETILE_H
#define MAZETILE_H

#include "Util.hpp"
#include "RoundedRectangle.hpp"
class MazeTile
{
private:
    RoundedRectangle *bg;
    Text text;
    char value;
    Font font;
    Color operandColor;
    Color operatorColor;
    Color equalColor;
    Color bgColor;
    bool isTextPresent;

public:
    MazeTile();
    MazeTile(float xPos, float yPos, float width, float radius, Font font, char value, bool isTextPresent);
    void draw(RenderWindow *window);
    void set_position(float xPos, float yPos);
    void set_xPos(float xPos);
    void set_yPos(float yPos);
    float get_xPos();
    float get_yPos();
    void set_fill_color(Color bgColor);
    void set_outline_color(Color outlineColor);
    void set_radiusA(float radiusA);
    void set_radiusB(float radiusB);
    void set_radiusC(float radiusC);
    void set_radiusD(float radiusD);
    void del();
    void gen_text();

private:
};

#endif