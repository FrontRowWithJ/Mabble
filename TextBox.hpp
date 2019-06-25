#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Util.hpp"
#include "RoundedRectangle.hpp"
#include "LinkedList.hpp"
using namespace vector_op;
class TextBox
{
public:
    typedef enum TextStyle
    {
        LEFT,
        CENTRE_HORI,
        RIGHT,
        TOP,
        CENTRE_VERT,
        BOTTOM,
    } TextStyle;
private:
    float xPos;
    float yPos;
    float width;
    float height;
    float lineSpacing; //Introduce linespacing to textBox?
    RoundedRectangle background;
    TextStyle vertical;
    TextStyle horizontal;
    Text *boxText;
    const char *message;
    int textLen;
    Color textColor;
    Color bgColor;
    const char *fontName;

public:
    TextBox(float xPos, float yPos, float width, float height, float radius, const char*fontName, const char *message, Color _bgColor, Color _textColor);
    void draw(RenderWindow *window);
    void set_textStyle(TextStyle vertical, TextStyle horizontal);
    void set_color(Color textColor, Color bgColor);
    Color get_bgColor();
    Color get_textColor();
    void print();
    void gen_text();
    void set_characterSize(int characterSize);
    void fit_to_text();
private:
    static void add_char(char *&str, char c);
};
#endif