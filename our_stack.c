#include <stdio.h>
#include <stdlib.h>
#include "our_tree.c"
#include "grammar.c"

typedef struct StackNode{
	TreeNode* treeNodePointer;
	struct StackNode* next;
}StackNode;

struct Stack{
	StackNode* top;
	int size;
}Stack;

StackNode* createStackNode(TreeNode* treeNodePointer){

	StackNode* stackNode = (StackNode*)malloc(sizeof(StackNode));	
	stackNode->treeNodePointer = treeNodePointer;
	stackNode->next = NULL;

	return stackNode;
}

void pushToStack(Stack* s, TreeNode* treeNodePointer){

	StackNode* newStackNode = createStackNode(treeNodePointer);
	newStackNode->next = s->top;
	s->top = newStackNode;
	s->size++;

}

StackNode* popFromStack(Stack* s){

	if(s->size == 0){
		return NULL;
	}

	else{
		StackNode* temp = s->top;
		s->top = s->top->next;
		s->size--;

		return temp;
	}
}

void addToStack(Stack* s, TreeNode* treeNode){

    TreeNode* child = treeNode->childHead;
    
    // If the rule is NT--> epsilon, we dont need to push anything on the stack
    if(child->symbol.t == 'epsilon')
        return;
    
    // We need to reverse the child before inserting in s
    // Reversal of treeNodes can be done via another stack s2
    Stack* s2 = (Stack*)malloc(sizeof(Stack));
    s2->top = NULL;
    s2->size = 0;

    while(child != NULL){
        pushToStack(s2,child);
        child = child->next;
    }

    while(s2->size != 0){
        StackNode* stackNode = popFromStack(s2);
        TreeNode* newNode = stackNode->treeNodePointer;
        pushToStack(s,newNode)
    }

}



