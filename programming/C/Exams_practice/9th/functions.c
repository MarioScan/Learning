#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

record readInput(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr,"Invalid number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    record rec;
    rec.IN = argv[1];

    return rec;
}

void enqueueWord(Queue* queue, char* word)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode)
    {
        fprintf(stderr,"Impossible to allocate memory for a new node.\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = strdup(word);
    newNode->next = NULL;

    if(queue->front == NULL)
    {
        queue->front = queue->rear = newNode;
        return;
    } 
    queue->rear->next = newNode;
    queue->rear = newNode;
}

char* dequeueWord(Queue* queue)
{
    if(queue->front == NULL)
    {
        return NULL;
    }

    Node* temp = queue->front;
    char* releaseWord = strdup(temp->key);
    queue->front = queue->front->next;

    if(queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(temp);
    return releaseWord;
}

void buildqueue(Queue* q, const char* file_name)
{
    FILE* file = fopen(file_name,"r");
    if(!file)
    {
        fprintf(stderr,"Impossible to open the input file for the reading.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[maxLength];
    while(fscanf(file,"%29s",buffer) == 1)
    {
        enqueueWord(q,buffer);
    }

    fclose(file);
}

char** buildStringArray(Queue* q, int* n)
{
    int dim = 10;
    char** array = (char**)malloc(sizeof(char*) * dim);
    if(!array)
    {
        fprintf(stderr,"Impossible to allocate memory for a string array.\n");
        exit(EXIT_FAILURE);
    }

    char* buffer;
    int c=0;
    while((buffer = dequeueWord(q)) != NULL)
    {
        //printf("%s\n",buffer);
        if(dim <= c)
        {
            dim *= 2;
            array = realloc(array, dim * (sizeof(char*)));
            if(!array)
            {
                fprintf(stderr,"Impossible to reallocate the string array to allocate more memory.\n");
                exit(EXIT_FAILURE);
            }
        }
        array[c++] = strdup(buffer); 
    }
    *n = c;
    return array;
}

void sortArray(char** array, int n)
{
    for(int i=0;i<n-1;i++)
    {
        int min=i;
        for(int j=i+1;j<n;j++)
        {
            if(strcmp(array[min],array[j]) > 0)
            {
                min = j;
            }
        }
        if(min != i)
        {
            char* temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
}

void printArray(char** array, int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%s\n",*(array+i));
    }
}