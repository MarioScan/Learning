#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arguments readInput(int argc, char* argv[])
{
    if(argc != 4)
    {
        fprintf(stderr,"Invalid number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    Arguments args;
    args.IN = argv[1];
    args.a = argv[2][0];
    args.b = argv[3][0];

    if(args.a < 'a' || args.a > 'z')
    {
        fprintf(stderr,"Invalid value for the variable \"a\". Expected: [\'a\'-\'z\'] ; provided %c.\n",args.a);
        exit(EXIT_FAILURE);
    }

    if(args.b < 'a' || args.b > 'z')
    {
        fprintf(stderr,"Invalid value for the variable \"b\". Expected: [\'a\'-\'z\'] ; provided %c.\n",args.b);
        exit(EXIT_FAILURE);
    }

    return args;
}

void enqueue(Queue* q, char* word)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode)
    {
        fprintf(stderr,"Impossible to allocate memory for a new node.\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = strdup(word);
    newNode->next = NULL;

    if(q->rear == NULL) //queue is not empty:
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode; //front queue is equal to new node
        q->rear = newNode;
    }
}

char* deQueue(Queue* queue)
{
    if(queue->front == NULL) //queue is empty
    {
        return NULL;
    }

    Node* temp = queue->front;
    char* releaseWord = strdup(temp->key);
    queue->front = queue->front->next;

    if(queue->front == NULL) //is queue now empty?
    {
        queue->rear = NULL; //then reset also the end pointer
    }

    free(temp);
    return releaseWord;
}

void buildQueue(Queue* queue, const char* file_name)
{
    FILE* file = fopen(file_name, "r");
    if(!file)
    {
        fprintf(stderr,"Impossible to open the input file for the reading.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[maxLength];
    while(fscanf(file,"%29s",buffer) == 1)
    {
        enqueue(queue,buffer);
    }

    fclose(file);
}

char* elab(char* word, char a, char b)
{
    if(!word)
    {
        fprintf(stderr,"Impossible to read the string.\n");
        exit(EXIT_FAILURE);
    }

    char* elabWord = strdup(word);
    
    for(int i=0;i<strlen(elabWord);i++)
    {
        if(elabWord[i] >= a && elabWord[i] <= b)
        {
            elabWord[i] = '0';
        }
    }
    
    return elabWord;
}

void printQueue(Queue* queue, char a, char b)
{
    while(queue->front != NULL)
    {
        char* printWord = strdup(deQueue(queue));
        printWord = elab(printWord,a,b);
        printf("%s\n",printWord);
    }
}