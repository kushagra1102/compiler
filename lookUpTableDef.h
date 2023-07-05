#ifndef LOOKUP_TABLE_DEF
#define LOOKUP_TABLE_DEF
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

char* tokenName[] = {"ID","NUM","RNUM","AND","OR","TRUE","FALSE","PLUS","MINUS","MUL","DIV","LT","LE","GE",
    "GT","EQ","NE","DEF","ENDEF","DRIVERDEF","DRIVERENDDEF","COLON","RANGEOP","SEMICOL",
    "COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK","INTEGER","REAL","BOOLEAN",
    "OF","ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","GET_VALUE","PRINT",
    "USE","WITH","PARAMETERS","TAKES","INPUT","RETURNS","FOR","IN","SWITCH","CASE","BREAK",
    "DEFAULT","WHILE","EPSILON","DOLLAR","ERROR"};

typedef struct Node
{
    struct Node *next;
    char *lexeme;
    token_name type;
    

}lookUpTable;

#endif