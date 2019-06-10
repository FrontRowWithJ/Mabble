#include "LinkedList.hpp"
// classes are going to have to have their own:
// equal operator
// less than
// greater than
// toString operator
// deep/shallow copy constructor
template <typename T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    tail = NULL;
}

template <typename T>
void LinkedList<T>::insert(T val)
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

template <typename T>
bool LinkedList<T>::contains(T val)
{
    return find(val) != NULL;
}

template <typename T>
bool LinkedList<T>::delete_node(T val)
{
    if (head == NULL)
        return false;
    Node *node = find(val);
    if (node == NULL)
        return false;
    if (node->val == head->val)
    {
        Node *n = head;
        head = head->next;
        delete n;
    }
    else if (node->val == tail->val)
    {
        Node *t = tail;
        Node *parent = get_parent(tail);
        parent->next = NULL;
        tail = parent;
        delete t;
    }
    else
    {
        Node *parent = get_parent(node);
        parent->next = node->next;
        delete node;
    }
    return true;
}

template <typename T>
bool LinkedList<T>::delete_node(Node *node)
{
    if (head == NULL)
        return false;
    if (node == NULL)
        return false;
    if (node == head)
    {
        head = head->next;
        delete node;
    }
    else if (node == tail)
    {
        Node *parent = get_parent(node);
        parent->next = NULL;
        tail = parent;
        delete node;
    }
    else
    {
        Node *parent = get_parent(node);
        parent->next = node->next;
        delete node;
    }
    return true;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::find(T val)
{
    if (head == NULL)
        return NULL;
    for (Node *node = head; node != NULL; node = node->next)
        if (node->val == val)
            return node;
    return NULL;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::find(Node *node)
{
    if (head == NULL)
        return NULL;
    Node *n = head;
    for (; n != NULL && n != node; n = n->next)
        ;
    return n;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::get_parent(Node *node)
{
    Node *n = head;
    for (; n->next != NULL && n->next != node; n = n->next)
        ;
    return n == tail ? NULL : n;
}

template <typename T>
int LinkedList<T>::count()
{
    return count_inner(head);
}

template <typename T>
int LinkedList<T>::count_inner(Node *node)
{
    return node == NULL ? 0 : 1 + count_inner(node->next);
}

template <typename T>
bool LinkedList<T>::swap(T val0, T val1)
{
    if (head == NULL)
        return false;
    Node *node0 = find(val0);
    Node *node1 = find(val1);
    if (node0 == NULL || node1 == NULL)
        return false;
    T tmp = node0->val;
    node0->val = node1->val;
    node1->val = tmp;
    return true;
}

template <typename T>
bool LinkedList<T>::swap(Node *node0, Node *node1)
{
    T tmp = node0->val;
    node0->val = node1->val;
    node1->val = tmp;
    return true;
}

template <typename T>
bool LinkedList<T>::llcat(LinkedList<T> *list)
{
    if (head == NULL || list->head == NULL)
        return false;
    tail->next = list->head;
    tail = list->tail;
}

template <typename T>
LinkedList<T> LinkedList<T>::reverse_list()
{
    LinkedList<T> list = LinkedList<T>();
    reverse_inner(head, &list);
    return list;
}

template <typename T>
void LinkedList<T>::reverse_inner(Node *node, LinkedList<T> *list)
{
    if (node != NULL)
    {
        reverse_inner(node->next, list);
        insert(list, node->val);
    }
}

template <typename T>
void LinkedList<T>::insert(LinkedList<T> *list, T val)
{
    if (list->head == NULL)
    {
        list->head = new Node();
        list->head->val = val;
        list->head->next = NULL;
        list->tail = list->head;
    }
    else
    {
        list->tail->next = new Node();
        list->tail->next->val = val;
        list->tail->next->next = NULL;
        list->tail = list->tail->next;
    }
}

template <typename T>
LinkedList<T> LinkedList<T>::clone()
{
    LinkedList<T> llist = LinkedList<T>();
    for (Node *node = head; node != NULL; node = node->next)
    {
        T copied = node->val;
        insert(&llist, copied);
    }
    return llist;
}

template <typename T>
void LinkedList<T>::print(function<char *(T)> c_str)
{
    string result = "";
    for (Node *node = head; node != NULL; node = node->next)
    {
        //for primitive data types?
        result += c_str == NULL ? node->val.c_str() : c_str(node->val);
        result += ", ";
    }
    printf("%s\n", result.substr(0, result.length() - 2).c_str());
}

template <typename T>
void LinkedList<T>::sort()
{
    for (Node *i = head; i != NULL; i = i->next)
        for (Node *j = i->next; j != NULL; j = j->next)
            if (i->val > j->val)
                swap(i, j);
}

template <typename T>
void LinkedList<T>::sort(function<int(T, T)> compare)
{
    for (Node *i = head; i != NULL; i = i->next)
        for (Node *j = i->next; j != NULL; j = j->next)
            if (compare(i->val, j->val) == GREATER_THAN)
                swap(i, j);
}
template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::remove(T val)
{
    if (head == NULL)
        return NULL;
    Node *node = find(val);
    if (node == NULL)
        return NULL;
    if (node->val == head->val)
    {
        Node *n = head;
        head = head->next;
        n->next = NULL;
        return n;
    }
    else if (node->val == tail->val)
    {
        Node *t = tail;
        Node *parent = get_parent(tail);
        parent->next = NULL;
        tail = parent;
        return t;
    }
    else
    {
        Node *parent = get_parent(node);
        parent->next = node->next;
        node->next = NULL;
        return node;
    }
}

template <typename T>
void LinkedList<T>::empty_list()
{
    while (head != NULL)
    {
        Node *h = head;
        head = head->next;
        delete h;
    }
    tail = NULL;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::pop()
{
    Node *h = head;
    head = head->next;
    h->next = NULL;
    return h;
}
