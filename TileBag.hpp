#ifndef TILEBAG_H
#define TILEBAG_H

#include "Util.hpp"
#include "LinkedList.hpp"
#include <time.h>
#include <random>
class TileBag
{
private:
  LinkedList<char> *tiles;
  int size;

public:
  TileBag();
  TileBag(int size, unsigned long seed);
  TileBag(const char *values);
  char get_tile();
  char get_tile(unsigned int index);
  void add_tile(char tile);
  void print();
  static char *c_str(char c);
  int get_size();
  bool is_empty();
};
#endif