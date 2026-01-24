#include "functions.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    Arguments args = readInput(argc, argv);
    
    Stack stack;
    stack.top = NULL;

    buildStack(&stack,args.IN);
    printStack(&stack,args.k);

    return 0;
}