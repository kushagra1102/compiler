#include<stdio.h>
#include "hashTable.h"
#include<string.h>
#include<stdlib.h>
int numSlots = 43; //number of slots in hashTable 
//number of slots in hash table are selected as 59 to minimise collisions (tested for all primes)
//59 results in atmax 3 collisions in a field which can easily be lineary probed using the linked list struct we created

//we choose a large prime number for effective hashing
//We are using the rolling hash function for hashing
//hash[s] = (s[0] + s[1]*p + s[2]*p^2....s[n-1]*p^(n-1))%m
int p = 53;//used for the rolling hash function


int max(int a,int b)
{
    if(a>b)return a;
    else return b;
}

int hash(char *key)//function to calculate the hash value of a particular key
{
    
    int hashValue=0;
    int power=1;
     for (int i=0; i<strlen(key) ; i++) {
        
        hashValue = (hashValue + (key[i]) * power) % numSlots;
        power = (power * p) % numSlots;
    }
    
	return hashValue;
}
hashTable *init()
{
    
    hashTable *hash_table= (hashTable *)malloc(sizeof(hashTable));
    hash_table->numSlots = numSlots;
    hash_table->slot = (lookUp **)malloc(numSlots*(sizeof(lookUp *)));

    for(int i=0;i<numSlots;i++)
    {
		hash_table->slot[i] = (lookUp*)malloc(sizeof(lookUp));
        hash_table->slot[i]->lexeme="\0";
        hash_table->slot[i]->type=0;
        hash_table->slot[i]->next=NULL;
        hash_table->slot[i]->head=hash_table->slot[i];
        hash_table->slot[i]->tail=hash_table->slot[i]->head;
	}

	
    return hash_table;
	
}

hashTable* insert(char *lexeme,token_name type,hashTable *hash_table)
{

    int hashValue= hash(lexeme);
    lookUp *tail=hash_table->slot[hashValue]->tail;
    tail->next=(lookUp *)malloc(sizeof(lookUp));
    tail=tail->next;
    tail->next=NULL;
    tail->lexeme=lexeme;
    tail->type=type;
    hash_table->slot[hashValue]->tail=tail;
    return hash_table;
}
lookUp* search(hashTable *hash_table,char *lexeme)
{
    
    int hashValue= hash(lexeme);
   
    lookUp *temp=hash_table->slot[hashValue]->head;
    int count=0;
    while(temp)
    {   
        count++;
       
        if(strcmp(lexeme,temp->lexeme)==0)
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}
hashTable* populateTable()
{
    hashTable *hash_table= init();
    hash_table=insert("integer",INTEGER,hash_table);
    hash_table=insert("real",REAL,hash_table);
    hash_table=insert("boolean",BOOLEAN,hash_table);
    hash_table=insert("of",OF,hash_table);
    hash_table=insert("array",ARRAY,hash_table);
    hash_table=insert("start",START,hash_table);
    hash_table=insert("end",END,hash_table);
    hash_table=insert("declare",DECLARE,hash_table);
    hash_table=insert("module",MODULE,hash_table);
    hash_table=insert("driver",DRIVER,hash_table);
    hash_table=insert("program",PROGRAM,hash_table);
    hash_table=insert("get_value",GET_VALUE,hash_table);
    hash_table=insert("print",PRINT,hash_table);
    hash_table=insert("use",USE,hash_table);
    hash_table=insert("with",WITH,hash_table);
    hash_table=insert("parameters",PARAMETERS,hash_table);
    hash_table=insert("takes",TAKES,hash_table);
    hash_table=insert("input",INPUT,hash_table);
    hash_table=insert("returns",RETURNS,hash_table);
    hash_table=insert("for",FOR,hash_table);
    hash_table=insert("in",IN,hash_table);
    hash_table=insert("switch",SWITCH,hash_table);
    hash_table=insert("case",CASE,hash_table);
    hash_table=insert("break",BREAK,hash_table);
    hash_table=insert("default",DEFAULT,hash_table);
    hash_table=insert("while",WHILE,hash_table);
    hash_table=insert("AND",AND,hash_table);
    hash_table=insert("true",TRUE,hash_table);
    hash_table=insert("false",FALSE,hash_table);
    hash_table=insert("OR",OR,hash_table);
    return hash_table;
}


/*int main()
{
    //to check whether lookup table is working properly
    hashTable *hash_table=populateTable();
    
    char *lexeme1="module";
    char *lexeme2="module1";
    lookUp *token1=search(hash_table,lexeme1);
    if(token1==NULL)
    {
        printf("Token1 Not found\n");

    }
    else
    {
        printf("Found Token1\n");
        printf("Lexeme: %s ",token1->lexeme);
        printf("Corresponding Keyword: %s\n",tokenName[token1->type]);
    }
    lookUp *token2=search(hash_table,lexeme2);
    if(token2==NULL)
    {
        printf("Token2 Not found\n");

    }
    else
    {
        printf("Found Token2\n");
        printf("Lexeme: %s ",tokenName[token2->type]);
        printf("Corresponding Keyword: %s\n",token2->lexeme);
    }
    //  used to test the best possible size of hash table
    // int maxVal=1e9;
    // int ind=0;
    // int cnt=0;
    // for(int i=2;i<=100;i++)
    // {
       
    //     int isPrime=1;
    //     for(int j=2;j*j<=i;j++)
    //     {
    //         if(i%j==0)isPrime=0;
    //     }
    //     if(isPrime){
    //         numSlots=i;
    //         int arr[997];
            
    //         for(int i=0;i<997;i++)arr[i]=0;
    //         int len=sizeof(tokenName)/sizeof(tokenName[0]);
    //         for(int i=0;i<len;i++)
    //         {
    //             arr[hash(tokenName[i])]++;
    //             if(hash(tokenName[i])<0)cnt++;
    //         }
    //         int maxi=0;
    //         for(int i=0;i<997;i++)
    //         {
    //             maxi=max(maxi,arr[i]);
    //         }
    //         if(maxi<maxVal)
    //         {
    //             maxVal=maxi;ind=i;
    //         }
    //     }
    // }
    
   
    
    
    
}*/