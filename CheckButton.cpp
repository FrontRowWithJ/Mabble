#include "CheckButton.hpp"
CheckButton::CheckButton()
{
}

CheckButton::CheckButton(float width, float height, float xPos, float yPos, Font font, float turnXPos, float turnYPos)
{
    this->width = width;
    this->height = height;
    this->xPos = xPos;
    this->yPos = yPos;
    this->font = font;
    this->turnsPassed = 0;
    this->isWinnerKnown = false;
    knownEquations = new LinkedList();
    gen_visuals(turnXPos, turnYPos);
    gen_text(turnXPos, turnYPos);
}

void CheckButton::check(float mousePosX, float mousePosY, float screenPosX, float screenPosY, Board board, LinkedList *placedTiles, Player *playerOne, Player *playerTwo, bool *isPlayerOne, float screenWidth, float screenHeight)
{
    float x = mousePosX - screenPosX + X_OFFSET;
    float y = mousePosY - screenPosY + Y_OFFSET;
    if (x >= xPos && x < xPos + width && y >= yPos && y < yPos + height)
    {
        if (*isPlayerOne)
            check_player(placedTiles, &board, playerOne, playerTwo, isPlayerOne);
        else
            check_player(placedTiles, &board, playerTwo, playerOne, isPlayerOne);
        if (is_game_over())
        {
            show_winner(playerOne, playerTwo, screenWidth, screenHeight);
            if (*isPlayerOne)
                playerOne->switch_turn();
            else
                playerTwo->switch_turn();
        }
    }
}

void CheckButton::gen_visuals(float turnXPos, float turnYPos)
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
    turnLable = new RoundedRectangle(turnXPos, turnYPos, 40, 20, 5, 10);
    turnLable->set_fill_color(Color::Red);
    turnLable->set_outline_color(Color::Blue);
}

void CheckButton::gen_text(float turnXpos, float turnYpos)
{
    text.setFont(font);
    text.setString("Check");
    text.setFillColor(textColor);
    text.setCharacterSize(height);
    FloatRect lb = text.getLocalBounds();
    text.setOrigin(lb.left - xPos - (width - lb.width) / 2.f, lb.top - yPos - (height - lb.height) / 2.f);

    turnText.setFont(font);
    turnText.setString("Your Turn");
    turnText.setFillColor(Color::Black);
    turnText.setCharacterSize(turnLable->get_height());
    lb = turnText.getLocalBounds();
    turnText.setOrigin(lb.left - turnXpos - (turnLable->get_width() - lb.width) / 2, lb.top - turnYpos - (turnLable->get_height() - lb.top) / 2);
}

void CheckButton::draw(RenderWindow *window)
{
    for (int i = 0; i < numOfVisuals; i++)
        window->draw(visuals[i]);
    window->draw(text);
    turnLable->draw(window);
    window->draw(turnText);
    if (isWinnerKnown)
    {
        winnerBoard->draw(window);
        window->draw(winnerText);
    }
}

CheckButton::Direction CheckButton::is_same_line(LinkedList *placedTiles, BoardTile ***table)
{
    TileData *pos = static_cast<TileData *>(placedTiles->head->val);
    int i = pos->i, j = pos->j, len = placedTiles->count();
    if (len == 1)
        return UNKOWN;
    Direction d;
    pos = static_cast<TileData *>(placedTiles->head->next->val);
    if (i == pos->i)
    {
        i = pos->i;
        d = RIGHT;
    }
    else if (j == pos->j)
    {
        j = pos->j;
        d = DOWN;
    }
    else
        return NEITHER;
    for (Node *node = placedTiles->head->next->next; node != NULL; node = node->next)
    {
        TileData *td = static_cast<TileData *>(node->val);
        if ((d == RIGHT ? td->i != i : td->j != j))
            return NEITHER;
    }
    return d;
}

int CheckButton::compare_right(void *a, void *b)
{
    TileData *td1 = static_cast<TileData *>(a);
    TileData *td2 = static_cast<TileData *>(b);
    return td1->j < td2->j ? -1 : td1->j == td2->j ? 0 : 1;
}

int CheckButton::compare_down(void *a, void *b)
{
    TileData *td1 = static_cast<TileData *>(a);
    TileData *td2 = static_cast<TileData *>(b);
    return td1->i < td2->i ? -1 : td1->i == td2->i ? 0 : 1;
}

