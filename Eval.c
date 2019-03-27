#include "Eval.h"

int main(int argc, char **argv)
{
    int res = -64+18*77+12-86/9;
    printf("%d\n", res);
    char *test = argc == 1 ? "-64+18*77+12-86/9=53*5*5" : argv[1];
    int equalPos = equal_pos_of(test);
    boolean is_left_v = is_valid_equation_structure(test, 0, equalPos);
    boolean is_right_v = is_valid_equation_structure(test, equalPos + 1, strlen(test));
    char *left = substring_of(test, 0, equalPos);
    char *right = substring_of(test, equalPos + 1, strlen(test));

    printf("The left side: (%s) structure is %s\n", left, is_left_v ? "valid" : "invalid");
    printf("The right side: (%s) structure is %s\n", right, is_right_v ? "valid" : "invalid");
    evalResult_t code;
    evaluate(test, &code);
    printf("The statement (%s) is%s sound\n", test, code == EVAL_SUCCESS ? "" : "n't");
    size_t leftLen;
    size_t rightLen;
    if (is_left_v && is_right_v)
    {
        Token *leftTokens = get_tokens(test, &leftLen, 0, equalPos);
        Token *rightTokens = get_tokens(test, &rightLen, equalPos + 1, strlen(test));
        printf("left: %ld\nright: %ld\n", eval(leftTokens, leftLen), eval(rightTokens, rightLen));
    }
}

//from start inclusive to end exclusive
char *substring_of(char *string, int start, int end)
{
    char *result = calloc(end - start + 1, sizeof(char));
    for (int i = start; i < end; i++)
    {
        result[i - start] = string[i];
    }
    return result;
}
void evaluate(char *statement, evalResult_t *code)
{
    if (strlen(statement) < 3)
    {
        *code = EVAL_STRING_TOO_SHORT;
        return;
    }
    if (num_of_equals(statement) != 1)
    {
        *code = EVAL_INCORRECT_NUM_OF_EQUALS;
        return;
    }
    int equalPos = equal_pos_of(statement);
    if (!check_string(statement))
    {
        *code = EVAL_INVALID_CHARACTER;
        return;
    }
    //evaluate left
    if (!is_valid_equation_structure(statement, 0, equalPos))
    {
        *code = EVAL_INVALID_STATEMENT_STRUCTURE_LEFT;
        return;
    }
    //evaluate right
    if (!is_valid_equation_structure(statement, equalPos + 1, strlen(statement)))
    {
        *code = EVAL_INVALID_STATEMENT_STRUCTURE_RIGHT;
        return;
    }
    size_t leftLen, rightLen;
    Token *leftTokens, *rightTokens;
    leftTokens = get_tokens(statement, &leftLen, 0, equalPos);
    rightTokens = get_tokens(statement, &rightLen, equalPos + 1, strlen(statement));
    long left = eval(leftTokens, leftLen);
    long right = eval(rightTokens, rightLen);
    if (left != right)
        *code = EVAL_STATEMENT_DOES_NOT_EQUAL_RESULT;
    else
        *code = EVAL_SUCCESS;
    free(leftTokens);
    free(rightTokens);
}

boolean check_string(char *str)
{
    for (int i = 0; i < strlen(str); i++)
        if (!(IS_NUMBER(str[i])) && !(IS_OPERATOR(str[i])))
            return FALSE;
    return TRUE;
}

boolean is_valid_equation_structure(char *statement, int start, int end)
{
    char prev = '\0';
    int offset = 0;
    if (statement[start] == MULTIPLY_OP || statement[start] == DIVIDE_OP)
        return FALSE;
    if (statement[start] == ADD_OP || statement[start] == SUBTRACT_OP)
        offset++;
        for (int i = start + offset; i < end - 1; i++)
        {
            if (IS_NUMBER(statement[i - 1]))
                continue;
            if (IS_DMAS_OPERATOR(statement[i - 1]))
                if (IS_DMAS_OPERATOR(statement[i]))
                    return FALSE;
        }
    return !(IS_OPERATOR(statement[end - 1])) && IS_NUMBER(statement[end - 1]);
}

boolean has_operator(char *statement)
{
    for (int i = 0; i < strlen(statement); i++)
        if (IS_DMAS_OPERATOR(statement[i]))
            return TRUE;
    return FALSE;
}

long calculate(long a, const char op, long b)
{
    switch (op)
    {
    case ADD_OP:
        return a + b;
    case MULTIPLY_OP:
        return a * b;
    case DIVIDE_OP:
        return a / b;
    case SUBTRACT_OP:
        return a - b;
    }
    return -1;
}

Token *get_tokens(char *statement, size_t *num_of_tokens, int start, int end)
{
    int numOfTokens = 0;
    boolean inNumber = FALSE;
    for (int i = start; i < end; i++)
    {
        if (IS_NUMBER(statement[i]) && !inNumber)
        {
            numOfTokens++;
            inNumber = TRUE;
        }
        else
        {
            numOfTokens++;
            inNumber = FALSE;
        }
    }
    int factor = 1;
    int offset = 0;
    if (statement[start] == ADD_OP || statement[start] == SUBTRACT_OP)
    {
        numOfTokens--;
        factor = statement[start] == ADD_OP ? 1 : -1;
        offset = 1;
    }
    Token *tokens = malloc(numOfTokens * sizeof(Token));
    int index = 0;
    int number = 0;
    for (int i = start + offset; i < end; i++)
    {
        if (IS_NUMBER(statement[i]))
            number = number * 10 + (statement[i] - '0');
        else
        {
            tokens[index++].number = number;
            tokens[index++].op = statement[i];
            number = 0;
        }
    }
    tokens[index].number = number;
    tokens[0].number *= factor;
    *num_of_tokens = index + 1;
    return tokens;
}

long eval(Token *tokens, size_t len)
{
    size_t length = len;
    int i = 1;
    while (length >= 1)
    {
        while (i < length)
        {
            if (tokens[i].op == MULTIPLY_OP || tokens[i].op == DIVIDE_OP)
            {
                long value = calculate(tokens[i - 1].number, tokens[i].op, tokens[i + 1].number);
                tokens[i - 1] = (Token){value};
                for (int j = i + 2; j < len; j++)
                    tokens[j - 2] = tokens[j];
                length -= 2;
                i = 1;
            }
            else
                i += 2;
        }
        i = 1;
        while (i < length)
        {
            if (tokens[i].op == ADD_OP || tokens[i].op == SUBTRACT_OP)
            {
                long value = calculate(tokens[i - 1].number, tokens[i].op, tokens[i + 1].number);
                tokens[i - 1] = (Token){value};
                for (int j = i + 2; j < len; j++)
                    tokens[j - 2] = tokens[j];
                length -= 2;
                i = 1;
            }
            else
                i += 2;
        }
        return tokens->number;
    }
}

void print_tokens(Token *t, size_t len)
{
    for (int i = 0; i < len; i++)
        if (i % 2 == 0)
            printf("%ld", t[i].number);
        else
            printf("%c", t[i].op);
    printf("\n");
}

int num_of_equals(char *statement)
{
    int total = 0;
    for (int i = 0; i < strlen(statement); i++)
        if (statement[i] == EQUAL_OP)
            total++;
    return total;
}

boolean is_number(char *statement, int start)
{
    for (int i = start; i < strlen(statement); i++)
        if (!(IS_NUMBER(statement[i])))
            return FALSE;
    return TRUE;
}

int equal_pos_of(char *statement)
{
    for (int i = strlen(statement) - 1; i > -1; i--)
        if (statement[i] == EQUAL_OP)
            return i;
    return ERROR;
}
