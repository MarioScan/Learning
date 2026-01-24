#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define maxLength 30
//struct
typedef struct
{
    char* IN;
    int k;
}Arguments;

typedef struct Node
{
    char* key;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct 
{
    Node* top;
}Stack;

//functions
Arguments readInput(int, char* []);
void insertWord(Stack *,char*);
void buildList(Stack*, const char*);
void printList(Stack*);
void elab(Stack*, int);


#endif