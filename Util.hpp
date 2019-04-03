#ifndef UTIL_H
#define UTIL_H
#endif

#include <iostream>
#include <string>
#include "LinkedList.hpp"
using namespace std;

#ifndef POSITION
#define POSITION
typedef struct BoardPosition
{
    int i;
    int j;
} Position;
#endif

#define BUFFER_SIZE 4096

#define MAX_BOARD_SIZE 150
#define EMPTY '\0'

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAILURE
#define FAILURE 0
#endif

typedef unsigned char byte_t;
