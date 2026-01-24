#include "functions.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    Arguments args = readInput(argc,argv);
    Stack stack;
    stack.top = NULL;
    buildList(&stack,args.IN);
    elab(&stack,args.k);
    printList(&stack); 
    
    return 0;
}