bool CheckButton::is_isolated(TileData *td, BoardTile ***table, int rowLen)
{
    int i = td->i, j = td->j;
    if (i == rowLen / 2 && j == rowLen / 2)
        return false;
    if (i != 0 && table[i - 1][j]->get_state() != TILE_EMPTY)
        return false;
    if (j != 0 && table[i][j - 1]->get_state() != TILE_EMPTY)
        return false;
    if (i != rowLen - 1 && table[i + 1][j]->get_state() != TILE_EMPTY)
        return false;
    if (j != rowLen - 1 && table[i][j + 1]->get_state() != TILE_EMPTY)
        return false;
    return true;
}

bool CheckButton::are_tiles_contiguous(Direction d, BoardTile ***table, LinkedList *placedTiles, int rowLen)
{
    if (d == DOWN)
    {
        placedTiles->sort(compare_down);
        TileData *td1 = static_cast<TileData *>(placedTiles->head->val);
        TileData *td2 = static_cast<TileData *>(placedTiles->tail->val);
        int start = td1->i;
        int j = td1->j;
        int end = td2->i;
        for (int i = start; i < end; i++)
            if (table[i][j]->get_state() == TILE_EMPTY)
                return false;
        return true;
    }
    if (d == RIGHT)
    {
        placedTiles->sort(compare_right);
        TileData *td1 = static_cast<TileData *>(placedTiles->head->val);
        TileData *td2 = static_cast<TileData *>(placedTiles->tail->val);
        int start = td1->j;
        int i = td1->i;
        int end = td2->j;
        for (int j = start; j < end; j++)
            if (table[i][j]->get_state() == TILE_EMPTY)
                return false;
        return true;
    }
    if (d == UNKOWN)
        return !is_isolated(static_cast<TileData *>(placedTiles->head->val), table, rowLen);
}

LinkedList *CheckButton::gen_equation_list(BoardTile ***table, int rowLen, LinkedList *placedTiles)
{
    LinkedList *result = new LinkedList();
    for (Node *node = placedTiles->head; node != NULL; node = node->next)
    {
        TileData *td = static_cast<TileData *>(node->val);
        CheckButton::Position posRight = get_equation_begin_pos(CheckButton::RIGHT, table, td->i, td->j);
        CheckButton::Equation *equationRight = gen_equation(table, rowLen, CheckButton::RIGHT, posRight.i, posRight.j);
        void *castRight = static_cast<void *>(equationRight);
        if (equationRight->value.length() > 1 && !knownEquations->contains(castRight, compare_equation) && !result->contains(castRight, compare_equation))
            result->insert(castRight);
        CheckButton::Position posLeft = get_equation_begin_pos(CheckButton::DOWN, table, td->i, td->j);
        CheckButton::Equation *equationDown = gen_equation(table, rowLen, CheckButton::DOWN, posLeft.i, posLeft.j);
        void *castDown = static_cast<void *>(equationDown);
        if (equationDown->value.length() > 1 && !knownEquations->contains(castDown, compare_equation) && !result->contains(castDown, compare_equation))
            result->insert(castDown);
    }
    return result;
}

CheckButton::Position CheckButton::get_equation_begin_pos(CheckButton::Direction d, BoardTile ***table, int i, int j)
{
    int I = i, J = j;
    switch (d)
    {
    case DOWN:
        while (I != 0 && table[I - 1][J]->get_state() != TILE_EMPTY)
            I--;
        return (CheckButton::Position){I, J};
    case RIGHT:
        while (J != 0 && table[I][J - 1]->get_state() != TILE_EMPTY)
            J--;
        return (CheckButton::Position){I, J};
    }
    return (CheckButton::Position){-1, -1};
}

CheckButton::Equation *CheckButton::gen_equation(BoardTile ***table, int rowLen, CheckButton::Direction d, int startI, int startJ)
{
    CheckButton::Equation *eq = new CheckButton::Equation();
    string value = "";
    switch (d)
    {
    case CheckButton::DOWN:
        for (int i = startI; i < rowLen && table[i][startJ]->get_state() != TILE_EMPTY; i++)
            value.append(new char[2]{table[i][startJ]->get_value(), '\0'});
        *eq = (CheckButton::Equation){startI, startJ, CheckButton::DOWN, value};
        return eq;
    case CheckButton::RIGHT:
        for (int j = startJ; j < rowLen && table[startI][j]->get_state() != TILE_EMPTY; j++)
            value.append(new char[2]{table[startI][j]->get_value(), '\0'});
        *eq = (CheckButton::Equation){startI, startJ, CheckButton::RIGHT, value};
        return eq;
    }
}

