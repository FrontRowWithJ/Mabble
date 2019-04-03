#include "Eval.hpp"

long evaluate(string statement, evalResult_t *code)
{
    if (statement.length() < 3)
    {
        *code = EVAL_STRING_TOO_SHORT;
        return ERROR;
    }
    if (num_of_equals(statement) != 1)
    {
        *code = EVAL_INCORRECT_NUM_OF_EQUALS;
        return ERROR;
    }
    int equalPos = equal_pos_of(statement);
    if (!check_string(statement))
    {
        *code = EVAL_INVALID_CHARACTER;
        return ERROR;
    }
    //evaluate left
    if (!is_valid_equation_structure(statement, 0, equalPos))
    {
        *code = EVAL_INVALID_STATEMENT_STRUCTURE_LEFT;
        return ERROR;
    }
    //evaluate right
    if (!is_valid_equation_structure(statement, equalPos + 1, statement.length()))
    {
        *code = EVAL_INVALID_STATEMENT_STRUCTURE_RIGHT;
        return ERROR;
    }
    size_t leftLen, rightLen;
    Token *leftTokens, *rightTokens;
    leftTokens = get_tokens(statement, &leftLen, 0, equalPos);
    rightTokens = get_tokens(statement, &rightLen, equalPos + 1, statement.length());
    long left = eval(leftTokens, leftLen);
    long right = eval(rightTokens, rightLen);
    long res;
    if (left != right)
    {
        *code = EVAL_STATEMENT_DOES_NOT_EQUAL_RESULT;
        res = ERROR;
    }
    else
    {
        *code = EVAL_SUCCESS;
        res = right;
    }
    delete[] leftTokens;
    delete[] rightTokens;
    return res;
}

bool check_string(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (!(IS_NUMBER(str[i])) && !(IS_OPERATOR(str[i])))
            return false;
    return true;
}

bool is_valid_equation_structure(string statement, int start, int end)
{
    char prev = EMPTY;
    int offset = 0;
    if (statement[start] == MULTIPLY_OP || statement[start] == DIVIDE_OP)
        return false;
    if (statement[start] == ADD_OP || statement[start] == SUBTRACT_OP)
        offset++;
    for (int i = start + offset; i < end - 1; i++)
    {
        if (IS_NUMBER(statement[i - 1]))
            continue;
        if (IS_DMAS_OPERATOR(statement[i - 1]))
            if (IS_DMAS_OPERATOR(statement[i]))
                return false;
    }
    return !(IS_OPERATOR(statement[end - 1])) && IS_NUMBER(statement[end - 1]);
}

bool has_operator(string statement)
{
    for (int i = 0; i < statement.length(); i++)
        if (IS_DMAS_OPERATOR(statement[i]))
            return true;
    return false;
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

Token *get_tokens(string statement, size_t *num_of_tokens, int start, int end)
{
    int numOfTokens = 0;
    bool inNumber = false;
    for (int i = start; i < end; i++)
    {
        if (IS_NUMBER(statement[i]) && !inNumber)
        {
            numOfTokens++;
            inNumber = true;
        }
        else
        {
            numOfTokens++;
            inNumber = false;
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
    Token *tokens = new Token[numOfTokens];
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

int num_of_equals(string statement)
{
    int total = 0;
    for (int i = 0; i < statement.length(); i++)
        if (statement[i] == EQUAL_OP)
            total++;
    return total;
}

bool is_number(string statement, int start)
{
    for (int i = start; i < statement.length(); i++)
        if (!(IS_NUMBER(statement[i])))
            return false;
    return true;
}

int equal_pos_of(string statement)
{
    for (int i = statement.length() - 1; i > -1; i--)
        if (statement[i] == EQUAL_OP)
            return i;
    return ERROR;
}