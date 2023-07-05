#include <stdio.h>
#include <stdlib.h>
#include "grammar.c"

typedef struct TreeNode{
    Symbol symbol;
    Token* token; // if leaf node
    struct TreeNode* next; 
    struct TreeNode* parent;
    struct TreeNode* childHead;
    int noOfChildren;
} TreeNode;

typedef struct ParseTree{
    TreeNode* root;
} ParseTree;

TreeNode* createTreeNode(symbol sym, TreeNode* parent){

    TreeNode* treeNode = (TreeNode*)malloc(sizeof(TreeNode));

    treeNode->sym = sym;
    treeNode->token = NULL;
    treeNode->next = NULL;
    treeNode->parent = parent;
    treeNode->childHead = NULL;
    treeNode->noOfChildren = 0;

    if(parent->childHead == NULL)
        parent->childHead = treeNode;

    parent->noOfChildren++;

    return treeNode;
}

void addChildToTree(TreeNode* treeNode, Rule* rule){

    SymbolNode* symbolNode = r->head;
    TreeNode* temp = treeNode->childHead;

    for(int i=0 ;i<r->length; i++){

        TreeNode* childNode = createTreeNode(symbolNode->symbol,treeNode);

        if(temp == NULL){
            temp = childNode;
        }
        else{
            temp->next = childNode;
            temp = childNode;
        }

        if(symbolNode->next != NULL)
            symbolNode = symbolNode->next;
                
    }
}