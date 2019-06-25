#include "MazeTile.hpp"

MazeTile::MazeTile()
{
}

MazeTile::MazeTile(float xPos, float yPos, float width, float radius, const char*fontName, char value, bool isTextPresent)
{
    bg = RoundedRectangle(xPos, yPos, width, width, radius, 7);
    this->value = value;
    int alpha = (int)(256.f * 0.5);
    this->operandColor = COLOR(0x270F36, alpha);
    this->operatorColor = COLOR(0x632B6C, alpha);
    this->equalColor = COLOR(0xC76B98, alpha);
    this->bgColor = isTextPresent ? COLOR(0xC76B98, alpha) : COLOR(0xFFFFFF, alpha);
    bg.set_thickness(0.0f);
    bg.set_fill_color(bgColor);
    bg.set_outline_color(bgColor);
    this->isTextPresent = isTextPresent;
    this->fontName = fontName;
}

void MazeTile::gen_text()
{
    Vector2f pos = bg.getPosition();
    float width = bg.get_width();
    Font f;
    f.loadFromFile(fontName);
    text = Text(new char[2]{value, '\0'}, f, width);
    FloatRect lb = text.getLocalBounds();
    text.setOrigin(SET_XPOS(pos.x, width), SET_YPOS(pos.y, width));
    if (value >= '0' && value <= '9')
        text.setFillColor(operandColor);
    else if (value == '/' || value == '+' || value == '*' || value == '-')
        text.setFillColor(operatorColor);
    else if (value == '=')
        text.setFillColor(equalColor);
    else
        text.setFillColor(Color::Black);
}

void MazeTile::draw(RenderWindow *window)
{
    bg.draw(window);
    if (isTextPresent)
        window->draw(text);
}

void MazeTile::set_position(float xPos, float yPos)
{
    bg.set_position(xPos, yPos);
    if (isTextPresent)
    {
        FloatRect lb = text.getLocalBounds();
        float width = bg.get_width();
        text.setOrigin(SET_XPOS(xPos, width), SET_YPOS(yPos, width));
    }
}

float MazeTile::get_xPos()
{
    return bg.getPosition().x;
}

float MazeTile::get_yPos()
{
    return bg.getPosition().y;
}

void MazeTile::set_fill_color(Color bgColor)
{
    bg.set_fill_color(bgColor);
}

void MazeTile::set_outline_color(Color outlineColor)
{
    bg.set_outline_color(outlineColor);
}

void MazeTile::set_radiusA()
{
    bg.set_radiusA_to_zero();
}

void MazeTile::set_radiusB()
{
    bg.set_radiusB_to_zero();
}

void MazeTile::set_radiusC()
{
    bg.set_radiusC_to_zero();
}

void MazeTile::set_radiusD()
{
    bg.set_radiusD_to_zero();
}

void MazeTile::set_xPos(float xPos)
{
    set_position(xPos, bg.getPosition().y);
}

void MazeTile::set_yPos(float yPos)
{
    set_position(bg.getPosition().x, yPos);
}