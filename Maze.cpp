#include "Maze.hpp"
Maze::Maze(size_t columnLen, size_t screenWidth, size_t screenHeight)
{
    srand(time(NULL));
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->columnLen = columnLen & 1 == 0 ? columnLen + 1 : columnLen;
    columns = new LinkedList();
    displayColumn = new LinkedList();
    this->xPos = 10;
    this->yPos = 10;
    this->width = 30;
    this->panSpeed = .1;
    this->startPos = 0;
    this->displayPos = NULL;
    this->valPos = NULL;
    int numOfVisibleColumns = screenWidth / width + 1;
    int n = (numOfVisibleColumns / 2) * width;
    this->threshold = n - screenWidth;
    for (int i = 0; i < numOfVisibleColumns / 2; i++)
        gen_row();
}

void Maze::display_matrix(RenderWindow *window)
{
    for (Node *node = displayColumn->head; node != NULL; node = node->next)
    {
        RoundedRectangle *rec = static_cast<RoundedRectangle *>(node->val);
        for (int i = 0; i < columnLen; i++)
        {
            rec[i].draw(window);
            rec[i].set_position(rec[i].get_xPos() - panSpeed, rec[i].get_yPos());
        }
    }
    threshold += panSpeed;
    startPos += panSpeed;
    if (threshold >= 2 * width)
    {
        gen_row();
        threshold = 0;
    }
    if (startPos >= width)
    {
        displayColumn->delete_node(displayColumn->head);
        columns->delete_node(columns->head);
        startPos = 0;
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
    for (int i = 1; i < columnLen; i += 2)
    {
        column[i] = rand() % 2 == 0;
        connectorColumn[i] = false;
    }
    columns->insert(static_cast<void *>(column));
    columns->insert(static_cast<void *>(connectorColumn));
    update_display();
    if (displayPos != NULL)
        update_tile_corners();
    update_tile_corners();
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
    Node *t = displayColumn->tail;
    for (int j = width - 2; j < width; j++)
    {
        columnRect = new RoundedRectangle[columnLen];
        bool *column = static_cast<bool *>(p->val);
        for (int i = 0; i < columnLen; i++)
        {
            int x;
            if (t == NULL)
                x = xPos + j * this->width;
            else
            {
                RoundedRectangle *c = static_cast<RoundedRectangle *>(t->val);
                x = c->get_xPos() + this->width;
            }
            columnRect[i] = RoundedRectangle(x, yPos + i * this->width, this->width, this->width, 10, 10, 10, 10, 7);
            columnRect[i].set_fill_color(column[i] ? Color::Green : Color::Red);
            columnRect[i].set_outline_color(column[i] ? Color::Green : Color::Red);
        }
        p = p->next;
        displayColumn->insert(static_cast<void *>(columnRect));
        t = displayColumn->tail;
    }
}

void Maze::update_tile_corners()
{
    displayPos = displayPos == NULL ? displayColumn->head : displayPos->next;
    valPos = valPos == NULL ? columns->head : valPos->next;
    RoundedRectangle *rects = static_cast<RoundedRectangle *>(displayPos->val);
    bool *vals = static_cast<bool *>(valPos->val);

    // Checking left side
    Node *leftColumnVal = columns->get_parent(valPos);
    if (leftColumnVal != NULL)
    {
        bool *leftVals = static_cast<bool *>(leftColumnVal->val);
        for (int i = 0; i < columnLen; i++)
            if (leftVals[i] && vals[i])
            {
                rects[i].set_radiusB(0);
                rects[i].set_radiusC(0);
            }
    }
    // Checking right side
    Node *rightColumnVal = valPos->next;
    if (rightColumnVal != NULL)
    {
        bool *rightVals = static_cast<bool *>(rightColumnVal->val);
        for (int i = 0; i < columnLen; i++)
            if (rightVals[i] && vals[i])
            {
                rects[i].set_radiusA(0);
                rects[i].set_radiusD(0);
            }
    }
    // Checking top
    for (int i = 1; i < columnLen; i++)
        if (vals[i - 1] && vals[i])
        {
            rects[i].set_radiusA(0);
            rects[i].set_radiusB(0);
        }
    // Checking bottom
    for (int i = 0; i < columnLen - 1; i++)
        if (vals[i + 1] && vals[i])
        {
            rects[i].set_radiusC(0);
            rects[i].set_radiusD(0);
        }
}

int main()
{
    Color beige = COLOR(0x632b6c);
    Maze m(17, 700, 700);
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
        window->clear(beige);
        m.display_matrix(window);
        window->display();
    }
}