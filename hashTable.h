
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTableDef.h" 

//contains function declarations
hashTable *init();
void addEntry(char *lexeme,token_name type);
hashTable* insert(char *lexeme,token_name type,hashTable *hash_table);
lookUp* search(hashTable *hash_table,char *lexeme);
hashTable* populateTable();
int max(int a,int b);
int hash(char *key);

