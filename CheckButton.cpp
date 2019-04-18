#include "CheckButton.hpp"

CheckButton::CheckButton()
{
}

CheckButton::CheckButton(float width, float height, float xPos, float yPos, Font font)
{
    this->width = width;
    this->height = height;
    this->xPos = xPos;
    this->yPos = yPos;
    this->font = font;
    gen_visuals();
    gen_text();
}

void CheckButton::check(float mousePosX, float mousePosY, float screenPosX, float screenPosY, Board board)
{
    float x = mousePosX - screenPosX + X_OFFSET;
    float y = mousePosY - screenPosY + Y_OFFSET;
    if (x >= xPos && x < yPos + width && y >= yPos && y < yPos + height)
    {
        //!do something
    }
}

void CheckButton::gen_visuals()
{
    numOfVisuals = 0;
    RectangleShape bg(Vector2f(width, height));
    bg.setPosition(Vector2f(xPos, yPos));
    bg.setFillColor(bgColor);
    numOfVisuals++;

    RectangleShape fg(Vector2f(width - 5.f, height - 5.f));
    fg.setPosition(Vector2f(xPos + 2.5, yPos + 2.5));
    fg.setFillColor(fgColor);
    numOfVisuals++;

    visuals = new RectangleShape[numOfVisuals];
    visuals[0] = bg;
    visuals[1] = fg;
}

void CheckButton::gen_text()
{
    text.setFont(font);
    text.setString("Check");
    text.setFillColor(textColor);
    text.setCharacterSize(height);
    text.setPosition(xPos + width / 5.f, yPos - height / 8.f);
}

void CheckButton::draw(RenderWindow *window)
{
    for (int i = 0; i < numOfVisuals; i++)
        window->draw(visuals[i]);
    window->draw(text);
}

CheckButton::Direction CheckButton::is_same_line(LinkedList *placedTiles, BoardTile **table)
{
    Board::TileData pos = *(Board::TileData *)placedTiles->head->val;
    int i = pos.i, j = pos.j, len = placedTiles->count();
    if (len == 1)
        return UNKOWN;
    Direction d;
    pos = *(Board::TileData *)placedTiles->head->next->val;
    if (i == pos.i)
    {
        i = pos.i;
        d = DOWN;
    }
    else if (j == pos.j)
    {
        j = pos.j;
        d = RIGHT;
    }
    else
        return NEITHER;

    if (d == RIGHT)
    {
        for (Node *node = placedTiles->head->next->next; node != NULL; node = node->next)
        {
            Board::TileData td = *(Board::TileData *)node->val;
            if (td.j == j)
                j = td.j;
            else
                return NEITHER;
        }
        return RIGHT;
    }
    else
    {
        for (Node *node = placedTiles->head->next->next; node != NULL; node = node->next)
        {
            Board::TileData td = *(Board::TileData *)node->val;
            if (td.i == i)
                i = td.i;
            else
                return NEITHER;
        }
        return DOWN;
    }
}

int CheckButton::compare_right(void *a, void *b)
{
    Board::TileData *td1 = (Board::TileData *)a;
    Board::TileData *td2 = (Board::TileData *)b;
    return (*td1).j < (*td1).j ? -1 : (*td1).j == (*td1).j ? 0 : 1;
}

int CheckButton::compare_down(void *a, void *b)
{
    Board::TileData *td1 = (Board::TileData *)a;
    Board::TileData *td1 = (Board::TileData *)b;
    return (*td1).i < (*td1).i ? -1 : (*td1).i == (*td1).i ? 0 : 1;
}

bool CheckButton::is_isolated(Board::TileData *td, BoardTile **table, int width)
{
    int i = td->i, j = td->j;
    if (i != 0 && table[i - 1][j].get_state() != TILE_EMPTY)
        return true;
    if (j != 0 && table[i][j - 1].get_state() != TILE_EMPTY)
        return true;
    if (i != width - 1 && table[i + 1][j].get_state() != TILE_EMPTY)
        return true;
    if (j != width - 1 && table[i][j + 1].get_state() != TILE_EMPTY)
        return true;
    return false;
}

bool CheckButton::are_tiles_contiguous(Direction d, BoardTile **table, LinkedList *placedTiles, int width)
{
    switch (d)
    {
    case DOWN:
        placedTiles->sort(compare_down);
        Board::TileData *td1 = (Board::TileData *)placedTiles->head;
        Board::TileData *td2 = (Board::TileData *)placedTiles->tail;
        int start = td1->i;
        int j = td1->j;
        int end = td2->i;
        for (int i = start; i < end; i++)
            if (table[i][j].get_state() == TILE_EMPTY)
                return false;
        return true;
    case RIGHT:
        placedTiles->sort(compare_right);
        Board::TileData *td1 = (Board::TileData *)placedTiles->head;
        Board::TileData *td2 = (Board::TileData *)placedTiles->tail;
        int start = td1->j;
        int i = td1->i;
        int end = td2->j;
        for (int j = start; j < end; j++)
            if (table[i][j].get_state() == TILE_EMPTY)
                return false;
        return true;
    case UNKOWN:
        return is_isolated((Board::TileData *)placedTiles->head, table, width);
        break;
    }
}

