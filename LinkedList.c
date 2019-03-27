#include "LinkedList.h"

void insert(LinkedList *llist, void *val)
{
    if (llist->head == NULL)
    {
        llist->head = (Node *)malloc(sizeof(Node));
        llist->head->val = val;
        llist->head->next = NULL;
        llist->tail = llist->head;
    }
    else
    {
        llist->tail->next = (Node *)malloc(sizeof(Node));
        llist->tail->next->val = val;
        llist->tail->next->next = NULL;
        llist->tail = llist->tail->next;
    }
}

boolean contains(Node *head, void *val)
{
    return find_node(head, val) != NULL;
}

boolean remove_node(LinkedList *llist, void *val)
{
    if (llist->head == NULL)
        return FALSE;
    Node *node = find_node(llist->head, val);
    if (node == NULL)
        return FALSE;
    if (node == llist->head)
    {
        Node *n = llist->head;
        free(n);
        llist->head = llist->head->next;
    }
    else if (node == llist->tail)
    {
        Node *parent = get_parent(llist->head, node);
        parent->next = malloc(sizeof(Node));
        llist->tail = parent;
    }
    else
    {
        Node *p = get_parent(llist->head, node);
        p->next = node->next;
        free(node);
    }
    return TRUE;
}

Node *find_node(Node *head, void *val)
{
    if (head == NULL)
        return NULL;
    for (Node *node = head; node->next != NULL; node = node->next)
    {
        if (node->val == val)
            return node;
    }
    return NULL;
}

Node *get_parent(Node *head, Node *node)
{
    for (Node *n = head; n->next != NULL; n = n->next)
        if (n->next == node)
            return n;
}

int count(Node *head)
{
    return head == NULL ? 0 : 1 + count(head->next);
}

boolean swap(LinkedList *llist, void *val1, void *val2)
{
    if (llist == NULL || llist->tail == NULL)
        return FALSE;
    Node *node1 = find_node(llist->head, val1);
    Node *node2 = find_node(llist->head, val2);
    if (node1 == NULL || node2 == NULL)
        return FALSE;
    void *tmp = node1->val;
    node1->val = node2->val;
    node2->val = tmp;
    if (node1 == llist->tail)
        llist->tail->val = node1->val;
    if (node2 == llist->tail)
        llist->tail->val = node2->val;
    return TRUE;
}

//joins the 2 linked lists and stores it in the linked List
boolean llcat(LinkedList *llist1, LinkedList *llist2)
{
    if (llist1 == NULL || llist2 == NULL)
        return FALSE;
    if (llist1->head == NULL)
    {
        llist1->head = llist2->head;
        return TRUE;
    }
    if (llist2->head == NULL)
        return TRUE;
    llist1->tail->next = llist2->head;
    llist1->tail = llist2->tail;
}

LinkedList *reverse_list(Node *node, LinkedList *llist)
{
    if (node != NULL)
    {
        reverse_list(node->next, llist);
        insert(llist, node->val);
    }
    return llist;
}

LinkedList copy_of(LinkedList *llist)
{
    LinkedList ll = (LinkedList){NULL, NULL};
    for (Node *node = llist->head; node != NULL; node = node->next)
        insert(&ll, node->val);
    return ll;
}
Node *reverse(Node *list)
{
    /* initialization */
    Node *reversed_list_head = 0;
    Node *rest_orig_list = list;

    /* build up the reversed_list like a stack while the original list
       remains */
    while (list != 0)
    {
        Node *orig_list_tail = list->next;
        /* the head of the remainder of the original list will be the
           new head of the new list */
        list->next = reversed_list_head;
        reversed_list_head = list;
        list = orig_list_tail;
    }
    return reversed_list_head;
}

void free_list(LinkedList *llist)
{
    Node *n = llist->head;
    while (n->next != NULL)
    {
        Node *tmpNode = n;
        n = n->next;
        free(tmpNode);
    }
    free(n);
    free(llist->head);
    free(llist->tail);
}
