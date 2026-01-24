#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define maxLength 30
//struct
typedef struct
{
    char* IN;
    int k; //[5-15]
}Arguments;

typedef struct Node
{
    char* key;
    struct Node* next;
}Node;

typedef struct
{
    Node *top;
}Stack;

//functions
Arguments readInput(int num_args, char* arg_values[]);
void pushWord(Stack *, char* );
char* popWord(Stack *);
void buildStack(Stack *, const char* );
char* sortWord(char*);
void printStack(Stack *, int);

#endif