LinkedList *CheckButton::gen_equation_list(BoardTile **table, int width, LinkedList *placedTiles, LinkedList *knownEquations)
{
    LinkedList *result = new LinkedList();
    for (Node *node = placedTiles->head; node != NULL; node = node->next)
    {
        Board::TileData *td = (Board::TileData *)node->val;
        CheckButton::Position pos = get_equation_begin_pos(CheckButton::RIGHT, table, td->i, td->j);
        CheckButton::Equation *equationRight = gen_equation(table, width, CheckButton::RIGHT, pos.i, pos.j);
        if (equationRight->value.length() > 1 && knownEquations->find((void *)equationRight, compare_equation) == NULL)
            ;
        result->insert((void *)equationRight);
        pos = get_equation_begin_pos(CheckButton::DOWN, table, td->i, td->j);
        CheckButton::Equation *equationDown = gen_equation(table, width, CheckButton::DOWN, pos.i, pos.j);
        if (equationDown->value.length() > 1 && knownEquations->find((void *)equationDown, compare_right) == NULL)
            ;
        result->insert((void *)equationDown);
    }
    return result;
}

CheckButton::Position CheckButton::get_equation_begin_pos(CheckButton::Direction d, BoardTile **table, int i, int j)
{
    switch (d)
    {
    case DOWN:
        while (i != 0 && table[i - 1][j].get_state() != TILE_EMPTY)
            i--;
        return (CheckButton::Position){i, j};
    case RIGHT:
        while (j != 0 && table[i][j - 1].get_state() != TILE_EMPTY)
            j--;
        return (CheckButton::Position){i, j};
    }
    return (CheckButton::Position){-1, -1};
}

CheckButton::Equation *CheckButton::gen_equation(BoardTile **table, int width, CheckButton::Direction d, int startI, int startJ)
{
    if (d == CheckButton::DOWN)
    {
        string value = "";
        for (int i = startI; i < width && table[i][startJ].get_state() != TILE_EMPTY; i++)
        {
            char val[2] = {table[i][startJ].get_tile()->get_value(), '\0'};
            value.append(val);
        }
        return &(CheckButton::Equation){startI, startJ, CheckButton::DOWN, value};
    }
    else
    {
        string value = "";
        for (int j = startJ; j < width && table[startI][j].get_state() != TILE_EMPTY; j++)
        {
            char val[2] = {table[startI][j].get_tile()->get_value(), '\0'};
            value.append(val);
        }
        return &(CheckButton::Equation){startI, startJ, CheckButton::RIGHT, value};
    }
}

int CheckButton::compare_equation(void *a, void *b)
{
    Equation *e1 = (Equation *)a;
    Equation *e2 = (Equation *)b;
    return (e1->dir == e2->dir && e1->startI == e2->startJ && strcmp(e1->value.c_str(), e2->value.c_str()) == EQUAL) ? 0 : 1;
}

void CheckButton::filter_equation_list(LinkedList *equationList)
{
    for (Node *a = equationList->head; a->next != NULL; a = a->next)
    {
        for (Node *b = a->next; b != NULL;)
        {
            if (compare_equation(a->val, b->val) == EQUAL)
            {
                Node *t = b->next;
                equationList->remove(b, compare_equation);
                b = t;
            }
            else
            {
                b = b->next;
            }
        }
    }
}

string CheckButton::gen_incorrect_statement_string(LinkedList *equations)
{
    string result = string("Sorry but");
    int equationsLen = equations->count();
    Node *node = equations->head;
    if (equationsLen == 1)
    {
        string equation = *(string *)node->val;
        result.append("(" + equation + ") isn't a valid equation\n");
        return result;
    }
    for (; node->next->next != NULL; node = node->next)
    {
        string equation = *(string *)node->val;
        result += "(" + equation + "), ";
    }
    string equation = *(string *)node->val;
    result += "(" + equation + ") and ";
    equation = *(string *)node->next->val;
    result += "(" + equation + ") aren't valid equations\n";
    return result;
}

void CheckButton::set_to_cant_remove(LinkedList *placedTiles, BoardTile **table)
{
    for (Node *node = placedTiles->head; node != NULL; node = node->next)
    {
        Board::TileData *td = (Board::TileData *)node->val;
        table[td->i][td->j].set_state(TILE_FULL_PERM);
    }
}

evalResult_t *CheckButton::evaluate_equations(LinkedList *equations)
{
    int len = equations->count();
    evalResult_t *results = new evalResult_t[len];
    int i = 0;
    for (Node *node = equations->head; node != NULL; node = node->next)
        results[i++] = check_equation((string *)node->val);
    return results;
}

bool CheckButton::are_equations_valid(evalResult_t *resultCodes, int len)
{
    for (int i = 0; i < len; i++)
        if (resultCodes[i] != EVAL_VALID_EQUATION)
            return false;
    return true;
}

LinkedList *CheckButton::split_list(LinkedList *equations, evalResult_t *resultCodes)
{
    LinkedList *invalidEquations = new LinkedList();
    int i = 0;
    for (Node *node = equations->head; node != NULL;)
    {
        Node *n = node->next;
        if (resultCodes[i++] != EVAL_VALID_EQUATION)
        {
            invalidEquations->insert(equations->remove(node->val, compare_equation)->val);
            node = n;
        }
        else
        {
            i++;
            node = node->next;
        }
    }
    return invalidEquations;
}


//after I check if there are any invalid equations
//if there are any invalid equations
//then I split the list between valid and invalid equations
//I then print to the user the invalid equations and re request for the user to make a change
//If there are no invalid equations then I evaluate the equations to see if the left side is the same as the right side
//if there are some invalid equations I will prompt to the user that some of the equations are incorrect
//if not tell the user congrats and the give him/her their points