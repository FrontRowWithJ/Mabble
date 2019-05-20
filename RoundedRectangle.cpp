#include "RoundedRectangle.hpp"

RoundedRectangle::RoundedRectangle()
{
}

RoundedRectangle::RoundedRectangle(float xPos, float yPos, float width, float height, float radiusA, float radiusB, float radiusC, float radiusD, int pointCount)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = this->originalWidth = width;
    this->height = this->originalHeight = height;
    this->pointCount = pointCount;
    this->roundedRect = ConvexShape(4 * pointCount);
    this->roundedRect.setOrigin(xPos, yPos);
    this->roundedRect.setPosition(xPos, yPos);
    float minVal = min(width, height) / 2;
    this->radiusA = MIN_OF(radiusA, minVal);
    this->radiusB = MIN_OF(radiusB, minVal);
    this->radiusC = MIN_OF(radiusC, minVal);
    this->radiusD = MIN_OF(radiusD, minVal);
    this->isShadowPresent = false;
    this->shadow = ConvexShape(4 + pointCount * 3);
    this->shadowWidth = 0;
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
    if (isShadowPresent)
    {
        roundedRect.setFillColor(Color(0, 0, 0, 0));
        window->draw(shadow);
    }
    window->draw(roundedRect);
}

void RoundedRectangle::gen_shape()
{
    int index = 0;
    double centreX = xPos + width - radiusA;
    double centreY = yPos + radiusA;
    //first curve
    Vector2f *vertices = gen_curve(centreX, centreY, 0, radiusA);
    for (int i = 0; i < pointCount; index++, i++)
        roundedRect.setPoint(index, vertices[i]);

    // second curve
    centreX = xPos + radiusB;
    centreY = yPos + radiusB;
    vertices = gen_curve(centreX, centreY, M_PI_2, radiusB);
    for (int i = 0; i < pointCount; index++, i++)
        roundedRect.setPoint(index, vertices[i]);

    //third curve
    centreX = xPos + radiusC;
    centreY = yPos + height - radiusC;
    vertices = gen_curve(centreX, centreY, M_PI, radiusC);
    for (int i = 0; i < pointCount; index++, i++)
        roundedRect.setPoint(index, vertices[i]);

    //fourth curve
    centreX = xPos + width - radiusD;
    centreY = yPos + height - radiusD;
    vertices = gen_curve(centreX, centreY, M_PI + M_PI_2, radiusD);
    for (int i = 0; i < pointCount; index++, i++)
        roundedRect.setPoint(index, vertices[i]);
    roundedRect.setOutlineThickness(1.f);
}

Vector2f *RoundedRectangle::gen_curve(double centreX, double centreY, double start, double radius)
{
    Vector2f *vertices = new Vector2f[pointCount];
    double inc = M_PI_2 / (double)pointCount;
    double theta = start;
    for (int i = 0; i < pointCount; i++)
    {
        double x = radius * cos(theta + i * inc);
        double y = radius * sin(theta + i * inc);
        vertices[i] = Vector2f(centreX + x, centreY - y);
    }
    return vertices;
}

void RoundedRectangle::set_fill_color(Color fillColor)
{
    this->fillColor = fillColor;
    roundedRect.setFillColor(fillColor);
    if (isShadowPresent)
        shadow.setFillColor(fillColor);
}

Color RoundedRectangle::get_fill_color()
{
    return fillColor;
}

void RoundedRectangle::set_outline_color(Color outlineColor)
{
    this->outlineColor = outlineColor;
    roundedRect.setOutlineColor(outlineColor);
    if (isShadowPresent)
        shadow.setOutlineColor(outlineColor);
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
    double centreX = xPos + width - radiusA;
    double centreY = yPos + radiusA;
    set_radius(centreX, centreY, 0, radiusA);
}

