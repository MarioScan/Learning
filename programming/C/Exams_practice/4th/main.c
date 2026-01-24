#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    Arguments args = readInput(argc,argv);
    printf("File name: %s\nValue of k: %d\n",args.IN,args.k);
    Stack stack;
    stack.top = NULL;
    buildStack(&stack,args.IN);
    printStack(&stack,args.k);

    return 0;
}