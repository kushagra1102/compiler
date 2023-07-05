#ifndef LEXER_DEF
#define LEXER_DEF

#include <stdio.h>
#define BUFFER_SIZE 64 

typedef enum{
    ID,
    NUM,
    RNUM,
    AND,
    OR,
    TRUE,
    FALSE,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LT,
    LE,
    GE,
    GT,
    EQ,
    NE,
    DEF,
    ENDEF,
    DRIVERDEF,
    DRIVERENDDEF,
    COLON,
    RANGEOP,
    SEMICOL,
    COMMA,
    ASSIGNOP,
    SQBO,
    SQBC,
    BO,
    BC,
    COMMENTMARK,
    INTEGER,
    REAL,
    BOOLEAN,
    OF,
    ARRAY,
    START,
    END,
    DECLARE,
    MODULE,
    DRIVER,
    PROGRAM,
    GET_VALUE,
    PRINT,
    USE,
    WITH,
    PARAMETERS,
    TAKES,
    INPUT,
    RETURNS,
    FOR,
    IN,
    SWITCH,
    CASE,
    BREAK,
    DEFAULT,
    WHILE,
    EPSILON,
    DOLLAR,
    ERROR
}token_name;

typedef union{
    int num;
    float rnum;
}Value;

typedef struct token{
    token_name type;//stores the types of the tokens
    unsigned int line_no;//stores the line number of the token
    char *lexeme;//stores the actual lexeme
    Value *val;//to store integers and floating point numbers
    int type_of_value; // assign ints - 0, assign reals - 1, assign others -2 , assign -1 to errors
}Token;

#endif