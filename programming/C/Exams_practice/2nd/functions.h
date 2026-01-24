#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define printMatrixName(Matrix,a,b) printf("*** Matrice %s (%d x %d) ***\n",#Matrix,a,b);
//struct
typedef struct
{
    //5 - 20
    unsigned int a; 
    unsigned int b;
    //10 - 20
    double alpha;
    //1 -5 
    double beta;
}Arguments;

//funzioni
Arguments readInput(int num_args, char *arg_values[]);
double*** allocMatrix(int, int);
void fillMatrix(double***,int, int, double, double);
unsigned int get_random();
double*** transposeMatrix(double***,int,int);
void printMatrix(double***, int, int);

#endif