#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "our_stack.c"
#include "our_tree.c"
#include "our_parser.h"

#define NO_OF_RULES 
#define NO_OF_TERMINALS
#define NO_OF_NON_TERMINALS
#define SIZE_OF_VECTOR ((NO_OF_TERMINALS/(sizeof(int)*8)) + 1)

// 1. Generate Grammar
void generate_grammar(FILE* fp){}









// 2. First & Follow Set Automation

// void addToSet(int* sizeOfVector, int idx){
// 	sizeOfVector[idx/(sizeof(int)*8)] = (sizeOfVector[idx/(sizeof(int)*8)]) | (1 << (idx%(sizeof(int)*8)));
// }
// void removeFromSet(int* sizeOfVector, int idx){
// 	sizeOfVector[idx/(sizeof(int)*8)] = (sizeOfVector[idx/(sizeof(int)*8)]) & (~(1 << ((idx%(sizeof(int)*8)))));
// }
// int checkPresence(int* sizeOfVector,  int idx){
// 	return (((sizeOfVector[idx/(sizeof(int)*8)]) & (1 << (idx%(sizeof(int)*8)))) != 0 ); 
// }

void combine_sets(int *set1,int *set2)
{
    for(int i=0;i<NO_OF_TERMINALS;i++)
    {
        if()
    }
}
bool findInSet(int *set,int index)
{
    int val = (index)/(sizeof(int)*8);
    int num = (sizeof(int)*8);
    return (((set[idx/num]) & (1 << (idx%(sizeof(int)*8)))) != 0);
}

void compute_first_set(Grammar* grammar, NonTerminal nonTerminal, int** first_sets)
{

    Rules* rules = grammar->rules[nonTerminal];//returns all rules corresponding to a non terminal
    Rule* firstRule = rules->head;
    for(int i=0;i<rules->noOfRules;i++)//traversing over all the rules corresponding to a non terminal
    {
        Rule *temp = firstRule;
        while(temp!=NULL)//traversing over the symbols in a rule
        {
            if(temp->head->symbol.isTerminal)
            {
                int index = temp->head->symbol.t;
                int val = (index)/(sizeof(int)*8);
                int num = (sizeof(int)*8); //adding the terminal to the first set of the corresponding non terminal
                first_sets[nonTerminal][index/num] |= (1<<((index%(num))));//hashing
                break;
            }
            else{
               compute_first_set(grammar,temp->head->symbol.nt,first_sets);



            }
            
            temp=temp->next;
        }
    }
}

// void computeFirstSet(Grammar grammar, NonTerminal nt, int** firstSets){

//     // TODO: Non-terminal to index
//     Rules* rules = grammar[ruleNo];
//     Rule* temp = rules->head;

//     for(int i = 0; i < rules->nonTerminalNo; i++){
//         SymbolNode * temp2 = temp->head;

//         for (int j = 0; i < temp->length; j++){
//             if(temp2->symbol.is_terminal){
//                 addToSet(first_set[nt], temp2->symbol.t);
//                 break;
//             }
//             else{
//                 compute_first_set(grammar, temp2->symbol.nt, first_set);
//                 union_set(first_set[nt], first_set[temp2->symbol.nt]);

//                 if(!checkPresence(first_set[temp2->symbol.nt], epsilon)){
//                     break;
//                 }
//             }
//             temp2= temp2->next;
//         }
//     }
// }



// 3. Parse Table Creation(Automated)

void createParseTable(Grammar* g, int **first_set, int **follow_set, ParsingTable * table){

    for (int i = 0; i < TOTAL_NON_TERMINALS; i++)
    {
        // rules[i] is a rules* which corresponds to head and length of rules of the non terminal at the index i
        Rules* rules = g->rules[i];
        Rule* rule_ptr = rules->head;//Rule at index i

        for (int j = 0; j < g->rules[i]->noOfRules; j++)
        {
            // currently pointing to a terminal
            if(rule_ptr->head->symbol.is_terminal){

                // check if its epsilon
                if(rule_ptr->head->symbol.t == EPSILON){

                    int* follow_set_of_i = follow_set[i];

                    // 
                    for (int k = 0; k < TOTAL_TERMINALS; k++)
                    {
                        if(checkPresence(follow_set_of_i, k)){
                            table->cells[i][k] = rule_ptr;
                        }
                    }
                    
                }

                // terminal but not epsilon
                else{
                    table->cells[i][rule_ptr->head->symbol.t] = rule_ptr;
                }

            }

            // currently pointing to a nonterminal
            else{
                int *first_set_NT_i = first_set[rule_ptr->head->symbol.nt]; // first set corresponding to the first non terminal symbol of ruleptr
                
                for (int k = 0; k < TOTAL_TERMINALS; k++)
                {
                    if(checkPresence(first_set_NT_i, k)){
                        table->cells[i][k] = rule_ptr;
                    }
                }
        
            }

            rule_ptr= rule_ptr->next;
        }
        
    }
    
}














// 4. Parse Tree and Parsing Algorithm

ParseTree* parseInputSourceCode(FILE* fp, int** parseTable, int* syntaxErorrs, Rule* grammar){
	

    // Initialise Parse Tree
    ParseTree* tree = (ParseTree*)malloc(sizeof(ParseTree));
    tree->root = createTreeNode(startsymbol,NULL);
    TreeNode* temp = tree->root;

    // Initialise PDA : Stack
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->size = 0;
    s->top = NULL;
    TreeNode* dollarNode = createTreeNode('$',NULL);
	StackNode* dollar = createStackNode(dollarNode);
    pushToStack(s,dollar);
    pushToStack(s,tree->root);


    // Fetch token from Lexer
    Token* L = getNextToken(fp);


    while(L != NULL){

        //TODO: error 4
        // Take a more in-depth view at errors before starting the parsing process
        if(s->size == 0){
            // report erorr of type 4 : Input is not consumed and stack is empty
        }
        // more error detection logic






        // Parsing Algorithm Begins

        StackNode* stackTopNode = popFromStack(s);
        TreeNode* treeNode = stackTopNode->treeNodePointer;




        // Case 1: Top of Stack is a terminal
        if(treeNode->symbol.isTerminal){

            // Case 1.a: Top of Stack matches with Lookahead Token
            if(treeNode->symbol.terminal ==  L.type){
                treeNode->token = L;
                L = getNextToken(fp);
            }
            // Case 1.b: Top of Stack does not match with Lookahead Token
            else{
                // report error Type 1 : Terminal Mismatch
            }

        }




        // Case 2: Top of Stack is a non-terminal
        else {
            
            NonTerminal nt = treeNode->symbol.nt;
            Terminal t = L.type;
            // TODO : t and nt are not yet mapped to an integer
            int ruleNo = parseTable[(int)nt][(int)t];

            // Case 2a: Valid Rule Present in ParseTable
            if(ruleNo != -1){
                // TODO : access rule from ruleNo
                Rule r = grammar[ruleNo];
                addChildrenOfTree(treeNode,r);
                addToStack(s,treeNode);
            }
            // Case 2.b: Rule not Present in ParseTable
            else{
                // report erorr of type 2 : NULL access from parse table
            }

        }

    }

    if(!s.empty()){
        // report error of type 3 : Input is consumed but stack is not empty
    }

}