int CheckButton::compare_equation(void *a, void *b)
{
    Equation *e1 = static_cast<Equation *>(a);
    Equation *e2 = static_cast<Equation *>(b);
    return *e1 == *e2 ? 0 : 1;
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
        Equation *eq = static_cast<Equation *>(node->val);
        result.append("(" + eq->value + ") isn't a valid equation\n");
        return result;
    }
    for (; node->next->next != NULL; node = node->next)
    {
        Equation *eq = static_cast<Equation *>(node->val);
        result += "(" + eq->value + "), ";
    }
    Equation *eq = static_cast<Equation *>(node->val);
    result += "(" + eq->value + ") and ";
    eq = static_cast<Equation *>(node->next->val);
    result += "(" + eq->value + ") aren't valid equations\n";
    return result;
}

void CheckButton::set_to_cant_remove(LinkedList *placedTiles, BoardTile ***table)
{
    for (Node *node = placedTiles->head; node != NULL; node = node->next)
    {
        TileData *td = static_cast<TileData *>(node->val);
        table[td->i][td->j]->set_state(TILE_FULL_PERM);
    }
}

evalResult_t *CheckButton::check_structure(LinkedList *equations, int *len)
{
    *len = equations->count();
    evalResult_t *results = new evalResult_t[*len];
    int i = 0;
    for (Node *node = equations->head; node != NULL; node = node->next)
    {
        Equation *eq = static_cast<Equation *>(node->val);
        results[i++] = check_equation(&eq->value);
    }
    return results;
}

bool CheckButton::are_equation_structure_valid(evalResult_t *resultCodes, int len)
{
    for (int i = 0; i < len; i++)
        if (resultCodes[i] != EVAL_VALID_EQUATION)
            return false;
    return true;
}

LinkedList *CheckButton::split_list(LinkedList *equations, evalResult_t *resultCodes, evalResult_t code)
{
    LinkedList *invalidEquations = new LinkedList();
    int i = 0;
    for (Node *node = equations->head; node != NULL;)
    {
        Node *n = node->next;
        if (resultCodes[i++] != code)
        {
            invalidEquations->insert(equations->remove(node->val, compare_equation)->val);
            node = n;
        }
        else
            node = node->next;
    }
    return invalidEquations;
}

evalResult_t *CheckButton::evaluate_equations(LinkedList *equations, long *totalScore, int *len)
{
    *len = equations->count();
    evalResult_t *results = new evalResult_t[*len];
    int i = 0;
    for (Node *node = equations->head; node != NULL; node = node->next)
    {
        Equation *eq = static_cast<Equation *>(node->val);
        *totalScore += evaluate(&eq->value, &results[i++]);
    }
    return results;
}

bool CheckButton::are_equations_balanced(evalResult_t *resultCodes, int len)
{
    for (int i = 0; i < len; i++)
        if (resultCodes[i] == EVAL_LEFT_DOES_NOT_EQUAL_RIGHT)
            return false;
    return true;
}

// After I check if there are any invalid equations
// If there are any invalid equations
// Then I split the list between valid and invalid equations
// I then print to the user the invalid equations and re request for the user to make a change
// If there are no invalid equations then I evaluate the equations to see if the left side is the same as the right side
// If there are some invalid equations I will prompt to the user that some of the equations are incorrect
// If not tell the user congrats and the give him/her their points

