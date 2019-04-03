#include "Board.hpp"

Board::Board(const size_t w)
{
    table = new Board::Square *[w];
    for (int i = 0; i < w; i++)
        table[i] = new Board::Square[w];
    for (int i = 0; i < w; i++)
        for (int j = 0; j < w; j++)
            table[i][j] = (Board::Square){EMPTY, true, false, false};
    width = w;
}

void Board::place_piece(char piece, int i, int j, LinkedList placedPieces)
{
    if (table[i][j].canPlace)
    {
        table[i][j].value = piece;
        table[i][j].canRemove = true;
        Position p = (Position){i, j};
        placedPieces.insert((void *)&p);
    }
}

bool Board::is_idle(LinkedList placedPieces)
{
    //check if at least one of the pieces are next to a previously placed piece
    //first check all the values are on the same line
    //if(not the first piece)
    for (Node *node = placedPieces.head->next->next; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        int i = p.i;
        int j = p.j;
        if (i == width / 2 && j == width / 2)
            return false;
        if (i - 1 > -1 && !table[i - 1][j].canRemove)
            return false;
        if (i + 1 < width && !table[i + 1][j].canRemove)
            return false;
        if (j - 1 > -1 && !table[i][j - 1].canRemove)
            return false;
        if (j + 1 < width && !table[i][j + 1].canRemove)
            return false;
    }
    return true;
}

bool Board::is_same_line(LinkedList placedPieces)
{
    Position pos = *(Position *)placedPieces.head->val;
    int i = pos.i, j = pos.j, length = placedPieces.count();
    int minI = get_min_i(placedPieces);
    int maxI = get_max_i(placedPieces);
    int minJ = get_min_j(placedPieces);
    int maxJ = get_max_j(placedPieces);
    if (length > 1)
    {
        Position nextPos = *(Position *)placedPieces.head->next->val;
        if (nextPos.i == i)
        {
            if (length > 2)
                for (Node *node = placedPieces.head->next->next; node != NULL; node = node->next)
                {
                    Position p = *(Position *)node->val;
                    if (p.i != i)
                        return false;
                }
            for (int jPos = minJ; jPos <= maxJ; jPos++)
                if (table[i][jPos].value == '\0')
                    return false;
        }
        else if (nextPos.j == j)
        {
            if (length > 2)
                for (Node *node = placedPieces.head->next->next; node != NULL; node = node->next)
                {
                    Position p = *(Position *)node->val;
                    if (p.j != j)
                        return false;
                }
            for (int iPos = minI; iPos <= maxI; iPos++)
                if (table[iPos][j].value == '\0')
                    return false;
        }
        else
            return false;
    }
    return true;
}

void Board::check_players_turn(LinkedList placedPieces, Equation *boardEquations, size_t len, evalResult_t *code)
{

    //check if the player has placed any pieces
    //check if at least one of the pieces are next to a previously placed piece
    if (placedPieces.head == NULL)
    {
        //*code = BOARD_NO_PLACED_PIECES
        return;
    }
    if (is_idle(placedPieces))
    {
        //*code = BOARD_NOT_ADJACENT_TO_ALREADY_PLACED_PIECE
        return;
    }
    //check if all the pieces are on the same line
    if (!is_same_line(placedPieces))
    {
        //*code = BOARD_NOT_IN_THE_SAME_LINE
        return;
    }
    //Check if the pieces placed by the player translates into valid statements
    //Remember that if all the pieces statements aren't valid then disregard the players attempt
    //How to do this:
    //Take a point placed by the player
    //trace back from that point to see where the corresponding starting points are
    //with the newly found starting points, check if their are valid for equations for all the points
    LinkedList equations = LinkedList();
    LinkedList results = LinkedList();
    if (is_player_equations_valid(equations, results, placedPieces))
    {
        //*code = BOARD_INVALID_EQUATIONS
        LinkedList incorrectEquations = remove_valid_equations(equations, results);
        string incorrectEquationsStatement = gen_incorrect_statement_string(incorrectEquations);
        ///do something with this sentence : that requires helping some SFML continue
    }
    else
    {
        //give the player his/her points -- player class
        //set the pieces placed to can't remove
        set_to_cant_remove(placedPieces);
        //port to cpp
        //end his/her turn -- SFML
        //evaluate if it's the end of the game -- GONNA NEED SOME RESEARCH Into that coz I don't know how to determine if more equations are possible or I could give each player a finite number of pieces?
        //swicth to the other player't turn -- SFML
    }
}

