#include "TileBag.hpp"

TileBag::TileBag() : TileBag(0)
{
}

TileBag::TileBag(int size, unsigned long seed)
{
    srand(seed);
    tiles = new LinkedList<char>();
    this->size = size;
    for (int i = 0; i < size; i++)
        tiles->insert(static_cast<char>(CHARACTER_OFFSET + rand() % 10));
}

char TileBag::get_tile(unsigned int index)
{
    if (index >= size)
        return EMPTY;
    LinkedList<char>::Node *node = tiles->head;
    for (int i = 0; i < index; i++)
        node = node->next;
    char tile = node->val;
    tiles->delete_node(node);
    size--;
    return tile;
}

TileBag::TileBag(const char *values)
{
    srand(time(NULL));
    this->tiles = new LinkedList<char>();
    this->size = static_cast<int>(strlen(values));
    for (int i = 0; i < this->size; i++)
        tiles->insert(values[i]);
}

char TileBag::get_tile()
{
    return size == 0 ? EMPTY : get_tile(rand() % size);
}

void TileBag::add_tile(char tile)
{
    tiles->insert(tile);
    size++;
}

char *TileBag::c_str(char c)
{
    return new char[2]{c, '\0'};
}

void TileBag::print()
{
    tiles->print(NULL);
}

int TileBag::get_size()
{
    return size;
}

bool TileBag::is_empty()
{
    return size == 0;
}