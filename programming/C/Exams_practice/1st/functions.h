#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define maxLength 20
#define maxArray 200
//mie struct
typedef struct
{
    char *input; //input txt file
    char *output; //output bin file
}Arguments;

typedef struct
{
    char key[maxLength];
    int length;
}record;

//mie funzioni
Arguments readInput(int num_args, char *arg_values[]);
void buildArray(record *Record, const char* file_name);
void filter(record *Record);
void createSet(record *Record);
void printArray(record *Record);
void save(record *Record, const char* file_name);
void read(const char* file_name);
 
#endif