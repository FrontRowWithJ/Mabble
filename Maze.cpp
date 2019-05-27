#include "Maze.hpp"
Maze::Maze(size_t columnLen, size_t screenWidth, size_t screenHeight, Font f)
{
    srand(time(NULL));
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->columnLen = columnLen & 1 == 0 ? columnLen + 1 : columnLen;
    columns = new LinkedList();
    displayColumn = new LinkedList();
    this->xPos = 0;
    this->yPos = 0;
    this->width = 30;
    this->panSpeed = .3;
    this->startPos = -xPos;
    this->displayPos = NULL;
    this->valPos = NULL;
    this->f = f;
    int numOfVisibleColumns = screenWidth / width;
    int n = (numOfVisibleColumns / 2) * width;
    this->threshold = n - screenWidth;
    this->nextColumn = new bool[this->columnLen];
    this->symbol = "0123456789-+=/*\0";
    for (int i = 0; i < numOfVisibleColumns / 2 + 1; i++)
        gen_column();
}

void Maze::display_matrix(RenderWindow *window)
{
    for (Node *node = displayColumn->head; node != NULL; node = node->next)
    {
        MazeTile *rec = static_cast<MazeTile *>(node->val);
        for (int i = 0; i < columnLen; i++)
        {
            rec[i].draw(window);
            rec[i].set_xPos(rec[i].get_xPos() - panSpeed);
        }
    }
    threshold += panSpeed;
    startPos += panSpeed;
    if (threshold >= 2 * width)
    {
        gen_column();
        threshold = 0;
    }
    if (startPos >= width)
    {
        displayColumn->delete_node(displayColumn->head, delete_rect);
        columns->delete_node(columns->head, delete_bool);
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

void Maze::gen_column()
{
    bool *column = new bool[columnLen];
    bool *connectorColumn = new bool[columnLen];
    for (int i = 0; i < columnLen; i += 2)
    {
        column[i] = oof ? nextColumn[i] : true;
        connectorColumn[i] = rand() % 2 == 0;
    }
    for (int i = 1; i < columnLen; i += 2)
    {
        column[i] = oof ? nextColumn[i] : rand() % 2 == 0;
        connectorColumn[i] = false;
    }
    for (int i = 0; i < columnLen; i += 2)
        nextColumn[i] = true;
    for (int i = 1; i < columnLen; i += 2)
        nextColumn[i] = rand() % 2 == 0;
    columns->insert(static_cast<void *>(column));
    columns->insert(static_cast<void *>(connectorColumn));
    update_display();
    oof = true;
}

void Maze::update_display()
{
    int width = columns->count();
    MazeTile *columnRect = new MazeTile[columnLen];
    Node *p = columns->get_parent(columns->tail);
    Node *t = displayColumn->tail;
    Node *valNode = columns->get_parent(p);
    bool *leftColumn = NULL;
    if (valNode != NULL)
        leftColumn = static_cast<bool *>(valNode->val);
    for (int j = width - 2; j < width; j++)
    {
        columnRect = new MazeTile[columnLen];
        bool *column = static_cast<bool *>(p->val);
        MazeTile *c;
        bool *rightVal;
        if (j == width - 2)
            rightVal = static_cast<bool *>(columns->tail->val);
        else
            rightVal = nextColumn;
        if (t != NULL)
        {
            c = static_cast<MazeTile *>(t->val);
        }
        for (int i = 0; i < columnLen; i++)
        {
            columnRect[i] = MazeTile(t == NULL ? xPos : c[i].get_xPos() + this->width, yPos + i * this->width, this->width, 10, f, symbol[rand() % strlen(symbol)], column[i]);
            if(column[i])
                columnRect[i].gen_text();
            if (i != 0 && column[i - 1] && column[i])
            {
                columnRect[i].set_radiusA(0);
                columnRect[i].set_radiusB(0);
            }
            if (i != columnLen - 1 && column[i + 1] && column[i])
            {
                columnRect[i].set_radiusC(0);
                columnRect[i].set_radiusD(0);
            }
            if (leftColumn != NULL && leftColumn[i] && column[i])
            {
                columnRect[i].set_radiusB(0);
                columnRect[i].set_radiusC(0);
            }
            if (rightVal[i] && column[i])
            {
                columnRect[i].set_radiusA(0);
                columnRect[i].set_radiusD(0);
            }
        }
        p = p->next;
        displayColumn->insert(static_cast<void *>(columnRect));
        t = displayColumn->tail;
        if (valNode == NULL)
            valNode = columns->head;
        else
            valNode = valNode->next;
        leftColumn = static_cast<bool *>(valNode->val);
    }
}

void Maze::update_tile_corners()
{
    if (oof)
    {
        displayPos = displayColumn->head;
        valPos = columns->head;
        oof = false;
    }
    for (int n = 0; n < 2; n++)
    {
        MazeTile *rects = static_cast<MazeTile *>(displayPos->val);
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
        displayPos = displayPos->next;
        valPos = valPos->next;
    }
}

// int main()
// {
//     Color beige = COLOR(0x632b6c);
//     RenderWindow *window = new RenderWindow(VideoMode(700, 700), "Window", Style::Close);
//     Maze m((700 + 30 - 1) / 30, 700, 700);
//     Event e;
//     while (window->isOpen())
//     {
//         while (window->pollEvent(e))
//         {
//             switch (e.type)
//             {
//             case Event::Closed:
//                 window->close();
//                 break;
//             }
//         }
//         window->clear(Color::Black);
//         m.display_matrix(window);
//         window->display();
//     }
// }

void Maze::delete_rect(void *val)
{
    MazeTile *rect = static_cast<MazeTile *>(val);
    delete[] rect;
}

void Maze::delete_bool(void *val)
{
    bool *b = static_cast<bool *>(val);
    delete[] b;
}