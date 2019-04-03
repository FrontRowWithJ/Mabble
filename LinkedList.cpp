#include "LinkedList.hpp"

LinkedList::LinkedList()
{
    head = NULL;
    tail = NULL;
}

void LinkedList::insert(void *val)
{
    if (head == NULL)
    {
        head = new Node();
        head->val = val;
        head->next = NULL;
        tail = head;
    }
    else
    {
        tail->next = new Node();
        tail->next->val = val;
        tail->next->next = NULL;
        tail = tail->next;
    }
}

bool LinkedList::contains(void *val)
{
    return find(val) != NULL;
}

bool LinkedList::remove(void *val)
{
    if (head == NULL)
        return false;
    Node *node = find(val);
    if (node == NULL)
        return false;
    if (node == head)
    {
        Node *n = head;
        free(n);
        head = head->next;
    }
    else if (node == tail)
    {
        Node *parent = get_parent(node);
        parent->next = new Node();
        tail = parent;
    }
    else
    {
        Node *p = get_parent(node);
        p->next = node->next;
        delete node;
    }
    return true;
}

Node *LinkedList::find(void *val)
{
    if (head == NULL)
        return NULL;
    for (Node *node = head; node != NULL; node = node->next)
        if (node->val == val)
            return node;
    return NULL;
}

Node *LinkedList::get_parent(Node *node)
{
    Node *n = head;
    for (; n->next != node; n = n->next)
        ;
    return n;
}

int LinkedList::count()
{
    return count_inner(head);
}

int LinkedList::count_inner(Node *node)
{
    return node == NULL ? 0 : 1 + count_inner(node->next);
}

bool LinkedList::swap(void *val1, void *val2)
{
    if (head == NULL || tail == NULL)
        return false;
    Node *node1 = find(val1);
    Node *node2 = find(val2);
    if (node1 == NULL || node2 == NULL)
        return false;
    void *tmp = node1->val;
    node1->val = node2->val;
    node2->val = tmp;
    return true;
}

bool LinkedList::llcat(LinkedList list)
{
    if (head == NULL && list.head == NULL)
        return false;
    if (head == NULL)
    {
        head = list.head;
        return true;
    }
    if (list.head == NULL)
        return false;
    tail->next = list.head;
    tail = list.tail;
    return true;
}

LinkedList LinkedList::reverse_list()
{
    return reverse_inner(head, LinkedList());
}

LinkedList LinkedList::reverse_inner(Node *node, LinkedList list)
{
    if (node == NULL)
    {
        reverse_inner(node->next, list);
        insert(list, node);
    }
}

void LinkedList::insert(LinkedList list, void *val)
{
    if (list.head == NULL)
    {
        list.head = (Node *)malloc(sizeof(Node));
        list.head->val = val;
        list.head->next = NULL;
        list.tail = list.head;
    }
    else
    {
        list.tail->next = (Node *)malloc(sizeof(Node));
        list.tail->next->val = val;
        list.tail->next->next = NULL;
        list.tail = list.tail->next;
    }
}

LinkedList LinkedList::clone()
{
    LinkedList l = LinkedList();
    for (Node *node = head; node != NULL; node = node->next)
        insert(l, node->val);
    return l;
}