#include "BoardChecker.h"

int main(int argc, char **argv)
{
    size_t len = 5;
    Square **board = calloc((len + 1), sizeof(Square *));
    for (int i = 0; i < len + 1; i++)
        board[i] = calloc(len, sizeof(Square));
    board[1][3] = (Square){'x', FALSE};
    board[2][3] = (Square){'x', FALSE};
    board[3][3] = (Square){'x', FALSE};
    board[3][4] = (Square){'x', FALSE};
    board[4][4] = (Square){'x', FALSE};
    for (int i = 1; i < 5; i++)
        board[2][i] = (Square){'x', FALSE};
    for (int i = 0; i < len + 1; i++)
    {
        for (int j = 0; j < len; j++)
            printf("%c", board[i][j].value ? 'x' : '0');
        printf("\n");
    }
    Position *vector_list = malloc(BUFFER_SIZE * sizeof(Position));
    size_t vector_len = 0;
    get_statements(2, 2, board, len, len + 1, vector_list, &vector_len);
    size_t filtered_vector_len = 0;
    Position *filtered_list = filter_vector(vector_list, vector_len, &filtered_vector_len);
    print_vector_list(filtered_list, filtered_vector_len);
}
void get_statements(int i, int j, Square **board, size_t width, size_t height, Position *vector_list, size_t *vector_len)
{
    if (i == 0 && board[i][j].value != '\0')
        vector_list[*vector_len++] = (Position){i, j};
    else if (j == 0 && board[i][j].value != '\0')
        vector_list[*vector_len++] = (Position){i, j};
    else if (j - 1 > -1 && board[i][j - 1].value == '\0' && j + 1 < width && board[i][j + 1].value != '\0')
    {
        vector_list[*vector_len] = (Position){i, j};
        *vector_len = *vector_len + 1;
    }
    else if (i - 1 > -1 && board[i - 1][j].value == '\0' && i + 1 < height && board[i + 1][j].value != '\0')
    {
        vector_list[*vector_len] = (Position){i, j};
        *vector_len = *vector_len + 1;
    }
    if (j - 1 > -1 && board[i][j - 1].value != '\0' && !board[i][j - 1].hasChecked)
    {
        board[i][j].hasChecked = TRUE;
        get_statements(i, j - 1, board, width, height, vector_list, vector_len);
    }
    if (i - 1 > -1 && board[i - 1][j].value != '\0' && !board[i - 1][j].hasChecked)
    {
        board[i][j].hasChecked = TRUE;
        get_statements(i - 1, j, board, width, height, vector_list, vector_len);
    }
    if (i + 1 < height && board[i + 1][j].value != '\0' && !board[i + 1][j].hasChecked)
    {
        board[i][j].hasChecked = TRUE;
        get_statements(i + 1, j, board, width, height, vector_list, vector_len);
    }

    if (j + 1 < width && board[i][j + 1].value != '\0' && !board[i][j + 1].hasChecked)
    {
        board[i][j].hasChecked = TRUE;
        get_statements(i, j + 1, board, width, height, vector_list, vector_len);
    }
}

void clear_board(Square **board, size_t width, size_t height)
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j].value = '\0';
}

void uncheck_board(Square **board, size_t width, size_t height)
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j].value = FALSE;
}

void print_vector_list(Position *list, size_t vector_len)
{
    for (int i = 0; i < vector_len; i++)
        printf("i: %d, j: %d\n", list[i].i, list[i].j);
}

Position *filter_vector(Position *vector_list, size_t vector_len, size_t *new_len)
{
    Position *filteredList = malloc(vector_len * sizeof(Position));
    filteredList[0] = vector_list[0];
    size_t len = 1;
    for (int i = 1; i < vector_len; i++)
    {
        boolean isPresent = FALSE;
        for (int j = 0; j < len; j++)
        {
            if (IS_EQUALS(vector_list[i], filteredList[j]))
            {
                isPresent = TRUE;
                break;
            }
        }
        if (!isPresent)
            filteredList[len++] = vector_list[i];
    }
    *new_len = len;
    return filteredList;
}

Line *gen_board_line(Square **board, size_t width, size_t height, Position *listOfPositions, size_t vector_len, size_t *lineLen)
{
    int len = 0;
    LinkedList list = (LinkedList){NULL, NULL};
    for (int index = 0; index < vector_len; index++)
    {
        int i = listOfPositions[index].i;
        int j = listOfPositions[index].j;
        if (j + 1 < width && board[i][j + 1].value != EMPTY)
        {
            Direction d = RIGHT;
            char *statement = calloc(MAX_BOARD_SIZE, sizeof(char));
            size_t statementLen;
            for (statementLen = 0; j + statementLen < width && board[i][j + statementLen].value != EMPTY; statementLen++)
                statement[statementLen] = board[i][j + statementLen].value;
            statement = realloc(statement, statementLen * sizeof(char));
            Position pos = (Position){i, j};
            Line l = (Line){pos, d, statement, len};
            insert(&list, (void *)&l);
        }
        if (i + 1 < height && board[i + 1][j].value != EMPTY)
        {
            Direction d = DOWN;
            char *statement = calloc(MAX_BOARD_SIZE, sizeof(char));
            size_t statementLen;
            for (statementLen = 0; j + statementLen < width && board[i + statementLen][j].value != EMPTY; statementLen++)
                statement[statementLen] = board[i][j + statementLen].value;
            statement = realloc(statement, statementLen * sizeof(char));
            Position pos = (Position){i, j};
            Line l = (Line){pos, d, statement, len};
            insert(&list, (void *)&l);
        }
    }
    return to_array(&list, lineLen);
}

Line *to_array(LinkedList *llist, size_t *arrayLen)
{
    *arrayLen = count(llist->head);
    int i = 0;
    Line *list = malloc(*arrayLen * sizeof(Line));
    for (Node *node = llist->head; node->next != NULL; node = node->next)
        list[i++] = *(Line *)node->val;
    return list;
}

Line get_line(Line *lines, size_t len, int i, int j)
{
    for (int index = 0; index < len; index++)
    {
        Position p = lines[index].pos;
        if (p.i == i && p.j == j)
            return lines[index];
    }
    return (Line){(Position){-1, -1}, RIGHT, NULL, 0};
}