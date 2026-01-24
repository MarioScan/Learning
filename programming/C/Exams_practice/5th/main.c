#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    Arguments args = readInput(argc,argv);
    Stack stack;
    stack.top = NULL;
    fillStack(&stack,args.N,args.a,args.b);
    printStack(&stack);

    return 0;
}