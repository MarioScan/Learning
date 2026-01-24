#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

Arguments readParameters(int num_args, char* args_value[])
{
    if(num_args != 3)
    {
        fprintf(stderr, "Error: invalid number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    Arguments args;
    strcpy(args.IN, args_value[1]);
    strcpy(args.OUT,args_value[2]);
    
    return args;
}

double*** createMatrix(const char *file_name, int *a, int *b)
{
    FILE *file = fopen(file_name,"r");
    if(!file)
    {
        fprintf(stderr,"Error: Impossibile to open the input file for the reading of the content.\n");
        exit(EXIT_FAILURE);
    }

    char buffer;
    int rows = 0;
    int col = 0;
    int firstRow = 0;
    while((buffer = fgetc(file)) != EOF)
    {
        if(buffer == '\n')
        {
            rows++;
            firstRow = 1;
        }
        else if(firstRow != 1 && buffer == ' ')
        {
            col++;
        }
    }
    col++;
    rows++;

    double ***m = (double***)malloc(sizeof(double**) * rows);
    for(int i=0;i<rows;i++)
    {
        m[i] = (double**)malloc(sizeof(double*) * col);
        for(int j=0;j<col;j++)
        {
            m[i][j] = (double*)malloc(sizeof(double));
        }
    }
    rewind(file); //analogamente: fseek(file, 0, SEEK_SET) //SEEK_SET --> inizio ; SEEK_END --> fine
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<col;j++)
        {
            fscanf(file,"%lf",m[i][j]);
        }
    }

    fclose(file);

    *a = rows;
    *b = col;    
    return m;
}

void sparsify(double ***m, int a, int b)
{
    for(int i=0;i<a;i++)
    {
        double media;
        for(int j=0;j<b;j++)
        {
            if(j==0)
                media = *m[i][j];
            else media += *m[i][j];
        }
        media /= b;
        for(int j=0;j<b;j++)
        {
            if(media > *m[i][j])
            {
                free(m[i][j]);
                m[i][j] = NULL;
            }
        }
        
    }
}

double* collect(double***m, int a, int b, int *newSize)
{
    double* m1 = (double*)malloc(sizeof(double)*(a*b));
    int c=0;
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<b;j++)
        {
            if(m[i][j] != NULL)
            {
                m1[c++] = *m[i][j];
            }
        }
    }
    *newSize = c;
    return m1;
}

void writeToFile(double *m1, int c, const char *file_name)
{
    FILE* file = fopen(file_name, "w");
    if(!file)
    {
        fprintf(stderr,"Error: cannot open output file for the writing of the data.\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<c;i++)
    {
        fprintf(file,"%f ",m1[i]);
    }

    fclose(file);
}