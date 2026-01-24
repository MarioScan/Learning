#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//Struct
typedef struct
{
    unsigned int N; //5-10
    char a;
    char b;
    //a-z 
}Arguments;

typedef struct Node
{
    char c;
    struct Node *next;
}Node;

typedef struct
{
    Node* top;
}Stack;

//Functions
Arguments readInput(int , char* []);
char genVowel();
char genConsonant();
unsigned int get_random();
void push(Stack *, char);
void fillStack(Stack *, unsigned int, char, char);
void printStack(Stack *);

#endif