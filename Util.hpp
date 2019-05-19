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
#define BUFFER_SIZE 4096
#define X_OFFSET 2
#define Y_OFFSET 22
#define CHARACTER_OFFSET 0x30

#define MAX_BOARD_SIZE 151
#define EMPTY '\0'

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAILURE
#define FAILURE 0
#endif

typedef unsigned char byte_t;
#endif
