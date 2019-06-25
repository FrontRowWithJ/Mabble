#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Util.hpp"

#ifndef LESS_THAN
#define LESS_THAN -1
#endif

#ifndef EQUAL
#define EQUAL 0
#endif

#ifndef GREATER_THAN
#define GREATER_THAN 1
#endif

template <typename T>
class LinkedList
{
public:
    typedef struct LinkedListNode
    {
        T val;
        LinkedListNode *next;
    } Node;

public:
    Node *head;
    Node *tail;

public:
    LinkedList();
    //object dependant functions
    void insert(T val);
    bool contains(T val);
    bool delete_node(T val);
    bool delete_node(Node *node);
    Node *remove(T val);
    Node *find(T val);
    Node *find(Node *node);
    int count();
    bool swap(T val0, T val1);
    bool swap(Node *node0, Node *node1);
    bool llcat(LinkedList<T> *list);
    LinkedList reverse_list();
    LinkedList clone();
    void print(function<char *(T)> c_str);
    void print();
    void sort();
    void sort(function<int(T, T)> compare);
    void empty_list();
    Node *pop();
    Node *get_parent(Node *node);
    void move_to_top(T val);
private:
    int count_inner(Node *node);
    void reverse_inner(Node *node, LinkedList<T> *list);
    void insert(LinkedList<T> *list, T val);
};

#include "LinkedList.cpp"
#endif