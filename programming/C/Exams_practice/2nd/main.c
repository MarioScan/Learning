#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    Arguments args = readInput(argc, argv);
    double*** m = allocMatrix(args.a,args.b);
    fillMatrix(m,args.a,args.b,args.alpha,args.beta);
    double*** m1 = transposeMatrix(m,args.a,args.b);
    printMatrix(m,args.a,args.b);
    printMatrix(m1,args.b,args.a);
    return 0;
}