void RoundedRectangle::set_radiusB(float radiusB)
{
    this->radiusB = radiusB;
    float centreX = xPos + radiusB;
    float centreY = yPos + radiusB;
    set_radius(centreX, centreY, 1, radiusB);
}

void RoundedRectangle::set_radiusC(float radiusC)
{
    this->radiusC = radiusC;
    float centreX = xPos + radiusC;
    float centreY = yPos + height - radiusC;
    set_radius(centreX, centreY, 2, radiusC);
}

void RoundedRectangle::set_radiusD(float radiusD)
{
    this->radiusD = radiusD;
    float centreX = xPos + width - radiusD;
    float centreY = yPos + height - radiusD;
    set_radius(centreX, centreY, 3, radiusD);
}

void RoundedRectangle::set_radius(float centreX, float centreY, int quadrantPos, float radius)
{
    Vector2f *vertices = gen_curve(centreX, centreY, quadrantPos * M_PI_2, radius);
    for (int index = 0; index < pointCount; index++)
        roundedRect.setPoint(quadrantPos * pointCount + index, vertices[index]);
    if (isShadowPresent)
        gen_shadow(shadowWidth);
}

float RoundedRectangle::get_width()
{
    return width;
}

float RoundedRectangle::get_height()
{
    return height;
}

float RoundedRectangle::get_xPos()
{
    return xPos;
}

float RoundedRectangle::get_yPos()
{
    return yPos;
}

float RoundedRectangle::set_position(float xPos, float yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
    roundedRect.setPosition(xPos, yPos);
    if (isShadowPresent)
        shadow.setPosition(xPos, yPos);
}

void RoundedRectangle::gen_shadow(float shadowWidth)
{
    this->shadowWidth = shadowWidth;
    int index = 0;
    shadow.setOrigin(xPos, yPos);
    shadow.setPosition(xPos, yPos);
    Vector2f pos = roundedRect.getPoint((int)(pointCount * 2.5)) + 0.f;
    shadow.setPoint(index++, pos);

    pos = roundedRect.getPoint(3 * pointCount - 1) + shadowWidth;
    shadow.setPoint(index++, pos);
    float centreX = xPos + width - radiusD;
    float centreY = yPos + height - radiusD;
    Vector2f *curve = gen_curve(centreX + shadowWidth, centreY + shadowWidth, M_PI + M_PI_2, radiusD);
    for (int i = 0; i < pointCount; i++)
        shadow.setPoint(index++, curve[i]);
    delete[] curve;
    pos = roundedRect.getPoint(0) + shadowWidth;
    shadow.setPoint(index++, pos);
    pos = roundedRect.getPoint((int)(pointCount * 0.5)) + 0.f;
    shadow.setPoint(index++, pos);
    for (int i = 0; i < pointCount / 2; i++)
        shadow.setPoint(index++, roundedRect.getPoint(pointCount / 2 + i));
    curve = gen_curve(xPos + radiusB, yPos + radiusB, M_PI_2, radiusB);
    for (int i = 0; i < pointCount; i++)
        shadow.setPoint(index++, curve[i]);
    delete[] curve;
    for (int i = 0; i < pointCount / 2; i++)
        shadow.setPoint(index++, roundedRect.getPoint(2 * pointCount + i));
    set_shadow_color();
    shadow.setOutlineThickness(1.f);
    this->isShadowPresent = true;
}

void RoundedRectangle::set_shadow_color()
{
    if (isShadowPresent)
    {
        shadow.setFillColor(outlineColor);
        shadow.setOutlineColor(outlineColor);
    }
}

void RoundedRectangle::set_size(float width, float height)
{
    float factorX = width / originalWidth;
    float factorY = height / originalHeight;
    roundedRect.setScale(factorX, factorY);
    this->width = width;
    this->height = height;
}

void RoundedRectangle::set_thickness(float thickness)
{
    roundedRect.setOutlineThickness(thickness);
    if (isShadowPresent)
        shadow.setOutlineThickness(thickness);
}