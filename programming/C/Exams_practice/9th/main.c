#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    record r = readInput(argc, argv);
    
    Queue q;
    q.front = NULL;
    q.rear = NULL;

    buildqueue(&q,r.IN);
    int n;
    char** arr = buildStringArray(&q,&n);

    sortArray(arr,n);
    printArray(arr,n);

    for(int i=0;i<n;i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}