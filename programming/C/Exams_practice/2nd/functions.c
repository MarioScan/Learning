#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Arguments readInput(int num_args, char *arg_values[])
{
    if(num_args != 5)
    {
        fprintf(stderr,"Error: incorrect number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    Arguments args;
    args.a = atoi(arg_values[1]);
    args.b = atoi(arg_values[2]);
    args.alpha = atof(arg_values[3]);
    args.beta = atof(arg_values[4]);

    if(args.a < 5 || args.a > 20)
    {
        fprintf(stderr,"Error: value of \"a\" out of range. Expected: [5-20], given: %d.\n",args.a);
        exit(EXIT_FAILURE);
    }
    else if(args.b < 5 || args.b > 20)
    {
        fprintf(stderr,"Error: value of \"b\" out of range. Expected: [5-20], given: %d.\n",args.b);
        exit(EXIT_FAILURE);
    }
    else if(args.alpha < 10 || args.a > 20)
    {
        fprintf(stderr,"Error: value of \"alpha\" out of range. Expected: [10-20], given: %f.\n",args.alpha);
        exit(EXIT_FAILURE);
    }
    else if(args.beta < 1 || args.beta > 5)
    {
        fprintf(stderr,"Error: value of \"beta\" out of range. Expected: [1-5], given: %f.\n",args.beta);
        exit(EXIT_FAILURE);
    }

    return args;
}

double*** allocMatrix(int a, int b)
{
    double*** allocatedMatrix = (double***)malloc(sizeof(double**) * a);
    for(int i=0;i<a;i++)
    {
        allocatedMatrix[i] = (double**)malloc(sizeof(double*) * b);
        for(int j=0;j<b;j++)
        {
            allocatedMatrix[i][j] = (double*)malloc(sizeof(double));
        }
    }

    return allocatedMatrix;
}

void fillMatrix(double***Matrix, int a, int b, double alpha, double beta)
{
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<b;j++)
        {
            double p = (double)get_random() / (UINT_MAX + 1.0);
            if(p > 0.2)
            {
                *Matrix[i][j] = (alpha-beta) + (double)get_random() / (UINT_MAX + 1.0) * (alpha+beta);
                // il calcolo di base restituisce un numero da 0 a 1 
                //* --> estende il calcolo da 0 a alpha+beta numeri
                //+ --> estende il range da alpha-beta a alpha+beta numeri 
            }
            else Matrix[i][j] = NULL;
        }
    }
}

unsigned int get_random() 
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);

    return (m_z << 16) + m_w;
}

double*** transposeMatrix(double***m, int a, int b)
{
    double*** m1 = allocMatrix(b,a);
    for(int i=0;i<b;i++)
    {
        for(int j=0;j<a;j++)
        {
            if(m[j][i] != NULL)
            {
                *m1[i][j] = *m[j][i];
            }
            else m1[i][j] = NULL;
        }
    }
    return m1;
}

void printMatrix(double***Matrix, int a, int b)
{
    printMatrixName(Matrix,a,b)
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<b;j++)
        {
            if(Matrix[i][j] != NULL)
            {
                printf("%.2f ",*Matrix[i][j]);
            }
            else printf("N ");
        }
        printf("\n");
    }
    printf("\n\n");
}