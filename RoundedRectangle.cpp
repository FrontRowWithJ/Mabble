#include "RoundedRectangle.hpp"

RoundedRectangle::RoundedRectangle()
{
}

RoundedRectangle::RoundedRectangle(float xPos, float yPos, float width, float height, float radiusA, float radiusB, float radiusC, float radiusD, int pointCount)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    this->pointCount = pointCount;
    float minVal = min(width, height) / 2;
    this->radiusA = MIN_OF(radiusA, minVal);
    this->radiusB = MIN_OF(radiusB, minVal);
    this->radiusC = MIN_OF(radiusC, minVal);
    this->radiusD = MIN_OF(radiusD, minVal);
    aStart = Vertex(Vector2f(xPos + width - radiusA, yPos));
    aEnd = Vertex(Vector2f(xPos + radiusB, yPos));
    bStart = Vertex(Vector2f(xPos, yPos + radiusB));
    bEnd = Vertex(Vector2f(xPos, yPos + height - radiusC));
    cStart = Vertex(Vector2f(xPos + radiusC, yPos + height));
    cEnd = Vertex(Vector2f(xPos + width - radiusD, yPos + height));
    dStart = Vertex(Vector2f(xPos + width, yPos + height - radiusD));
    dEnd = Vertex(Vector2f(xPos + width, yPos + radiusA));
    numOfCoords = 4 * (2 + pointCount);
    gen_shape();
}
RoundedRectangle::RoundedRectangle(float xPos, float yPos, float width, float height, float radius, int pointCount) : RoundedRectangle(xPos, yPos, width, height, radius, radius, radius, radius, pointCount)
{
}

RoundedRectangle::RoundedRectangle(float xPos, float yPos, float width, float height, float radiusA, float radiusB, int pointCount) : RoundedRectangle(xPos, yPos, width, height, radiusA, radiusA, radiusB, radiusB, pointCount)
{
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
    circles[0] = CircleShape(radiusA, 30);
    circles[1] = CircleShape(radiusB, 30);
    circles[2] = CircleShape(radiusC, 30);
    circles[3] = CircleShape(radiusD, 30);
    //first curve
    double centreX = xPos + width - radiusA;
    double centreY = yPos + radiusA;
    Vertex *vertices = gen_curve(centreX, centreY, 0, radiusA);
    copy_to_shape(vertices);

    circles[index++].setPosition(centreX - radiusA, centreY - radiusA);

    roundedRect.push_back(aStart);
    roundedRect.push_back(aEnd);

    //second curve
    centreX = xPos + radiusB;
    centreY = yPos + radiusB;
    vertices = gen_curve(centreX, centreY, M_PI_2, radiusB);
    copy_to_shape(vertices);

    circles[index++].setPosition(centreX - radiusB, centreY - radiusB);

    roundedRect.push_back(bStart);
    roundedRect.push_back(bEnd);

    //third curve
    centreX = xPos + radiusC;
    centreY = yPos + height - radiusC;
    vertices = gen_curve(centreX, centreY, M_PI, radiusC);
    copy_to_shape(vertices);

    circles[index++].setPosition(centreX - radiusC, centreY - radiusC);

    roundedRect.push_back(cStart);
    roundedRect.push_back(cEnd);

    //fourth curve
    centreX = xPos + width - radiusD;
    centreY = yPos + height - radiusD;
    vertices = gen_curve(centreX, centreY, M_PI + M_PI_2, radiusD);
    copy_to_shape(vertices);

    circles[index++].setPosition(centreX - radiusD, centreY - radiusD);

    roundedRect.push_back(dStart);
    roundedRect.push_back(dEnd);
    r1 = RectangleShape(Vector2f(width - (radiusA + radiusB), height));
    r1.setPosition(Vector2f(xPos + radiusB, yPos));
    r2 = RectangleShape(Vector2f(width, height - (radiusB + radiusC)));
    r2.setPosition(Vector2f(xPos, yPos + radiusB));
}

Vertex *RoundedRectangle::gen_curve(double centreX, double centreY, double start, double radius)
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

void RoundedRectangle::set_radiusA(float radiusA)
{
    this->radiusA = radiusA;
}

void RoundedRectangle::set_radiusB(float radiusB)
{
    this->radiusB = radiusB;
}

void RoundedRectangle::set_radiusC(float radiusC)
{
    this->radiusC = radiusC;
}

void RoundedRectangle::set_radiusD(float radiusD)
{
    this->radiusD = radiusD;
}

int main(int argc, char **argv)
{
    RoundedRectangle r(80, 80, 100, 40, 10, 0, 7);
    RenderWindow *window = new RenderWindow(VideoMode(600, 600), "Test", Style::Close);
    r.set_fill_color(Color::White);
    r.set_outline_color(Color::Blue);
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