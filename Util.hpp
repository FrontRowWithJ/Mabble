#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include "LinkedList.hpp"
#include <functional>
#include <math.h>
#include <chrono>
#include <unistd.h>
// #include <SFML/Graphics.hpp>
#include "SFML-2.5.1/include/SFML/Graphics.hpp"
#include "SFML-2.5.1/include/SFML/System.hpp"
// #include <SFML/System.hpp>
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

#ifndef COLOR
#define COLOR(C) \
    Color((C >> 16) & 0xFF, (C >> 8) & 0xFF, C & 0xFF)
#endif

typedef unsigned char byte_t;
#endif
