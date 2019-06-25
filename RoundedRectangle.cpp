#include "RoundedRectangle.hpp"

RoundedRectangle::RoundedRectangle()
{
}

RoundedRectangle::RoundedRectangle(float xPos, float yPos, float width, float height, float radiusA, float radiusB, float radiusC, float radiusD, int pointCount) : ConvexShape(pointCount * 4)
{
    this->pos = Vector2f(xPos, yPos);
    this->setOrigin(xPos, yPos);
    this->setPosition(xPos, yPos);
    this->width = this->originalWidth = width;
    this->height = this->originalHeight = height;
    this->pointCount = pointCount;
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
        setFillColor(Color(0, 0, 0, 0));
        window->draw(shadow);
    }
    window->draw(*this);
}

void RoundedRectangle::gen_shape()
{
    int index = 0;
    Vector2f centrePos = Vector2f(pos.x + width - radiusA, pos.y + radiusA);
    Vector2f *vertices = gen_curve(centrePos, 0, radiusA);
    for (int i = 0; i < pointCount; index++, i++)
        setPoint(index, vertices[i]);
    delete[] vertices;
    centrePos = Vector2f(pos.x + radiusB, pos.y + radiusB);
    vertices = gen_curve(centrePos, M_PI_2, radiusB);
    for (int i = 0; i < pointCount; index++, i++)
        setPoint(index, vertices[i]);
    delete[] vertices;
    centrePos = Vector2f(pos.x + radiusC, pos.y + height - radiusC);
    vertices = gen_curve(centrePos, M_PI, radiusC);
    for (int i = 0; i < pointCount; index++, i++)
        setPoint(index, vertices[i]);
    delete[] vertices;
    centrePos = Vector2f(pos.x + width - radiusD, pos.y + height - radiusD);
    vertices = gen_curve(centrePos, M_PI + M_PI_2, radiusD);
    for (int i = 0; i < pointCount; index++, i++)
        setPoint(index, vertices[i]);
    delete[] vertices;
}

Vector2f *RoundedRectangle::gen_curve(Vector2f centrePos, double start, double radius)
{
    Vector2f *vertices = new Vector2f[pointCount];
    double inc = M_PI_2 / (double)pointCount;
    double theta = start;
    for (int i = 0; i < pointCount; i++)
    {
        double x = radius * cos(theta + i * inc);
        double y = radius * sin(theta + i * inc);
        vertices[i] = Vector2f(centrePos.x + x, centrePos.y - y);
    }
    return vertices;
}

void RoundedRectangle::set_fill_color(Color fillColor)
{
    this->fillColor = fillColor;
    setFillColor(fillColor);
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
    setOutlineColor(outlineColor);
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
    if (this->radiusA == radiusA)
        return;
    this->radiusA = radiusA;
    Vector2f centrePos(pos.x + width - radiusA, pos.y + radiusA);
    set_radius(centrePos, 0, radiusA);
}

void RoundedRectangle::set_radiusB(float radiusB)
{
    if (this->radiusB == radiusB)
        return;
    this->radiusB = radiusB;
    Vector2f centrePos(pos.x + radiusB, pos.y + radiusB);
    set_radius(centrePos, 1, radiusB);
}

void RoundedRectangle::set_radiusC(float radiusC)
{
    if (this->radiusC == radiusC)
        return;
    this->radiusC = radiusC;
    Vector2f centrePos(pos.x + radiusC, pos.y + height - radiusC);
    set_radius(centrePos, 2, radiusC);
}

void RoundedRectangle::set_radiusD(float radiusD)
{
    if (this->radiusD == radiusD)
        return;
    this->radiusD = radiusD;
    Vector2f centrePos(pos.x + width - radiusD, pos.y + height - radiusD);
    set_radius(centrePos, 3, radiusD);
}

void RoundedRectangle::set_radius(Vector2f centrePos, int quadrantPos, float radius)
{
    Vector2f *vertices = gen_curve(centrePos, quadrantPos * M_PI_2, radius);
    for (int index = 0; index < pointCount; index++)
        setPoint(quadrantPos * pointCount + index, vertices[index]);
    if (isShadowPresent)
        gen_shadow(shadowWidth);
}

float RoundedRectangle::set_position(float xPos, float yPos)
{
    pos = Vector2f(xPos, yPos);
    setPosition(xPos, yPos);
    if (isShadowPresent)
        shadow.setPosition(xPos, yPos);
}

void RoundedRectangle::gen_shadow(float shadowWidth)
{
    this->shadowWidth = shadowWidth;
    int index = 0;
    shadow.setOrigin(pos);
    shadow.setPosition(pos);
    Vector2f position = getPoint((int)(pointCount * 2.5));
    shadow.setPoint(index++, position);
    position = getPoint(3 * pointCount - 1) + shadowWidth;
    shadow.setPoint(index++, position);
    Vector2f centrePos = pos + Vector2f(width, height) - radiusD;
    Vector2f *curve = gen_curve(centrePos + shadowWidth, M_PI + M_PI_2, radiusD);
    for (int i = 0; i < pointCount; i++)
        shadow.setPoint(index++, curve[i]);
    delete[] curve;
    position = getPoint(0) + shadowWidth;
    shadow.setPoint(index++, position);
    position = getPoint((int)(pointCount * 0.5));
    shadow.setPoint(index++, position);
    for (int i = 0; i < pointCount / 2; i++)
        shadow.setPoint(index++, getPoint(pointCount / 2 + i));
    curve = gen_curve(pos + radiusB, M_PI_2, radiusB);
    for (int i = 0; i < pointCount; i++)
        shadow.setPoint(index++, curve[i]);
    delete[] curve;
    for (int i = 0; i < pointCount / 2; i++)
        shadow.setPoint(index++, getPoint(2 * pointCount + i));
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
    setScale(factorX, factorY);
    this->width = width;
    this->height = height;
}

