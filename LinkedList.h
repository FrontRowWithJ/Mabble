#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#endif

#include <stdlib.h>
#ifndef BOOLEAN
#define BOOLEAN
typedef int boolean;
enum
{
    FALSE,
    TRUE
};
#endif
typedef struct LinkedNode
{
    void *val;
    struct LinkedNode *next;
} Node;

typedef struct LList
{
    Node *head;
    Node *tail;
} LinkedList;

void insert(LinkedList *llist, void *val);
boolean contains(Node *head, void *val);
boolean remove_node(LinkedList *llist, void *val);
Node *find_node(Node *head, void *val);
Node *get_parent(Node *head, Node *node);
int count(Node *head);
boolean swap(LinkedList *llist, void *val1, void *val2);
boolean llcat(LinkedList *llist1, LinkedList *LList2);
LinkedList *reverse_list(Node *node, LinkedList *llist);
LinkedList copy_of(LinkedList *llist);
Node *reverse(Node *list);
void free_list(LinkedList *llist);