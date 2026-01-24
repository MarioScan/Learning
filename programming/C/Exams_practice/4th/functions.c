#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arguments readInput(int num_args, char* arg_values[])
{
    if(num_args != 3)
    {
        fprintf(stderr,"Error: Invalid number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    Arguments args;
    args.IN = arg_values[1];
    args.k = atoi(arg_values[2]);

    if(args.k < 5 || args.k > 15)
    {
        fprintf(stderr,"Invalid value of the variable \"k\", expected: [5-15] ; provided: %d\n",args.k);
        exit(EXIT_FAILURE);
    }

    return args;
}

void pushWord(Stack *stack, char* word)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode)
    {
        fprintf(stderr,"Error while allocating memory for a new Node.\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = strdup(word); //assegno valore a nuovo nodo
    // newNode --> cima della pila (last in first out -- LIFO --) 
    
    newNode->next = stack->top; //nuovo nodo punta al successivo 
    stack->top = newNode; //nuovo nodo diventa cima (top) della pila
}

char* popWord(Stack *stack)
{
    if(stack->top == NULL)
    {
        return NULL; //stack is empty...
    }

    char* releasedWord = strdup(stack->top->key);
    stack->top = stack->top->next;
    return releasedWord;
}

void buildStack(Stack* stack, const char* file_name)
{
    FILE *file = fopen(file_name,"r");
    if(!file)
    {
        fprintf(stderr,"Error: Impossible to open the input file for the reading.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[maxLength];
    while(fscanf(file,"%29s",buffer) == 1)
    {
        pushWord(stack,buffer);
        printf("Inserisco \"%s\" nello Stack...\n",buffer);
    }

    fclose(file);
}

char* sortWord(char *word)
{
    if(word == NULL)
    {
        fprintf(stderr,"Error: invalid word.\n");
        exit(EXIT_FAILURE);
    }

    char* sortedWord = strdup(word);

    for(int i=0;i<strlen(word)-1;i++)
    {
        int min = i;
        for(int j=i+1;j<strlen(word);j++)
        {
            if(sortedWord[min] > sortedWord[j])
            {
                min = j;
            }
        }
        if(min != i)
        {
            char temp = sortedWord[i];
            sortedWord[i] = sortedWord[min];
            sortedWord[min] = temp;
        }
    }
    return sortedWord;
}

void printStack(Stack *stack, int k)
{
    char* poppedWord;
    while((poppedWord = strdup(popWord(stack))) != NULL)
    {
        if(strlen(poppedWord) >= k)
        {
            poppedWord = sortWord(poppedWord);
        }
        printf("%s\n",poppedWord);
    }
}