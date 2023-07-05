#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define MAX_SYMBOL_LENGTH 50

// 0. Data Structures & Definitions

#define NO_OF_RULES 108
#define NO_OF_NON_TERMINALS 69
#define NO_OF_TERMINALS 51
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

int get_terminal_index(char *s)
{
    int i = 0;
    while (i < NO_OF_TERMINALS)
    {
        if (!strcmp(T_HashMap[i], s))
            return i;
        i++;
    }
    return -1;
}
int get_nonterminal_index(char *s)
{
    int i = 0;
    while (i < NO_OF_NON_TERMINALS)
    {
        if (!strcmp(NT_HashMap[i], s))
            return i;
        i++;
    }
    return -1;
}

typedef struct Symbol
{
    union
    {
        Terminal t;
        NonTerminal nt;
    };
    bool is_terminal;
} Symbol;

typedef struct SymbolNode
{
    Symbol *symbol;
    struct SymbolNode *next;
} SymbolNode;

typedef struct Rule
{
    NonTerminal LHS;
    SymbolNode *head;
    struct Rule *next;
    int length;
    int ruleNo;
} Rule;

typedef struct Rules
{
    NonTerminal LHS;
    Rule *head;
    // int nonTerminalNo;
    int noOfRules;
} Rules;

typedef struct Grammar
{
    Rules **rules;
} Grammar;

// new

Symbol *new_symbol(char *s, bool is_terminal)
{
    Symbol *t = (Symbol *)malloc(sizeof(Symbol));
    t->is_terminal = is_terminal;
    if (is_terminal)
        t->t = get_terminal_index(s);
    else
        t->nt = get_nonterminal_index(s);
    return t;
}
SymbolNode *new_symbol_node(char *s, bool is_terminal)
{
    SymbolNode *t = (SymbolNode *)malloc(sizeof(SymbolNode));
    t->symbol = new_symbol(s, is_terminal);
    t->next = NULL;
    return t;
}
Rule *new_rule(NonTerminal nt, int ruleNo)
{
    Rule *t = (Rule *)malloc(sizeof(Rule));
    t->head = NULL;
    t->next = NULL;
    t->length = 0;
    t->ruleNo = ruleNo;
    t->LHS = nt;
    return t;
}
Rules *new_rules(NonTerminal nt)
{
    Rules *t = (Rules *)malloc(sizeof(Rules));
    t->LHS = nt;
    t->noOfRules = 0;
    t->head = NULL;
    return t;
}

Grammar *g;
Rule **headRule;
Rules **headRules;

