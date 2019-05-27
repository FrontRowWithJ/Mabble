#include "MazeTile.hpp"

MazeTile::MazeTile()
{
}

MazeTile::MazeTile(float xPos, float yPos, float width, float radius, Font font, char value, bool isTextPresent)
{
    bg = new RoundedRectangle(xPos, yPos, width, width, radius, 7);
    this->value = value;
    this->font = font;
    int alpha = static_cast<int>(255 * 0.5);
    this->operandColor = COLOR(0x270F36, alpha);
    this->operatorColor = COLOR(0x632B6C, alpha);
    this->equalColor = COLOR(0xC76B98, alpha);
    this->bgColor = isTextPresent ? COLOR(0xC76B98, alpha) : COLOR(0xFFFFFF, alpha);
    bg->set_thickness(0.0f);
    bg->set_fill_color(bgColor);
    bg->set_outline_color(bgColor);
    this->isTextPresent = isTextPresent;
}

void MazeTile::gen_text()
{
    float xPos = bg->get_xPos(), yPos = bg->get_yPos(), width = bg->get_width();
    text = Text(new char[2]{value, '\0'}, font, width);
    FloatRect lb = text.getLocalBounds();
    text.setOrigin(SET_XPOS(xPos, width), SET_YPOS(yPos, width));
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
    bg->draw(window);
    if (isTextPresent)
        window->draw(text);
}

void MazeTile::set_position(float xPos, float yPos)
{
    bg->set_position(xPos, yPos);
    if (isTextPresent)
    {
        FloatRect lb = text.getLocalBounds();
        float width = bg->get_width();
        text.setOrigin(SET_XPOS(xPos, width), SET_YPOS(yPos, width));
    }
}

float MazeTile::get_xPos()
{
    return bg->get_xPos();
}

float MazeTile::get_yPos()
{
    return bg->get_yPos();
}

void MazeTile::set_fill_color(Color bgColor)
{
    bg->set_fill_color(bgColor);
}

void MazeTile::set_outline_color(Color outlineColor)
{
    bg->set_outline_color(outlineColor);
}

void MazeTile::set_radiusA(float radiusA)
{
    bg->set_radiusA(radiusA);
}

void MazeTile::set_radiusB(float radiusB)
{
    bg->set_radiusB(radiusB);
}

void MazeTile::set_radiusC(float radiusC)
{
    bg->set_radiusC(radiusC);
}

void MazeTile::set_radiusD(float radiusD)
{
    bg->set_radiusD(radiusD);
}

void MazeTile::del()
{
    delete bg;
}

void MazeTile::set_xPos(float xPos)
{
    float yPos = bg->get_yPos();
    set_position(xPos, yPos);
}

void MazeTile::set_yPos(float yPos)
{
    float xPos = bg->get_xPos();
    set_position(xPos, yPos);
}