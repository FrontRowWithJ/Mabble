#ifndef TILEVISUAL_H
#define TILEVISUAL_H

#include "Util.hpp"
#include "RoundedRectangle.hpp"

#ifndef MAX_ALPHA
#define MAX_ALPHA 255
#endif

class TileVisual
{
private:
    RoundedRectangle bg;
    Text tileText;
    char *text;
    Font font;
    float alpha;
    bool isTextPresent;
public:
    TileVisual();
    TileVisual(float xPos, float yPos, float width, float height, float radius, char *text, Font font, bool isTextPresent);
    void set_position(Vector2f position);
    Vector2f get_position();
    void set_position(float xPos, float yPos);
    void set_bg_color(Color c);
    void set_text_color(Color c);
    void set_outline_color(Color c);
    void set_outline_thickness(float thickness);
    void draw(RenderWindow *window);
    void set_alpha(float alpha);
    float get_alpha();
    float set_size(float width, float height);
    float get_width();
    float get_height();
    void gen_text(Text t);

private:
    void set_bg_position(float xPos, float yPos);
    void set_text_position(float xPos, float yPos);
    void set_bg_alpha(float alpha);
    void set_text_alpha(float alpha);
};

#endif