void generate_grammar(FILE *fp)
{
    int ruleNo = 0;
    char row[200];

    headRule = (Rule **)malloc(sizeof(Rule *) * NO_OF_RULES);

    while (fscanf(fp, "%[^\n] ", row) != -1)
    {
        int ind = 0;
        char *lhsNT = (char *)malloc(sizeof(char) * MAX_SYMBOL_LENGTH);

        /* LHS */
        while (row[ind] != '>')
        {
            char c = row[ind];
            if (c == '<')
                ;
            else
            {
                lhsNT[ind - 1] = c;
            }
            ind++;
        }
        lhsNT[ind - 1] = '\0';
        ind++;

        headRule[ruleNo] = new_rule(get_nonterminal_index(lhsNT), ruleNo);

        // printf("<%s> -->", NT_HashMap[headRule[ruleNo]->LHS]);

        free(lhsNT);

        /* --> */
        while (row[ind] != '>')
        {
            ind++;
        }
        ind++;

        SymbolNode *tempNode = NULL;

        /* RHS */
        while (row[ind] != '\0')
        {
            char c = row[ind];
            if (c == ' ')
            {
                ind++;
                continue;
            }

            char *rhsSym = (char *)malloc(sizeof(char) * MAX_SYMBOL_LENGTH);
            bool is_terminal = false;

            if (c == '<') // Non-Terminal
            {
                is_terminal = false;
                ind++;
                int rhsNTind = ind;
                while (row[ind] != '>')
                {
                    rhsSym[ind - rhsNTind] = row[ind];
                    ind++;
                }
                rhsSym[ind - rhsNTind] = '\0';
            }
            else // Terminal
            {
                is_terminal = true;
                int rhsTind = ind;
                while ((row[ind] >= 'a' && row[ind] <= 'z') || (row[ind] >= 'A' && row[ind] <= 'Z'))
                {
                    rhsSym[ind - rhsTind] = row[ind];
                    ind++;
                }
                rhsSym[ind - rhsTind] = '\0';
            }

            headRule[ruleNo]->length++;

            if (tempNode == NULL)
            {
                tempNode = new_symbol_node(rhsSym, is_terminal);
                headRule[ruleNo]->head = tempNode;
            }
            else
            {
                tempNode->next = new_symbol_node(rhsSym, is_terminal);
                tempNode = tempNode->next;
            }

            // if (is_terminal)
            //     printf(" %s", T_HashMap[tempNode->symbol->t]);
            // else
            //     printf(" <%s>", NT_HashMap[tempNode->symbol->nt]);

            free(rhsSym);
            ind++;
        }

        // printf("\n");

        memset(row, '\0', sizeof(row));
        ruleNo++;
    }

    headRules = (Rules **)malloc(sizeof(Rules *) * NO_OF_NON_TERMINALS);

    int nonTerminalNo = 0;
    while (nonTerminalNo < NO_OF_NON_TERMINALS)
    {

        headRules[nonTerminalNo] = new_rules(nonTerminalNo);
        Rule *tempRule = NULL;

        ruleNo = 0;
        while (ruleNo < NO_OF_RULES)
        {
            if (headRule[ruleNo]->LHS == nonTerminalNo)
            {
                if (tempRule == NULL)
                {
                    tempRule = headRule[ruleNo];
                    headRules[nonTerminalNo]->head = tempRule;
                }
                else
                {
                    tempRule->next = headRule[ruleNo];
                    tempRule = tempRule->next;
                }
                headRules[nonTerminalNo]->noOfRules++;
            }
            ruleNo++;
        }

        nonTerminalNo++;
    }

    g = (Grammar *)malloc(sizeof(Grammar));

    g->rules = (Rules **)malloc(sizeof(Rules *) * NO_OF_NON_TERMINALS);
    for (int i = 0; i < NO_OF_NON_TERMINALS; i++)
    {
        g->rules[i] = headRules[i];
    }
}

void test_grammar()
{
    // int ruleNo = 0;
    // while (ruleNo < NO_OF_RULES)
    // {
    //     printf("Rule %d : %d\n", headRule[ruleNo]->ruleNo, headRule[ruleNo]->length);
    //     ruleNo++;
    // }

    // int nonTerminalNo = 0;
    // while (nonTerminalNo < NO_OF_NON_TERMINALS)
    // {
    //     printf("Rules %d : %d\n", headRules[nonTerminalNo]->LHS, headRules[nonTerminalNo]->noOfRules);
    //     nonTerminalNo++;
    // }

    // printf("%d\n", g->rules[0]->noOfRules);
    // printf("%d\n", headRules[0]->head->ruleNo);
    // printf("%d\n", headRule[56]->length);
    // if (headRule[56]->head == NULL)
    //     printf("NULL\n");
    // else
    //     printf("%d\n", headRule[56]->head->symbol->nt);

    for (int i = 0; i < NO_OF_NON_TERMINALS; i++)
    {
        // printf("%d\n", headRules[i]->noOfRules);

        Rule *tempRule = headRules[i]->head;
        for (int j = 0; j < headRules[i]->noOfRules; j++)
        {
            printf("%d %d | <%s> -->", tempRule->ruleNo, tempRule->length, NT_HashMap[headRules[i]->LHS]);
            SymbolNode *temp = tempRule->head;
            while (temp != NULL)
            {
                if (temp->symbol->is_terminal)
                    printf(" %s", T_HashMap[temp->symbol->t]);
                else
                    printf(" <%s>", NT_HashMap[temp->symbol->nt]);
                temp = temp->next;
            }
            tempRule = tempRule->next;
            printf("\n");
        }
    }

    // printf("%d", headRules[65]->head->next->length);
}

int main()
{
    FILE *fp;
    fp = fopen("grammar.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }
    generate_grammar(fp);

    test_grammar();

    fclose(fp);
}
