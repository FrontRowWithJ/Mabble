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

bool LinkedList::contains(void *val, function<int(void *, void *)> compare)
{
    return find(val, compare) != NULL;
}

bool LinkedList::delete_node(void *val, function<int(void *, void *)> compare)
{
    if (head == NULL)
        return false;
    Node *node = find(val, compare);
    if (node == NULL)
        return false;
    if (compare(node->val, head->val) == EQUAL)
    {
        Node *n = head;
        head = head->next;
        delete n;
    }
    else if (compare(node->val, tail->val) == EQUAL)
    {
        Node *t = tail;
        Node *parent = get_parent(tail, compare);
        parent->next = NULL;
        tail = parent;
        delete t;
    }
    else
    {
        Node *p = get_parent(node, compare);
        p->next = node->next;
        delete node;
    }
    return true;
}

Node *LinkedList::find(void *val, function<int(void *, void *)> compare)
{
    if (head == NULL)
        return NULL;
    for (Node *node = head; node != NULL; node = node->next)
        if (compare(val, node->val) == EQUAL)
            return node;
    return NULL;
}

Node *LinkedList::get_parent(Node *node, function<int(void *, void *)> compare)
{
    Node *n = head;
    for (; !(compare(n->next->val, node->val) == EQUAL); n = n->next)
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

bool LinkedList::swap(void *val1, void *val2, function<int(void *, void *)> compare)
{
    if (head == NULL)
        return false;
    Node *node1 = find(val1, compare);
    Node *node2 = find(val2, compare);
    if (node1 == NULL || node2 == NULL)
        return false;
    void *tmp = node1->val;
    node1->val = node2->val;
    node2->val = tmp;
    return true;
}

bool LinkedList::swap(Node *node1, Node *node2)
{
    void *tmp = node1->val;
    node1->val = node2->val;
    node2->val = tmp;
}

bool LinkedList::llcat(LinkedList *list)
{
    if (head == NULL && list->head == NULL)
        return false;
    if (head == NULL)
    {
        head = list->head;
        return true;
    }
    if (list->head == NULL)
        return false;
    tail->next = list->head;
    tail = list->tail;
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

void LinkedList::print(function<char *(void *)> to_string)
{
    string result = "";
    for (Node *node = head; node != NULL; node = node->next)
    {
        result += to_string(node->val);
        result += ", ";
    }
    printf("%s\n", result.c_str());
}

void LinkedList::sort(function<int(void *, void *)> compare)
{
    //sorting a linked list
    for (Node *i = head; i != NULL; i = i->next)
        for (Node *j = i->next; j != NULL; j = j->next)
            if (compare(i->val, j->val) == GREATER_THAN)
                swap(i, j);
}

Node *LinkedList::remove(void *val, function<int(void *, void *)> compare)
{
    if (head == NULL)
        return NULL;
    Node *node = find(val, compare);
    if (node == NULL)
        return NULL;
    if (compare(node->val, head->val) == EQUAL)
    {
        Node *n = head;
        head = head->next;
        n->next = NULL;
        return n;
    }
    else if (compare(node->val, tail->val) == EQUAL)
    {
        Node *t = tail;
        Node *parent = get_parent(tail, compare);
        parent->next = NULL;
        tail = parent;
        t->next = NULL;
        return t;
    }
    else
    {
        Node *p = get_parent(node, compare);
        p->next = node->next;
        node->next = NULL;
        return node;
    }
    return NULL;
}