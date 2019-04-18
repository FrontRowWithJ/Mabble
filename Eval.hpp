#ifndef EVAL_H
#define EVAL_H
#endif

#ifndef UTIL_H
#include "Util.hpp"
#endif

#define ERROR -1
#define IS_OPERATOR(C) \
    C == ADD_OP || C == MULTIPLY_OP || C == SUBTRACT_OP || C == DIVIDE_OP || C == EQUAL_OP
#define IS_DMAS_OPERATOR(C) \
    C == DIVIDE_OP || C == MULTIPLY_OP || C == ADD_OP || C == SUBTRACT_OP
#define IS_NUMBER(N) \
    N >= '0' && N <= '9'

#define ADD_OP 43
#define MULTIPLY_OP 42
#define SUBTRACT_OP 45
#define DIVIDE_OP 47
#define EQUAL_OP 61
typedef enum RESULT_CODE
{
    EVAL_SUCCESS,
    EVAL_VALID_EQUATION,
    EVAL_INVALID_STATEMENT_STRUCTURE_LEFT,
    EVAL_INVALID_STATEMENT_STRUCTURE_RIGHT,
    EVAL_STRING_TOO_SHORT,
    EVAL_INVALID_CHARACTER,
    EVAL_INCORRECT_NUM_OF_EQUALS,
    EVAL_INCORRECT_EQUAL_POS,
    EVAL_RESULT_NOT_A_NUMBER,
    EVAL_STATEMENT_DOES_NOT_EQUAL_RESULT,
} evalResult_t;

typedef union token {
    long number;
    char op;
} Token;

bool has_operator(string *statement);
Token *get_tokens(string *statement, size_t *num_of_tokens, int start, int end);
long eval(Token *tokens, size_t len);
long calculate(long a, char op, long b);
void print_tokens(Token *t, size_t len);
long evaluate(string *statement, evalResult_t *code);
int num_of_equals(string *statement);
bool is_number(string *statement, int start);
int equal_pos_of(string *statement);
bool check_string(string *statement);
bool is_valid_equation_structure(string *statement, int start, int end);
evalResult_t check_equation(string *equation);
