#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arguments readInput(int argc, char* argv[])
{
    if(argc != 3)
    {
        fprintf(stderr,"Invalid number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    Arguments args;
    args.IN = argv[1];
    args.k = atoi(argv[2]);

    if(args.k < 5 || args.k > 15)
    {
        fprintf(stderr,"Invalid value of the variable \"k\". Expected: [5-15] ; provided: %d.\n",args.k);
        exit(EXIT_FAILURE);
    }

    return args;
}

void pushWord(Stack* stack, char* word)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode)
    {
        fprintf(stderr,"Error: impossible to allocate memory for a new node.\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = strdup(word);
    newNode->next = stack->top;
    stack->top = newNode;
}

char* popWord(Stack* stack)
{
    if(stack->top == NULL)
    {
        return NULL; 
    }
    Node* temp = stack->top;
    char* releasedWord = strdup(temp->key);
    stack->top = stack->top->next;
    free(temp->key);
    free(temp);

    return releasedWord;
}

void buildStack(Stack* stack, const char* file_name)
{
    FILE* file = fopen(file_name,"r");
    if(!file)
    {
        fprintf(stderr,"Impossible to open the input file (\"%s\") for the reading.\n",file_name);
        exit(EXIT_FAILURE);
    }

    char buffer[maxLength];
    while(fscanf(file,"%29s",buffer) == 1)
    {
        pushWord(stack,buffer);
    }

    fclose(file);
}

char* sortWord(char* word)
{
    if(!word)
    {
        fprintf(stderr,"Impossible to read the string.\n");
        exit(EXIT_FAILURE);
    }

    char* sortedWord = strdup(word);
    int len = strlen(sortedWord);
    for(int i=0;i<len-1;i++)
    {
        int min=i;
        for(int j=i;j<len;j++)
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

void printStack(Stack* stack, int k)
{
    while(stack->top != NULL)
    {
        char* word = strdup(popWord(stack));
        if(strlen(word) >= k)
        {
            strcpy(word,sortWord(word));
        }
        printf("%s\n",word);
    }
}