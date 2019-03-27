#ifndef UTIL_H
#define UTIL_H
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"


#ifndef BOOLEAN
#define BOOLEAN
typedef int boolean;
enum
{
    FALSE,
    TRUE
};
#endif

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
typedef unsigned char byte_t;

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef ERROR
#define FAILURE 0
#endif
