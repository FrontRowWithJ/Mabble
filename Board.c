#include "Board.h"

int main()
{
    Square **board = malloc(10 * sizeof(Square *));
}

//expersions is equation without the equal symbol

//this defines the rules of a piece while it is the player's turn
void place_piece(char piece, Board board, int i, int j, LinkedList placedPieces)
{
    if (board.table[i][j].canPlace)
    {
        board.table[i][j].value = piece;
        board.table[i][j].canRemove = TRUE;
        Position p = (Position){i, j};
        insert(&placedPieces, (void *)&p);
    }
}

boolean is_idle(Board board, LinkedList placedPieces)
{
    //check if at least one of the pieces are next to a previously placed piece
    //first check all the values are on the same line
    //if(not the first piece)
    for (Node *node = placedPieces.head->next->next; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        int i = p.i;
        int j = p.j;
        if (i == board.width / 2 && j == board.width / 2)
            return FALSE;
        if (i - 1 > -1 && !board.table[i - 1][j].canRemove)
            return FALSE;
        if (i + 1 < board.width && !board.table[i + 1][j].canRemove)
            return FALSE;
        if (j - 1 > -1 && !board.table[i][j - 1].canRemove)
            return FALSE;
        if (j + 1 < board.width && !board.table[i][j + 1].canRemove)
            return FALSE;
    }
    return TRUE;
}

boolean is_same_line(LinkedList placedPieces, Board board)
{
    Position pos = *(Position *)placedPieces.head->val;
    int i = pos.i, j = pos.j, length = count(placedPieces.head);
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
                        return FALSE;
                }
            for (int jPos = minJ; jPos <= maxJ; jPos++)
                if (board.table[i][jPos].value == '\0')
                    return FALSE;
        }
        else if (nextPos.j == j)
        {
            if (length > 2)
                for (Node *node = placedPieces.head->next->next; node != NULL; node = node->next)
                {
                    Position p = *(Position *)node->val;
                    if (p.j != j)
                        return FALSE;
                }
            for (int iPos = minI; iPos <= maxI; iPos++)
                if (board.table[iPos][j].value == '\0')
                    return FALSE;
        }
        else
            return FALSE;
    }
    return TRUE;
}
void check_players_turn(LinkedList placedPieces, Board board, Line *boardLines, size_t len, evalResult_t *code)
{

    //check if the player has placed any pieces
    //check if at least one of the pieces are next to a previously placed piece
    if (placedPieces.head == NULL)
    {
        //*code = BOARD_NO_PLACED_PIECES
        return;
    }
    if (is_idle(board, placedPieces))
    {
        //*code = BOARD_NOT_ADJACENT_TO_ALREADY_PLACED_PIECE
        return;
    }
    //check if all the pieces are on the same line
    if (!is_same_line(placedPieces, board))
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
    LinkedList equations = (LinkedList){NULL, NULL};
    LinkedList results = (LinkedList){NULL, NULL};
    if (is_player_equations_valid(board, &equations, &results, &placedPieces))
    {
        //*code = BOARD_INVALID_EQUATIONS
        LinkedList incorrectEquations = remove_valid_equations(&equations, &results);
        char *incorrectEquationsStatement = gen_incorrect_statement_string(&incorrectEquations);
        ///do something with this sentence : that requires helping some SFML continue
    }
    else
    {
        //give the player his/her points -- player class
        //set the pieces placed to can't remove
        setToCantRemove(placedPieces, board);
        //end his/her turn -- SFML
        //evaluate if it's the end of the game -- GONNA NEED SOME RESEARCH Into that coz I don't know how to determine if more equations are possible or I could give each player a finite number of pieces?
        //swicth to the other player't turn -- SFML
    }
}

boolean is_player_equations_valid(Board board, LinkedList *equations, LinkedList *equationResults, LinkedList *placedPieces)
{

    //it should filter out the equations that arent correct
    for (Node *node = placedPieces->head; node != NULL; node = node->next)
    {
        Position pos = *(Position *)node->val;
        Position leftStart = get_equation_begin_pos(board, RIGHT, pos.i, pos.j);
        char *equation = get_equation(board, leftStart, RIGHT);
        if (strlen(equation) > 1)
        {
            insert(equations, (void *)equation);
            evalResult_t code;
            evaluate(equation, &code);
            insert(equationResults, (void *)&code);
        }
        Position topStart = get_equation_begin_pos(board, DOWN, pos.i, pos.j);
        equation = get_equation(board, topStart, DOWN);
        if (strlen(equation) > 1)
        {
            insert(equations, (void *)equation);
            evalResult_t code;
            evaluate(equation, &code);
            insert(equationResults, (void *)&code);
        }
    }
    for (Node *node = equationResults->head; node != NULL; node = node->next)
    {
        evalResult_t result = *(evalResult_t *)node->val;
        if (result != EVAL_SUCCESS)
            return FALSE;
    }
    return TRUE;
}

