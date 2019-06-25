#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <cstring>
#include <functional>
#include <math.h>
#include <chrono>
#include <unistd.h>
#include <cstdarg>
#include "SFML-2.5.1/include/SFML/Graphics.hpp"
#include "SFML-2.5.1/include/SFML/System.hpp"
using namespace std;
using namespace sf;
#ifndef POSITION
#define POSITION
typedef struct BoardPosition
{
    int i;
    int j;
} Position;
#endif

#ifndef MIN_OF
#define MIN_OF(X, Y) \
    X > Y ? Y : X
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
#endif

#ifndef X_OFFSET
#define X_OFFSET 2
#endif

#ifndef Y_OFFSET
#define Y_OFFSET 22
#endif

#ifndef CHARACTER_OFFSET
#define CHARACTER_OFFSET 0x30
#endif

#ifndef MAX_BOARD_SIZE
#define MAX_BOARD_SIZE 151
#endif

#ifndef EMPTY
#define EMPTY '\0'
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAILURE
#define FAILURE 0
#endif

#ifndef COLOR0
#define COLOR0(C) \
    Color((C >> 16) & 0xFF, (C >> 8) & 0xFF, C & 0xFF)
#endif

#ifndef COLOR1
#define COLOR1(C, A) \
    Color((C >> 16) & 0xFF, (C >> 8) & 0xFF, C & 0xFF, A % 255)
#endif

#ifndef GET_MACRO
#define GET_MACRO(_1, _2, NAME, ...) \
    NAME
#endif

#ifndef COLOR
#define COLOR(...)                         \
    GET_MACRO(__VA_ARGS__, COLOR1, COLOR0) \
    (__VA_ARGS__)
#endif

#ifndef SET_XPOS
#define SET_XPOS(X, Y) \
    lb.left - X - (Y - lb.width) / 2.f
#endif

#ifndef SET_YPOS
#define SET_YPOS(X, Y) \
    lb.top - X - (Y - lb.height) / 2.f
#endif

#ifndef BYTE_T
#define BYTE_T
typedef unsigned char byte_t;
#endif

#ifndef V2F_OPERATOR_OVERLOAD
#define V2F_OPERATOR_OVERLOAD
namespace vector_op
{

static Vector2f operator*(Vector2f left, Vector2f right)
{
    return Vector2f(left.x * right.x, left.y * right.y);
}

static Vector2f operator+(Vector2f left, Vector2f right)
{
    return Vector2f(left.x + right.x, left.y + right.y);
}

static Vector2f operator-(Vector2f left, Vector2f right)
{
    return Vector2f(left.x - right.x, left.y - right.y);
}

static Vector2f operator+(Vector2f v, float constant)
{
    return Vector2f(v.x + constant, v.y + constant);
}

static Vector2f operator-(Vector2f v, float constant)
{
    return Vector2f(v.x - constant, v.y - constant);
}

static Vector2f operator/(Vector2f v, float constant)
{
    return Vector2f(v.x / constant, v.y / constant);
}

static Vector2f operator*(Vector2f v, float constant)
{
    return Vector2f(v.x * constant, v.y * constant);
}

static Vector2f operator/(Vector2f left, Vector2f right)
{
    return Vector2f(left.x / right.x, left.y / right.y);
}

static bool operator>(Vector2f left, Vector2f right)
{
    return left.x > right.x && left.y > right.y;
}

static bool operator>=(Vector2f left, Vector2f right)
{
    return left.x >= right.x && left.y >= right.y;
}

static bool operator<(Vector2f left, Vector2f right)
{
    return left.x < right.x && left.y < right.y;
}

static bool operator<=(Vector2f left, Vector2f right)
{
    return left.x <= right.x && left.y <= right.y;
}

static void operator-=(Vector2f &left, const Vector2f &right)
{
    left = left - right;
}

static void operator/=(Vector2f &left, const Vector2f &right)
{
    left = left / right;
}

static void operator*=(Vector2f &left, const Vector2f &right)
{
    left = left * right;
}

static void operator/=(Vector2f &left, const float right)
{
    left.x /= right;
    left.y /= right;
}

static void operator+=(Vector2f &left, const float right)
{
    left.x *= right;
    left.y *= right;
}

static bool operator!=(Vector2i left, Vector2i right)
{
    return left.x != right.x || left.y != right.y;
}
} // namespace vector_op

#endif

#endif
