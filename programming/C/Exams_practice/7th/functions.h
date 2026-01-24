#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define maxLength 30
//struct
typedef struct 
{
    char* IN;
    char a;
    char b;
}Arguments;

typedef struct Node
{
    char* key;
    struct Node* next;
}Node;

typedef struct
{
    Node* front; //testa
    Node* rear; //coda
}Queue;


//functions
Arguments readInput(int, char* []);
void enqueue(Queue*, char*);
char* deQueue(Queue*);
void buildQueue(Queue*, const char*);
char* elab(char*,char,char);
void printQueue(Queue*,char,char);
#endif