void RoundedRectangle::set_thickness(float thickness)
{
    setOutlineThickness(thickness);
    if (isShadowPresent)
        shadow.setOutlineThickness(thickness);
}

void RoundedRectangle::set_radiusA_to_zero()
{
    if (isRadiusAZero)
        return;
    isRadiusAZero = true;
    this->radiusA = 0;
    ConvexShape newShape(this->getPointCount() - (pointCount - 1));
    newShape.setFillColor(this->getFillColor());
    newShape.setOrigin(this->getOrigin());
    newShape.setPosition(this->getPosition());
    newShape.setOutlineThickness(this->getOutlineThickness());
    newShape.setPoint(0, Vector2f(pos.x + width, pos.y));
    for (int i = pointCount; i < this->getPointCount(); i++)
        newShape.setPoint(i - (pointCount - 1), this->getPoint(i));
    int newPC = newShape.getPointCount();
    this->setPointCount(newPC);
    for (int i = 0; i < newPC; i++)
        setPoint(i, newShape.getPoint(i));
}

void RoundedRectangle::set_radiusB_to_zero()
{
    if (isRadiusBZero)
        return;
    isRadiusBZero = true;
    this->radiusB = 0;
    ConvexShape newShape(getPointCount() - (pointCount - 1));
    newShape.setFillColor(getFillColor());
    newShape.setOrigin(getOrigin());
    newShape.setPosition(getPosition());
    newShape.setOutlineThickness(getOutlineThickness());
    newShape.setPoint(isRadiusAZero ? 1 : pointCount, Vector2f(pos.x, pos.y));
    if (!isRadiusAZero)
    {
        for (int i = 0; i < pointCount; i++)
            newShape.setPoint(i, getPoint(i));
        for (int i = 2 * pointCount; i < getPointCount(); i++)
            newShape.setPoint(i - (pointCount - 1), getPoint(i));
    }
    else
    {
        newShape.setPoint(0, getPoint(0));
        for (int i = pointCount + 1; i < getPointCount(); i++)
            newShape.setPoint(i - (pointCount - 1), getPoint(i));
    }
    int newPC = newShape.getPointCount();
    setPointCount(newPC);
    for (int i = 0; i < newPC; i++)
        setPoint(i, newShape.getPoint(i));
}

void RoundedRectangle::set_radiusC_to_zero()
{
    if (isRadiusCZero)
        return;
    isRadiusCZero = true;
    this->radiusC = 0;
    ConvexShape newShape(getPointCount() - (pointCount - 1));
    newShape.setFillColor(getFillColor());
    newShape.setOrigin(getOrigin());
    newShape.setPosition(getPosition());
    newShape.setOutlineThickness(getOutlineThickness());
    int index = 0;
    if (isRadiusAZero)
        newShape.setPoint(index++, getPoint(0));
    else
        for (; index < pointCount; index++)
            newShape.setPoint(index, getPoint(index));
    int n = index;
    if (isRadiusBZero)
        newShape.setPoint(index++, getPoint(n));
    else
        for (; index < n + pointCount; index++)
            newShape.setPoint(index, getPoint(index));
    newShape.setPoint(index, Vector2f(pos.x, pos.y + height));
    index += pointCount;
    for (int i = index; i < getPointCount(); i++)
        newShape.setPoint(i - (pointCount - 1), getPoint(i));
    int newPC = newShape.getPointCount();
    setPointCount(newPC);
    for (int i = 0; i < newPC; i++)
        setPoint(i, newShape.getPoint(i));
}

void RoundedRectangle::set_radiusD_to_zero()
{
    if (isRadiusDZero)
        return;
    isRadiusDZero = true;
    this->radiusD = 0;
    ConvexShape newShape(getPointCount() - (pointCount - 1));
    newShape.setFillColor(getFillColor());
    newShape.setOrigin(getOrigin());
    newShape.setPosition(getPosition());
    newShape.setOutlineThickness(getOutlineThickness());
    for (int i = 0; i < getPointCount() - pointCount; i++)
        newShape.setPoint(i, getPoint(i));
    newShape.setPoint(newShape.getPointCount() - 1, Vector2f(pos.x + width, pos.y + height));
    int newPC = newShape.getPointCount();
    setPointCount(newPC);
    for (int i = 0; i < newPC; i++)
        setPoint(i, newShape.getPoint(i));
}

float RoundedRectangle::get_width()
{
    return width;
}

float RoundedRectangle::get_height()
{
    return height;
}

Vector2f RoundedRectangle::get_size()
{
    return Vector2f(width, height);
}