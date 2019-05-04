#include "TileBag.hpp"

TileBag::TileBag() : TileBag(0)
{
}

TileBag::TileBag(int size, unsigned long seed)
{
    srand(seed);
    tiles = new LinkedList();
    this->size = 0;
    for (int i = 0; i < size; i++)
        add_tile(static_cast<char>(CHARACTER_OFFSET + rand() % 10));
}

char TileBag::get_tile(unsigned int index)
{
    if (index >= size)
        return EMPTY;
    Node *node = tiles->head;
    for (int i = 0; i < index; i++)
        node = node->next;
    char tile = *static_cast<char *>(node->val);
    tiles->delete_node(node);
    size--;
    return tile;
}

TileBag::TileBag(const char *values)
{
    srand(time(NULL));
    this->tiles = new LinkedList();
    this->size = static_cast<int>(strlen(values));
    for (int i = 0; i < this->size; i++)
        tiles->insert(static_cast<void *>(new char[1]{values[i]}));
}

char TileBag::get_tile()
{
    return size == 0 ? EMPTY : get_tile(rand() % size);
}

int TileBag::compare_tile(void *a, void *b)
{
    return *static_cast<char *>(a) == *static_cast<char *>(b) ? 0 : 1;
}

void TileBag::add_tile(char tile)
{
    tiles->insert(static_cast<void *>(new char[1]{tile}));
    size++;
}

char *TileBag::to_string(void *val)
{
    return static_cast<char *>(realloc(val, 2));
}

void TileBag::print()
{
    tiles->print(to_string);
}

int TileBag::get_size()
{
    return size;
}

bool TileBag::is_empty()
{
    return size == 0;
}