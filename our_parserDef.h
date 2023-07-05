#include <stdio.h>
#include <stdlib.h>
#include "our_stack.c"
#include "our_tree.c"

#define SIZE_OF_VECTOR ((NO_OF_TERMINALS/(sizeof(int)*8)) + 1)
#define NO_OF_RULES 108
#define NO_OF_NON_TERMINALS 69
#define NO_OF_TERMINALS 51

// 0. Data Structures & Definitions

char *T_HashMap[] = {"AND", "ARRAY", "ASSIGNOP", "BC", "BO", "BOOLEAN", "BREAK", "CASE", "COLON", "COMMA", "DECLARE", "DEF", "DEFAULT", "DIV", "DRIVER", "DRIVERDEF", "DRIVERENDDEF", "END", "ENDDEF", "FALSE", "FOR", "GET_VALUE", "ID", "IN", "INPUT", "INTEGER", "MINUS", "MODULE", "MUL", "NUM", "OF", "OR", "PARAMETERS", "PLUS", "PRINT", "PROGRAM", "RANGEOP", "REAL", "RETURNS", "RNUM", "SEMICOL", "SQBC", "SQBO", "START", "SWITCH", "TAKES", "TRUE", "USE", "WHILE", "WITH", "e"};
char *NT_HashMap[] = {"AnyTerm", "N1", "N2", "N3", "N4", "N5", "N7", "N8", "N_10", "arithmeticExpr", "arithmeticOrBooleanExpr", "arrExpr", "arrFactor", "arrTerm", "arr_N4", "arr_N5", "array_element", "assignmentStmt", "boolConstt", "caseStmt", "caseStmts", "condionalStmt", "dataType", "declareStmt", "deFault", "driverModule", "element_index_with_expressions", "expression", "factor", "idList", "id_num_rnum", "index_arr", "index_for_loop", "input_plist", "ioStmt", "iterativeStmt", "logicalOp", "lvalueARRStmt", "lvalueIDStmt", "module", "moduleDeclaration", "moduleDeclarations", "moduleDef", "moduleReuseStmt", "new_index", "new_index_for_loop", "op1", "op2", "op", "optional", "otherModules", "output_plist", "program", "range_arrays", "range_for_loop", "relationalOp", "ret", "sign", "sign_for_loop", "simpleStmt", "statement", "statements", "term", "type", "value", "var", "var_print", "whichId", "whichStmt"};

typedef enum terminal
{
    AND,
    ARRAY,
    ASSIGNOP,
    BC,
    BO,
    BOOLEAN,
    BREAK,
    CASE,
    COLON,
    COMMA,
    DECLARE,
    DEF,
    DEFAULT,
    DIV,
    DRIVER,
    DRIVERDEF,
    DRIVERENDDEF,
    END,
    ENDDEF,
    FALSE,
    FOR,
    GET_VALUE,
    ID,
    IN,
    INPUT,
    INTEGER,
    MINUS,
    MODULE,
    MUL,
    NUM,
    OF,
    OR,
    PARAMETERS,
    PLUS,
    PRINT,
    PROGRAM,
    RANGEOP,
    REAL,
    RETURNS,
    RNUM,
    SEMICOL,
    SQBC,
    SQBO,
    START,
    SWITCH,
    TAKES,
    TRUE,
    USE,
    WHILE,
    WITH,
    e
} Terminal;

typedef enum nonTerminal
{
    AnyTerm,
    N1,
    N2,
    N3,
    N4,
    N5,
    N7,
    N8,
    N_10,
    arithmeticExpr,
    arithmeticOrBooleanExpr,
    arrExpr,
    arrFactor,
    arrTerm,
    arr_N4,
    arr_N5,
    array_element,
    assignmentStmt,
    boolConstt,
    caseStmt,
    caseStmts,
    condionalStmt,
    dataType,
    declareStmt,
    deFault,
    driverModule,
    element_index_with_expressions,
    expression,
    factor,
    idList,
    id_num_rnum,
    index_arr,
    index_for_loop,
    input_plist,
    ioStmt,
    iterativeStmt,
    logicalOp,
    lvalueARRStmt,
    lvalueIDStmt,
    module,
    moduleDeclaration,
    moduleDeclarations,
    moduleDef,
    moduleReuseStmt,
    new_index,
    new_index_for_loop,
    op1,
    op2,
    op,
    optional,
    otherModules,
    output_plist,
    program,
    range_arrays,
    range_for_loop,
    relationalOp,
    ret,
    sign,
    sign_for_loop,
    simpleStmt,
    statement,
    statements,
    term,
    type,
    value,
    var,
    var_print,
    whichId,
    whichStmt
} NonTerminal;

typedef struct Symbol{
    union{
        Terminal t;
        NonTerminal nt;
    };
    bool is_terminal;
}Symbol;

typedef struct SymbolNode{
    Symbol symbol;
    struct SymbolNode *next;
} SymbolNode;

typedef struct Rule{
    NonTerminal LHS;
    SymbolNode* head;
    struct Rule* next;
    int length;
    int ruleNo;
} Rule;

typedef struct Rules{
    NonTerminal LHS;
    Rule* head;
    // int nonTerminalNo;
    int noOfRules;
} Rules;

// grammar is an array of rules
typedef struct Grammar{
    Rules** rules;
} Grammar;

// TODO : define startsymbol = new symbol(malloc/calloc)

Rule* parseTable[NO_OF_NON_TERMINALS][NO_OF_TERMINALS];

