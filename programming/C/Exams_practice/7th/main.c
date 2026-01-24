#include "functions.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    Arguments args = readInput(argc,argv);
    Queue queue;
    queue.front = NULL;
    queue.rear = NULL;

    buildQueue(&queue,args.IN);
    printQueue(&queue,args.a,args.b); 
    
    return 0;
}