bool Board::is_player_equations_valid(LinkedList equations, LinkedList equationResults, LinkedList placedPieces)
{
    //it should filter out the equations that arent correct
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position pos = *(Position *)node->val;
        Position leftStart = get_equation_begin_pos(RIGHT, pos.i, pos.j);
        string equation = get_equation_as_string(leftStart, RIGHT);
        if (equation.length() > 1)
        {
            equations.insert((void *)&equation);
            evalResult_t code;
            evaluate(equation, &code);
            equationResults.insert((void *)&code);
        }
        Position topStart = get_equation_begin_pos(DOWN, pos.i, pos.j);
        equation = get_equation_as_string(topStart, DOWN);
        if (equation.length() > 1)
        {
            equations.insert((void *)&equation);
            evalResult_t code;
            evaluate(equation, &code);
            equationResults.insert((void *)&code);
        }
    }
    for (Node *node = equationResults.head; node != NULL; node = node->next)
    {
        evalResult_t result = *(evalResult_t *)node->val;
        if (result != EVAL_SUCCESS)
            return false;
    }
    return true;
}

Position Board::get_equation_begin_pos(Direction d, int i, int j)
{
    switch (d)
    {
    case DOWN:
        while (i - 1 > -1 && table[i - 1][j].value != EMPTY)
            i--;
        return (Position){i, j};
    case RIGHT:
        while (j - 1 > -1 && table[i][j - 1].value != EMPTY)
            j--;
        return (Position){i, j};
    }
}

string Board::get_equation_as_string(Position p, Direction d)
{
    string result = string();
    int i = p.i, j = p.j;
    switch (d)
    {
    case RIGHT:
        while (j + 1 < width && j + 1 != '\0')
        {
            char val[2] = {table[i][j++].value, '\0'};
            result.append(val);
        }
        return string(result);
    case DOWN:
        while (i + 1 < width && i + 1 != '\0')
        {
            char val[2] = {table[i++][j].value, '\0'};
            result.append(val);
        }
        return string(result);
    }
}

string Board::gen_incorrect_statement_string(LinkedList equations)
{
    string result = string("Sorry but");
    int equationsLen = equations.count();
    Node *node = equations.head;
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

LinkedList Board::remove_valid_equations(LinkedList equations, LinkedList equationResult)
{
    LinkedList reducedList = LinkedList();
    for (Node *e = equations.head, *er = equationResult.head; e != NULL || er != NULL; e = e->next, er = er->next)
    {
        evalResult_t res = *(evalResult_t *)er->val;
        if (res != EVAL_SUCCESS)
            reducedList.insert(e->val);
    }
    return reducedList;
}

int Board::get_min_i(LinkedList placedPieces)
{
    int i = MAX_BOARD_SIZE;
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        i = p.i < i ? p.i : i;
    }
    return i;
}

int Board::get_max_i(LinkedList placedPieces)
{
    int i = -1;
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        i = p.i > i ? p.i : i;
    }
    return i;
}

int Board::get_min_j(LinkedList placedPieces)
{
    int j = MAX_BOARD_SIZE;
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        j = p.j < j ? p.j : j;
    }
    return j;
}

int Board::get_max_j(LinkedList placedPieces)
{
    int j = MAX_BOARD_SIZE;
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        j = p.j < j ? p.j : j;
    }
    return j;
}

void Board::set_to_cant_remove(LinkedList placedPieces)
{
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        table[p.i][p.j].canRemove = false;
    }
}

