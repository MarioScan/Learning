#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define maxLength 30
//struct
typedef struct
{
    char* IN;
}record;

typedef struct Node
{
    char* key;
    struct Node* next;
}Node;

typedef struct
{
    Node* front;
    Node* rear;
}Queue;

//funzioni
record readInput(int, char* []);
void enqueueWord(Queue*,char*);
char* dequeueWord(Queue*);
void buildqueue(Queue*,const char*);
char** buildStringArray(Queue*, int*);
void sortArray(char**, int);
void printArray(char**, int);

#endif