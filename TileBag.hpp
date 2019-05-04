#ifndef TILEBAG_H
#define TILEBAG_H

#include "Util.hpp"
#include <time.h>
#include <random>
class TileBag
{
private:
  LinkedList *tiles;
  int size;
public:
  TileBag();
  TileBag(int size, unsigned long seed);
  TileBag(const char *values);
  char get_tile();
  char get_tile(unsigned int index);
  void add_tile(char tile);
  void print();
  static int compare_tile(void *a, void *b);
  static char *to_string(void *val);
  int get_size();
  bool is_empty();
};
#endif