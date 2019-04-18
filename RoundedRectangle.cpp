#include "RoundedRectangle.hpp"

RoundedRectangle::RoundedRectangle()
{
}
RoundedRectangle::RoundedRectangle(float xPos, float yPos, float width, float height, float radius, int pointCount)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    radius = MIN_OF(radius, min(width, height) / 2);
    this->radius = radius;
    this->pointCount = pointCount;
    aStart = Vertex(Vector2f(xPos + width - radius, yPos));
    aEnd = Vertex(Vector2f(xPos + radius, yPos));
    bStart = Vertex(Vector2f(xPos, yPos + radius));
    bEnd = Vertex(Vector2f(xPos, yPos + height - radius));
    cStart = Vertex(Vector2f(xPos + radius, yPos + height));
    cEnd = Vertex(Vector2f(xPos + width - radius, yPos + height));
    dStart = Vertex(Vector2f(xPos + width, yPos + height - radius));
    dEnd = Vertex(Vector2f(xPos + width, yPos + radius));
    numOfCoords = 8 + pointCount * 4;
    gen_shape();
}

void RoundedRectangle::draw(RenderWindow *window)
{
    window->draw(r1);
    window->draw(r2);
    for (int i = 0; i < 4; i++)
        window->draw(circles[i]);
    window->draw(&roundedRect[0], numOfCoords, sf::LineStrip);
}

void RoundedRectangle::gen_shape()
{
    int index = 0;
    for (int i = 0; i < 4; i++)
        circles[i] = CircleShape(radius, 30);
    //first curve
    double centreX = xPos + width - radius;
    double centreY = yPos + radius;
    Vertex *vertices = gen_curve(centreX, centreY, 0);
    copy_to_shape(vertices);

    circles[index++].setPosition(centreX - radius, centreY - radius);

    roundedRect.push_back(aStart);
    roundedRect.push_back(aEnd);

    //second curve
    centreX = xPos + radius;
    vertices = gen_curve(centreX, centreY, M_PI_2);
    copy_to_shape(vertices);

    circles[index++].setPosition(centreX - radius, centreY - radius);

    roundedRect.push_back(bStart);
    roundedRect.push_back(bEnd);

    //third curve
    centreY = yPos + height - radius;
    vertices = gen_curve(centreX, centreY, M_PI);
    copy_to_shape(vertices);

    circles[index++].setPosition(centreX - radius, centreY - radius);

    roundedRect.push_back(cStart);
    roundedRect.push_back(cEnd);

    //fourth curve
    centreX = xPos + width - radius;
    vertices = gen_curve(centreX, centreY, 3 * M_PI_2);
    copy_to_shape(vertices);

    circles[index++].setPosition(centreX - radius, centreY - radius);

    roundedRect.push_back(dStart);
    roundedRect.push_back(dEnd);
    r1 = RectangleShape(Vector2f(width - 2 * radius, height));
    r1.setPosition(Vector2f(xPos + radius - 1, yPos));
    r2 = RectangleShape(Vector2f(width, height - 2 * radius));
    r2.setPosition(Vector2f(xPos - 1, yPos + radius));
}

Vertex *RoundedRectangle::gen_curve(double centreX, double centreY, double start)
{
    Vertex *vertices = new Vertex[pointCount];
    double inc = M_PI_2 / (double)pointCount;
    double theta = start;
    for (int i = 0; i < pointCount; i++)
    {
        double x = (radius)*cos(theta + i * inc);
        double y = (radius)*sin(theta + i * inc);
        Vertex v(Vector2f(centreX + x, centreY - y));
        vertices[i] = v;
    }
    return vertices;
}

void RoundedRectangle::copy_to_shape(Vertex *vertices)
{
    for (int i = 0; i < pointCount; i++)
        roundedRect.push_back(vertices[i]);
}

void RoundedRectangle::set_fill_color(Color fillColor)
{
    this->fillColor = fillColor;
    r1.setFillColor(fillColor);
    r2.setFillColor(fillColor);
    for (int i = 0; i < 4; i++)
        circles[i].setFillColor(fillColor);
}

Color RoundedRectangle::get_fill_color()
{
    return fillColor;
}

void RoundedRectangle::set_outline_color(Color outlineColor)
{
    this->outlineColor = outlineColor;
    for (int i = 0; i < numOfCoords; i++)
        roundedRect[i].color = outlineColor;
}
Color RoundedRectangle::get_outline_color()
{
    return outlineColor;
}

int RoundedRectangle::get_point_count()
{
    return pointCount;
}

int main(int argc, char **argv)
{
    RoundedRectangle r(80, 80, 100, 40, 10, 7);
    RenderWindow *window = new RenderWindow(VideoMode(600, 600), "Test", Style::Close);
    r.set_fill_color(Color::Blue);
    r.set_outline_color(Color::Red);
    CircleShape c(20, 100);
    c.setFillColor(Color::White);
    c.setPosition(122, 80);
    c.setOutlineColor(Color::Red);
    c.setOutlineThickness(1);
    Event e;
    while (window->isOpen())
    {
        while (window->pollEvent(e))
        {
            switch (e.type)
            {
            case Event::Closed:
                window->close();
                break;
            }
        }
        window->clear(Color::Black);
        r.draw(window);
        // window->draw(c);
        window->display();
    }
}