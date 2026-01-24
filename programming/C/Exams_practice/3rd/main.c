#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    Arguments args = readParameters(argc, argv);
    int a,b;
    double*** m = createMatrix(args.IN,&a,&b);
    printf("a = %d\nb = %d\n",a,b);
    sparsify(m,a,b);
    int c;
    double* m1 = collect(m,a,b,&c);
    writeToFile(m1,c,args.OUT);

    return 0;
}