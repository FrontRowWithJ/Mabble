#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#ifndef UTIL_H
#include "Util.hpp"
#endif

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
    bool contains(void *val);
    bool remove(void *val);
    Node *find(void *val);
    Node *get_parent(Node *node);
    int count();
    bool swap(void *val1, void *val2);
    bool llcat(LinkedList list);
    LinkedList reverse_list();
    LinkedList clone();
    
  private:
    int count_inner(Node *node);
    LinkedList reverse_inner(Node *node, LinkedList list);
    void insert(LinkedList list, void *val);
};

#endif