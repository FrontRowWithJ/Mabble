#include "Maze.hpp"
Maze::Maze(size_t columnLen)
{
    srand(time(NULL));
    this->columnLen = columnLen & 1 == 0 ? columnLen + 1 : columnLen;
    columns = new LinkedList();
    displayColumn = new LinkedList();
    this->xPos = -40;
    this->yPos = 10;
    this->width = 40;
}

void Maze::display_matrix(RenderWindow *window)
{
    for (Node *node = displayColumn->head; node != NULL; node = node->next)
    {
        RoundedRectangle *rec = static_cast<RoundedRectangle *>(node->val);
        for (int i = 0; i < columnLen; i++)
            rec[i].draw(window);
    }
}

int Maze::get_height()
{
    return columnLen;
}

int Maze::get_width()
{
    return columns->count();
}

void Maze::gen_row()
{
    bool *column = new bool[columnLen];
    bool *connectorColumn = new bool[columnLen];
    for (int i = 0; i < columnLen; i += 2)
    {
        column[i] = true;
        connectorColumn[i] = rand() % 2 == 0;
    }
    for (int i = 1; i < columnLen; i += 2){
        column[i] = rand() % 2 == 0;
        connectorColumn[i] = false;
    }
    columns->insert(static_cast<void *>(column));
    columns->insert(static_cast<void *>(connectorColumn));
    update_display();
}

bool **Maze::to_matrix(size_t *width, size_t *height)
{
    *width = columns->count();
    *height = columnLen;
    bool **matrix = new bool *[*height];
    for (int i = 0; i < *height; i++)
        matrix[i] = new bool[*width];
    int j = 0;
    for (Node *node = columns->head; node != NULL; node = node->next)
    {
        bool *column = static_cast<bool *>(node->val);
        for (int i = 0; i < *height; i++)
            matrix[i][j] = column[i];
        j++;
    }
    return matrix;
}

void Maze::update_display()
{
    int width = columns->count();
    RoundedRectangle *columnRect = new RoundedRectangle[columnLen];
    Node *p = columns->get_parent(columns->tail);
    for (int j = width - 2; j < width; j++)
    {
        columnRect = new RoundedRectangle[columnLen];
        bool *column = static_cast<bool *>(p->val);
        for (int i = 0; i < columnLen; i++)
        {
            columnRect[i] = RoundedRectangle(xPos + j * this->width, yPos + i * this->width, this->width, this->width, 10, 10, 10, 10, 7);
            columnRect[i].set_fill_color(column[i] ? Color::Green : Color::Red);
            columnRect[i].set_outline_color(column[i] ? Color::Green : Color::Red);
        }
        p = p->next;
        displayColumn->insert(static_cast<void *>(columnRect));
    }
}

int main()
{
    Maze m(17);
    for(int i = 0; i < 17; i++)
        m.gen_row();
    RenderWindow *window = new RenderWindow(VideoMode(700, 700), "Window", Style::Close);
    Event e;
    while (window->isOpen())
    {
        while (window->pollEvent(e))
        {
            switch (e.type)
            {
            case Event::Closed:
                window->close();
                break;
            }
        }
        window->clear(Color::Black);
        m.display_matrix(window);
        window->display();
    }
}