#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Util.hpp"
#include <functional>
#include <iostream>
#include <stdio.h>
#include <string.h>

#define LESS_THAN -1
#define EQUAL 0
#define GREATER_THAN 1
using namespace std;
class Node
{
public:
  void *val;
  Node *next;
};

class LinkedList
{
public:
  Node *head;
  Node *tail;

public:
  LinkedList();
  void insert(void *val);
  bool contains(void *val, function<int(void *, void *)> compare);
  bool delete_node(void *val, function<int(void *, void *)> compare);
  bool delete_node(Node *node);
  Node *remove(void *val, function<int(void *, void *)> compare);
  Node *find(void *val, function<int(void *, void *)> compare);
  Node *find(Node *node);
  Node *get_parent(Node *node, function<int(void *, void *)> compare);
  int count();
  bool swap(void *val1, void *val2, function<int(void *, void *)> compare);
  bool llcat(LinkedList *list);
  LinkedList reverse_list();
  LinkedList clone(function<void *(void *)> clone_of);
  void print(function<char *(void *)> to_string);
  void sort(function<int(void *, void *)> compare);
  void empty_list();
  void *pop();

private:
  int count_inner(Node *node);
  LinkedList reverse_inner(Node *node, LinkedList list);
  void insert(LinkedList list, void *val);
  bool swap(Node *node1, Node *node2);
  Node *get_parent(Node *node);
};

#endif