Board init_board(size_t width)
{
    Square **table = malloc(width * sizeof(Square *));
    for (int i = 0; i < width; i++)
        table[i] = malloc(width * sizeof(Square));
    for (int i = 0; i < width; i++)
        for (int j = 0; j < width; j++)
            table[i][j] = (Square){EMPTY, TRUE, TRUE, FALSE};
    Board b = (Board){table, width};
    return b;
}

Position get_equation_begin_pos(Board board, Direction d, int i, int j)
{
    switch (d)
    {
    case DOWN:
        while (i - 1 > -1 && board.table[i - 1][j].value != EMPTY)
            i--;
        return (Position){i, j};
    case RIGHT:
        while (j - 1 > -1 && board.table[i][j - 1].value != EMPTY)
            j--;
        return (Position){i, j};
    }
}

char *get_equation(Board board, Position p, Direction d)
{
    char *result = calloc(board.width, sizeof(char));
    int len = 0;
    int i = p.i, j = p.j;
    switch (d)
    {
    case RIGHT:
        while (j + 1 < board.width && j + 1 != '\0')
            result[len++] = board.table[i][j++].value;
        result = realloc(result, (len + 1) * sizeof(char));
        return result;
    case DOWN:
        while (i + 1 < board.width && i + 1 != '\0')
            result[len++] = board.table[i++][j].value;
        result = realloc(result, (len + 1) * sizeof(char));
        return result;
    }
}

char *gen_incorrect_statement_string(LinkedList *equations)
{
    char *result = calloc(BUFFER_SIZE, sizeof(char));
    int equationsLen = count(equations->head);
    strcpy(result, "Sorry but ");
    Node *node = equations->head;
    char *equation;
    if (equationsLen == 1)
    {
        char *bracketedEquation = calloc(MAX_BOARD_SIZE, sizeof(char));
        equation = (char *)node->val;
        sprintf(bracketedEquation, "(%s) ", equation);
        strcat(result, bracketedEquation);
        strcat(result, "isn't a valid equation\n");
        free(bracketedEquation);
        return result;
    }
    for (; node->next->next != NULL; node = node->next)
    {
        char *bracketedEquation = calloc(MAX_BOARD_SIZE, sizeof(char));
        equation = (char *)node->val;
        sprintf(bracketedEquation, "(%s), ", equation);
        strcat(result, equation);
    }
    equation = (char *)node->val;
    char *bracketedEquation = calloc(MAX_BOARD_SIZE, sizeof(char));
    sprintf(bracketedEquation, "(%s) and ", equation);
    strcat(result, bracketedEquation);
    equation = (char *)node->next->val;
    sprintf(bracketedEquation, "(%s) aren't valid equations\n", equation);
    strcat(result, bracketedEquation);
    return result;
}

LinkedList remove_valid_equations(LinkedList *equations, LinkedList *equationResult)
{
    LinkedList reducedList = (LinkedList){NULL, NULL};
    for (Node *e = equations->head, *er = equationResult->head; e != NULL || er != NULL; e = e->next, er = er->next)
    {
        evalResult_t res = *(evalResult_t *)er->val;
        if (res != EVAL_SUCCESS)
            insert(&reducedList, e->val);
    }
    return reducedList;
}

int get_min_i(LinkedList placedPieces)
{
    int i = MAX_BOARD_SIZE;
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        i = p.i < i ? p.i : i;
    }
    return i;
}

int get_max_i(LinkedList placedPieces)
{
    int i = -1;
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        i = p.i > i ? p.i : i;
    }
    return i;
}

int get_min_j(LinkedList placedPieces)
{
    int j = MAX_BOARD_SIZE;
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        j = p.j < j ? p.j : j;
    }
    return j;
}

int get_max_j(LinkedList placedPieces)
{
    int j = MAX_BOARD_SIZE;
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        j = p.j < j ? p.j : j;
    }
    return j;
}

void setToCantRemove(LinkedList placedPieces, Board board)
{
    for (Node *node = placedPieces.head; node != NULL; node = node->next)
    {
        Position p = *(Position *)node->val;
        board.table[p.i][p.j].canRemove = FALSE;
    }
}