#ifndef FUNCTIONS_H
#define FUNCTIONS_h

//struct
typedef struct
{
    char IN[255];
    char OUT[255];
}Arguments;

//propotipo funzioni
Arguments readParameters(int num_args, char* arg_values[]);
double*** createMatrix(const char *, int *, int *);
void sparsify(double***, int, int);
double* collect(double***,int,int, int *);
void writeToFile(double*, int, const char*);

#endif