void Board::get_statements(int i, int j, Position *vector_list, size_t *vector_len)
{
    if (i == 0 && table[i][j].value != '\0')
        vector_list[*vector_len++] = (Position){i, j};
    else if (j == 0 && table[i][j].value != '\0')
        vector_list[*vector_len++] = (Position){i, j};
    else if (j - 1 > -1 && table[i][j - 1].value == '\0' && j + 1 < width && table[i][j + 1].value != '\0')
    {
        vector_list[*vector_len] = (Position){i, j};
        *vector_len = *vector_len + 1;
    }
    else if (i - 1 > -1 && table[i - 1][j].value == '\0' && i + 1 < width && table[i + 1][j].value != '\0')
    {
        vector_list[*vector_len] = (Position){i, j};
        *vector_len = *vector_len + 1;
    }
    if (j - 1 > -1 && table[i][j - 1].value != '\0' && !table[i][j - 1].hasChecked)
    {
        table[i][j].hasChecked = true;
        get_statements(i, j - 1, vector_list, vector_len);
    }
    if (i - 1 > -1 && table[i - 1][j].value != '\0' && !table[i - 1][j].hasChecked)
    {
        table[i][j].hasChecked = true;
        get_statements(i - 1, j, vector_list, vector_len);
    }
    if (i + 1 < width && table[i + 1][j].value != '\0' && !table[i + 1][j].hasChecked)
    {
        table[i][j].hasChecked = true;
        get_statements(i + 1, j, vector_list, vector_len);
    }

    if (j + 1 < width && table[i][j + 1].value != '\0' && !table[i][j + 1].hasChecked)
    {
        table[i][j].hasChecked = true;
        get_statements(i, j + 1, vector_list, vector_len);
    }
}

void Board::clear_board()
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < width; j++)
            table[i][j].value = '\0';
}

void Board::uncheck_board()
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < width; j++)
            table[i][j].value = false;
}

void Board::print_vector_list(Position *list, size_t vector_len)
{
    for (int i = 0; i < vector_len; i++)
        printf("i: %d, j: %d\n", list[i].i, list[i].j);
}

Position *Board::filter_vector(Position *vector_list, size_t vector_len, size_t *new_len)
{
    Position *filteredList = new Position[vector_len];
    filteredList[0] = vector_list[0];
    size_t len = 1;
    for (int i = 1; i < vector_len; i++)
    {
        bool isPresent = false;
        for (int j = 0; j < len; j++)
        {
            if (IS_EQUALS(vector_list[i], filteredList[j]))
            {
                isPresent = true;
                break;
            }
        }
        if (!isPresent)
            filteredList[len++] = vector_list[i];
    }
    *new_len = len;
    return filteredList;
}

Board::Equation *Board::gen_board_equation(Position *listOfPositions, size_t vector_len, size_t *lineLen)
{
    LinkedList list = LinkedList();
    for (int index = 0; index < vector_len; index++)
    {
        int i = listOfPositions[index].i;
        int j = listOfPositions[index].j;
        if (j + 1 < width && table[i][j + 1].value != EMPTY)
        {
            Direction d = RIGHT;
            string statement = string();
            size_t statementLen;
            for (statementLen = 0; j + statementLen < width && table[i][j + statementLen].value != EMPTY; statementLen++)
                statement += table[i][j + statementLen].value;
            Position pos = (Position){i, j};
            Equation l = (Equation){pos, d, statement};
            list.insert((void *)&l);
        }
        if (i + 1 < width && table[i + 1][j].value != EMPTY)
        {
            Direction d = DOWN;
            string statement = string();
            size_t statementLen;
            for (statementLen = 0; j + statementLen < width && table[i + statementLen][j].value != EMPTY; statementLen++)
            {
                char val[2] = {table[i][j + statementLen].value, '\0'};
                statement.append(val);
            }
            Position pos = (Position){i, j};
            Equation l = (Equation){pos, d, statement};
            list.insert((void *)&l);
        }
    }
    return to_array(list, lineLen);
}

Board::Equation *Board::to_array(LinkedList list, size_t *arrayLen)
{
    *arrayLen = list.count();
    int i = 0;
    Equation *equations = new Equation[*arrayLen];
    for (Node *node = list.head; node != NULL; node = node->next)
        equations[i++] = *(Equation *)node->val;
    return equations;
}

Board::Equation Board::get_equation(Equation *lines, size_t len, int i, int j)
{
    for (int index = 0; index < len; index++)
    {
        Position p = lines[index].pos;
        if (p.i == i && p.j == j)
            return lines[index];
    }
    return (Equation){(Position){-1, -1}, RIGHT, NULL};
}