#include "TileVisual.hpp"

TileVisual::TileVisual()
{
}

TileVisual::TileVisual(float xPos, float yPos, float width, float height, float radius, char *text, Font font, bool isTextPresent)
{
    bg = RoundedRectangle(xPos, yPos, width, height, radius, 7);
    this->alpha = 255.f;
    this->text = text;
    this->isTextPresent = isTextPresent;
    set_bg_position(xPos, yPos);
}

void TileVisual::set_text_position(float xPos, float yPos)
{
    FloatRect lb = tileText.getLocalBounds();
    Vector2f size(bg.get_width(), bg.get_height());
    tileText.setOrigin(lb.left - xPos - (size.x - lb.width) / 2.f, lb.top - yPos - (size.y - lb.height) / 2.f);
}

Vector2f TileVisual::get_position()
{
    return Vector2f(bg.get_xPos(), bg.get_yPos());
}

void TileVisual::set_bg_position(float xPos, float yPos)
{
    bg.set_position(xPos, yPos);
}

void TileVisual::set_position(Vector2f position)
{
    set_bg_position(position.x, position.y);
    if (isTextPresent)
        set_text_position(position.x, position.y);
}

void TileVisual::set_position(float xPos, float yPos)
{
    set_bg_position(xPos, yPos);
    if (isTextPresent)
        set_text_position(xPos, yPos);
}

void TileVisual::set_bg_color(Color c)
{
    bg.set_fill_color(c);
}

void TileVisual::set_outline_color(Color c)
{
    bg.set_outline_color(c);
}

void TileVisual::set_text_color(Color c)
{
    tileText.setFillColor(c);
}

void TileVisual::set_outline_thickness(float thickness)
{
    bg.set_thickness(thickness);
}

void TileVisual::draw(RenderWindow *window)
{
    bg.draw(window);
    window->draw(tileText);
}

void TileVisual::set_alpha(float alpha)
{
    this->alpha = alpha;
    set_bg_alpha(alpha);
    if (isTextPresent)
        set_text_alpha(alpha);
}

void TileVisual::set_bg_alpha(float alpha)
{
    Color c = bg.get_fill_color();
    bg.set_fill_color(Color(c.r, c.g, c.b, (int)alpha));
    // bg.set_fill_color(Color((c.toInteger() & 0xFFFFFF00) | (int)alpha));
}

void TileVisual::set_text_alpha(float alpha)
{
    Color c = tileText.getFillColor();
    tileText.setFillColor(Color(c.r, c.g, c.b, (int)alpha));
    // tileText.setFillColor(Color((c.toInteger() & 0xFFFFFF00) | (int)alpha));
}

float TileVisual::get_alpha()
{
    return alpha;
}

float TileVisual::get_width()
{
    return bg.get_width();
}

float TileVisual::get_height()
{
    return bg.get_height();
}

float TileVisual::set_size(float width, float height)
{
    bg.set_size(width, height);
    tileText.setCharacterSize(MIN_OF(width, height));
}

void TileVisual::gen_text(Text t)
{
    if (isTextPresent)
    {
        tileText = t;
        set_text_position(bg.get_xPos(), bg.get_yPos());
    }
}