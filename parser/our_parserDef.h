#include <stdio.h>
#include <stdlib.h>
#include "our_stack.c"
#include "our_tree.c"

#define NO_OF_RULES 30
#define NO_OF_TERMINALS 30
#define NO_OF_NON_TERMINALS 30
#define SIZE_OF_VECTOR ((NO_OF_TERMINALS/(sizeof(int)*8)) + 1)


// 0. Data Structures & Definitions

enum {
    PLUS,
    MINUS

}Terminal;
enum {
    program

}NonTerminal;

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
    int nonTerminalNo;
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
    int noOfRules;
} Grammar;

// TODO : define startsymbol = new symbol(malloc/calloc)

int** first_sets;

Rule* parseTable[NO_OF_NON_TERMINALS][NO_OF_TERMINALS];

