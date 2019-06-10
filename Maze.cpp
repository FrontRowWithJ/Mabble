#include "Maze.hpp"

Maze::Maze()
{
}

Maze::Maze(size_t columnLen, size_t screenWidth, size_t screenHeight, Font f)
{
    srand(time(NULL));
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->columnLen = columnLen & 1 == 0 ? columnLen + 1 : columnLen;
    columns = new LinkedList<bool *>();
    displayColumn = new LinkedList<Maze::RectArray>();
    textColumns = new LinkedList<Maze::TextArray>();
    this->xPos = 0;
    this->yPos = 0;
    this->currXPos = this->xPos;
    this->width = 30;
    this->panSpeed = .5;
    this->startPos = -xPos;
    this->displayPos = NULL;
    this->valPos = NULL;
    this->f = f;
    int numOfVisibleColumns = screenWidth / width;
    int n = (numOfVisibleColumns / 2) * width;
    this->threshold = n - screenWidth;
    this->nextColumn = new bool[this->columnLen];
    this->prevColumn = new bool[this->columnLen];
    this->symbol = "0123456789-+=/*\0";
    for (int i = 0; i < numOfVisibleColumns / 2 + 1; i++)
        gen_column();
}

void Maze::draw(RenderWindow *window)
{
    for (LinkedList<Maze::RectArray>::Node *node = displayColumn->head; node != NULL; node = node->next)
    {
        Maze::RectArray ra = node->val;
        for (int i = 0; i < ra.len; i++)
        {
            ra.rect[i].draw(window);
            ra.rect[i].set_position(ra.rect[i].get_xPos() - panSpeed, ra.rect[i].get_yPos());
        }
    }

    for (LinkedList<Maze::TextArray>::Node *node = textColumns->head; node != NULL; node = node->next)
    {
        Maze::TextArray ta = node->val;
        for (int i = 0; i < ta.len; i++)
        {
            window->draw(ta.texts[i]);
            ta.texts[i].setPosition(ta.texts[i].getPosition() - Vector2f(panSpeed, 0));
        }
    }

    currXPos -= panSpeed;
    threshold += panSpeed;
    startPos += panSpeed;
    if (threshold >= 2 * width)
    {
        gen_column();
        threshold = 0;
    }
    if (startPos >= width)
    {
        LinkedList<Maze::RectArray>::Node *td0 = displayColumn->pop();
        Maze::RectArray td1 = td0->val;
        delete[] td1.rect;
        delete td0;
        LinkedList<bool *>::Node *b = columns->pop();
        delete[] b->val;
        delete b;
        LinkedList<Maze::TextArray>::Node *t0 = textColumns->pop();
        Maze::TextArray t1 = t0->val;
        delete[] t1.texts;
        delete t0;
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
    if (oof)
    {
        bool *prevColumn = static_cast<bool *>(columns->tail->val);
        for (int i = 0; i < columnLen; i++)
            this->prevColumn[i] = prevColumn[i];
    }
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
    columns->insert(column);
    columns->insert(connectorColumn);
    gen_text_column();
    gen_column_visuals();
    oof = true;
}

void Maze::gen_column_visuals()
{
    int n = 0;
    Text t;
    LinkedList<bool *>::Node *tail = columns->tail;
    LinkedList<bool *>::Node *tailParent = columns->get_parent(columns->tail);
    bool *column0 = tailParent->val;
    bool *column1 = tail->val;
    Maze::RectArray *r0 = new Maze::RectArray(), *r1 = new Maze::RectArray();
    r0->len = 1;
    r1->len = 1;
    bool state0 = column0[0], state1 = column1[0];
    for (int i = 1; i < columnLen; i++)
    {
        if (state0 != column0[i] || !column0[i])
        {
            r0->len++;
            state0 = column0[i];
        }
        if (state1 != column1[i] || !column1[i])
        {
            r1->len++;
            state1 = column1[i];
        }
    }

    r0->rect = new RoundedRectangle[r0->len], r1->rect = new RoundedRectangle[r1->len];
    int index0 = 0, index1 = 0;
    int height0 = width, height1 = width;
    state0 = column0[0], state1 = column1[0];
    float yPos0 = 0, yPos1 = 0;
    for (int i = 1; i < columnLen; i++)
    {
        if (column0[i] != state0 || !column0[i])
        {
            int indexA = (int)(yPos0 / width);
            float radiusA = column0[indexA] && column1[indexA] ? 0 : 5;
            float radiusB = !oof ? 5 : prevColumn[indexA] && column0[indexA] ? 0 : 5;
            float radiusC = !oof ? 5 : prevColumn[i - 1] && column0[i - 1] ? 0 : 5;
            float radiusD = column0[i - 1] && column1[i - 1] ? 0 : 5;
            r0->rect[index0] = RoundedRectangle(currXPos, yPos0, width, height0, radiusA, radiusB, radiusC, radiusD, 7);
            r0->rect[index0++].set_fill_color(state0 ? COLOR(0xC76B98) : COLOR(0xFFFFFF));
            state0 = column0[i];
            yPos0 += height0;
            height0 = width;
        }
        else
        {
            height0 += width;
        }
        if (column1[i] != state1 || !column1[i])
        {
            int indexA = (int)(yPos1 / width);
            float radiusA = column1[indexA] && nextColumn[indexA] ? 0 : 5;
            float radiusB = column0[indexA] && column1[indexA] ? 0 : 5;
            float radiusC = column0[i - 1] && column1[i - 1] ? 0 : 5;
            float radiusD = column1[i - 1] && nextColumn[i - 1] ? 0 : 5;
            r1->rect[index1] = RoundedRectangle(currXPos + width, yPos1, width, height1, radiusA, radiusB, radiusC, radiusD, 7);
            r1->rect[index1++].set_fill_color(state1 ? COLOR(0xC76B98) : COLOR(0xFFFFFF));
            state1 = column1[i];
            yPos1 += height1;
            height1 = width;
        }
        else
        {
            height1 += width;
        }
    }
    int indexA = (int)(yPos0 / width);
    float radiusA = column0[indexA] && column1[indexA] ? 0 : 5;
    float radiusB = !oof ? 5 : prevColumn[indexA] && column1[indexA] ? 0 : 5;
    float radiusC = !oof ? 5 : prevColumn[columnLen - 1] && column1[columnLen - 1] ? 0 : 5;
    float radiusD = column0[columnLen - 1] && column1[columnLen - 1] ? 0 : 5;
    r0->rect[index0] = RoundedRectangle(currXPos, yPos0, width, height0, radiusA, radiusB, radiusC, radiusD, 7);
    r0->rect[index0].set_fill_color(state0 ? COLOR(0xC76B98) : COLOR(0xFFFFFF));
    r0->rect[index0].set_thickness(0);
    indexA = (int)(yPos1 / width);
    radiusA = column1[indexA] && nextColumn[indexA] ? 0 : 5;
    radiusB = column0[indexA] && column1[indexA] ? 0 : 5;
    radiusC = column0[columnLen - 1] && column1[columnLen - 1] ? 0 : 5;
    radiusD = column1[columnLen - 1] && nextColumn[columnLen - 1] ? 0 : 5;
    r1->rect[index1] = RoundedRectangle(currXPos + width, yPos1, width, height1, radiusA, radiusB, radiusC, radiusD, 7);
    r1->rect[index1].set_fill_color(state1 ? COLOR(0xC76B98) : COLOR(0xFFFFFF));
    r1->rect[index1].set_thickness(0);
    currXPos += 2 * width;
    displayColumn->insert(*r0);
    displayColumn->insert(*r1);
}

void Maze::delete_bool(void *val)
{
    bool *b = static_cast<bool *>(val);
    delete[] b;
}

void Maze::delete_RectArray(void *val)
{
    RectArray *ra = static_cast<RectArray *>(val);
    delete ra;
}

void Maze::delete_text(void *val)
{
    delete[] static_cast<TextArray *>(val);
}

void Maze::gen_text_column()
{
    Maze::TextArray *ta0 = new Maze::TextArray();
    Maze::TextArray *ta1 = new Maze::TextArray();
    Color operandColor = COLOR(0x270F36);
    Color operatorColor = COLOR(0x632B6C);
    ta0->len = 0;
    ta1->len = 0;
    LinkedList<bool *>::Node *tail = columns->tail;
    LinkedList<bool *>::Node *parentTail = columns->get_parent(columns->tail);
    bool *column0 = parentTail->val;
    bool *column1 = tail->val;
    for (int i = 0; i < columnLen; i++)
    {
        if (column0[i])
            ta0->len++;
        if (column1[i])
            ta1->len++;
    }
    ta0->texts = new Text[ta0->len];
    ta1->texts = new Text[ta1->len];
    int index0 = 0, index1 = 0;
    for (int i = 0; i < columnLen; i++)
    {
        if (column0[i])
        {
            char value = symbol[rand() % strlen(symbol)];
            ta0->texts[index0] = Text(new char[2]{value, '\0'}, f, width);
            FloatRect lb = ta0->texts[index0].getLocalBounds();
            ta0->texts[index0].setOrigin(SET_XPOS(currXPos, width), SET_YPOS((yPos + i * width), width));
            if (value >= '0' && value <= '9')
                ta0->texts[index0].setFillColor(operandColor);
            else if (value == '/' || value == '+' || value == '*' || value == '-')
                ta0->texts[index0].setFillColor(operatorColor);
            else
                ta0->texts[index0].setFillColor(Color::Black);
            index0++;
        }
        if (column1[i])
        {
            char value = symbol[rand() % strlen(symbol)];
            ta1->texts[index1] = Text(new char[2]{value, '\0'}, f, width);
            FloatRect lb = ta1->texts[index1].getLocalBounds();
            ta1->texts[index1].setOrigin(SET_XPOS((currXPos + width), width), SET_YPOS((yPos + i * width), width));
            if (value >= '0' && value <= '9')
                ta1->texts[index1].setFillColor(operandColor);
            else if (value == '/' || value == '+' || value == '*' || value == '-')
                ta1->texts[index1].setFillColor(operatorColor);
            else
                ta1->texts[index1].setFillColor(Color::Black);
            index1++;
        }
    }
    textColumns->insert(*ta0);
    textColumns->insert(*ta1);
}