void CheckButton::check_player(LinkedList *placedTiles, Board *board, Player *player1, Player *player2, bool *isPlayerOne)
{
    if (placedTiles->head != NULL)
    {
        Direction d = is_same_line(placedTiles, board->get_table());
        if (d == RIGHT || d == DOWN)
        {
            if (are_tiles_contiguous(d, board->get_table(), placedTiles, board->get_rowLen()))
            {
                if (are_tiles_connected(placedTiles, board->get_table(), board->get_rowLen()))
                {
                    LinkedList *equationList = gen_equation_list(board->get_table(), board->get_rowLen(), placedTiles);
                    int len = 0;
                    evalResult_t *structureCodes = check_structure(equationList, &len);
                    if (are_equation_structure_valid(structureCodes, len))
                    {
                        int length = 0;
                        long score = 0;
                        evalResult_t *calcCodes = evaluate_equations(equationList, &score, &length);
                        if (are_equations_balanced(calcCodes, length))
                        {
                            //? Give the player his/her points.
                            //? End the turn and switch control to the other player
                            //? set tiles to perm
                            //? add the equations to known equations (saved to the board)
                            //! Check if the game is over.
                            player1->update_score(score);
                            player1->update_tileRack();
                            set_to_cant_remove(placedTiles, board->get_table());
                            placedTiles->empty_list();
                            knownEquations->llcat(equationList);
                            *isPlayerOne = !(*isPlayerOne);
                            player1->switch_turn();
                            player2->switch_turn();
                            move_turnLable(player2->get_xPos() + player2->get_width() / 2, turnLable->get_yPos());
                            turnsPassed++;
                            printf("turnsPassed: %d\n", turnsPassed);
                            printf("There are %d turns left.\n", MAX_NUMBER_OF_TURNS - turnsPassed / 2);
                        }
                        else
                        {
                            LinkedList *incurrEquations = split_list(equationList, structureCodes, EVAL_LEFT_DOES_NOT_EQUAL_RIGHT);
                            string incurrstatements = gen_incorrect_statement_string(incurrEquations);
                            cout << incurrstatements << endl;
                        }
                    }
                    else
                    {
                        LinkedList *incurrEquations = split_list(equationList, structureCodes, EVAL_VALID_EQUATION);
                        string incurrstatements = gen_incorrect_statement_string(incurrEquations);
                        cout << incurrstatements << endl;
                    }
                }
            }
        }
    }
}

bool CheckButton::are_tiles_connected(LinkedList *placedTiles, BoardTile ***table, int rowLen)
{
    for (Node *node = placedTiles->head; node != NULL; node = node->next)
    {
        TileData *td = static_cast<TileData *>(node->val);
        if (is_tile_positioned_correctly(td, table, rowLen))
            return true;
    }
    return false;
}

bool CheckButton::is_tile_positioned_correctly(TileData *td, BoardTile ***table, int rowLen)
{
    int i = td->i, j = td->j;
    if (i == rowLen / 2 && j == rowLen / 2)
        return true;
    if (i != 0 && table[i - 1][j]->get_state() == TILE_FULL_PERM)
        return true;
    if (j != 0 && table[i][j - 1]->get_state() == TILE_FULL_PERM)
        return true;
    if (i != rowLen - 1 && table[i + 1][j]->get_state() == TILE_FULL_PERM)
        return true;
    if (j != rowLen - 1 && table[i][j + 1]->get_state() == TILE_FULL_PERM)
        return true;
    return false;
}

char *CheckButton::to_string(void *a)
{
    Equation *eq = static_cast<Equation *>(a);
    char *result = new char[BUFFER_SIZE]();
    sprintf(result, "pos: (%d, %d), value: %s, direction: %s", eq->startI, eq->startJ, eq->value.c_str(), (int)eq->dir ? "RIGHT" : "DOWN");
    return result;
}

void CheckButton::add_to_known_equations(LinkedList *equations)
{
    knownEquations->llcat(equations);
}

void CheckButton::move_turnLable(float xPos, float yPos)
{
    turnLable->set_position(xPos, yPos);
    FloatRect lb = turnText.getLocalBounds();
    turnText.setOrigin(lb.left - xPos - (turnLable->get_width() - lb.width) / 2, lb.top - yPos - (turnLable->get_height() - lb.top) / 2);
}

void CheckButton::pass_turn()
{
    turnsPassed++;
}

bool CheckButton::is_game_over()
{
    return 2 * MAX_NUMBER_OF_TURNS == turnsPassed;
}

void CheckButton::show_winner(Player *p1, Player *p2, float width, float height)
{
    string anouncement;
    if (p1->get_score() > p2->get_score())
        anouncement = p1->get_playerName() + " wins!";
    else if (p2->get_score() > p1->get_score())
        anouncement = p2->get_playerName() + " wins!";
    else
        anouncement = "It's a draw!";
    winnerText.setFont(font);
    winnerText.setFillColor(Color::Green);
    winnerText.setCharacterSize(30);
    winnerText.setString(anouncement);
    FloatRect lb = winnerText.getLocalBounds();
    winnerBoard = new RoundedRectangle(width / 2.f - (lb.width * 1.3) / 2, height / 2.f - (lb.height * 1.3) / 2, lb.width * 1.3, lb.height * 1.3, 10, 10);
    winnerBoard->set_fill_color(Color::Black);
    winnerBoard->set_outline_color(Color::Magenta);
    winnerText.setOrigin(GET_ORIGIN(winnerBoard));
    isWinnerKnown = true;
}