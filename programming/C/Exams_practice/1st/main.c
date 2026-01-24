#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"


int main(int argc, char *argv[])
{
    Arguments args = readInput(argc, argv);

    printf("File in input: \"%s\"\n",args.input);
    printf("File in output: \"%s\"\n",args.output);

    record arr[maxArray];
    buildArray(arr,args.input);
    filter(arr);
    createSet(arr);
    printArray(arr);
    save(arr,args.output);
    read(args.output);
    
    return 0;
}