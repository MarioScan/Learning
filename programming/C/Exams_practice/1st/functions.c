#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

Arguments readInput(int num_args, char *arg_values[])
{
    if(num_args != 3)
    {
        fprintf(stderr,"Errore: numero di argomenti inseriti non valido.\n\n");
        exit(EXIT_FAILURE);
    }

    Arguments storedArguments;
    storedArguments.input = arg_values[1];
    storedArguments.output = arg_values[2];

    return storedArguments;
}

void buildArray(record *Record, const char* file_name)
{
    FILE *file = fopen(file_name, "r");
    if(!file)
    {
        fprintf(stderr,"Errore: impossibile aprire il file in input per la lettura.\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<maxArray;i++)
    {
        if(fscanf(file,"%19s",Record[i].key) == 1 ) //19 + 1 (per il carattere di terminazione)
        {
            Record[i].length = strlen(Record[i].key);
        }
        else //valori in eccesso
        {
            Record[i].key[0] = '\0';
            Record[i].length = -1;
        }
    }

    fclose(file);
}

void filter(record *Record)
{
    for(int i=0;i<maxArray;i++)
    {
        int len = strlen(Record[i].key);
        int c=0;
        char cleaned_key[maxLength];
        for(int j=0;j<len;j++)
        {
            if(Record[i].key[j] != ',' && Record[i].key[j] != ';' && Record[i].key[j] != ':' && Record[i].key[j] != '.')
            {
                cleaned_key[c] = Record[i].key[j];
                c++;
            }
        }
        cleaned_key[c] = '\0';
        strcpy(Record[i].key,cleaned_key);
        Record[i].length = strlen(Record[i].key);
    }
}

void createSet(record *Record)
{
    for(int i=0;i<maxArray-1;i++)
    {
        for(int j=i+1;j<maxArray;j++)
        {
            if(strcmp(Record[i].key,Record[j].key) == 0)
            {
                Record[j].length = -1;
            }
        }
    }
}

void printArray(record *Record)
{
    for(int i=0;i<maxArray;i++)
    {
        if(Record[i].length > 0)
        {
            fprintf(stdout,"%s ",Record[i].key);
        }
    }
}

void save(record *Record, const char* file_name)
{
    FILE *file = fopen(file_name,"wb");
    if(!file)
    {
        fprintf(stderr,"Errore: impossibile aprire il file di output per la scrittura.\n");
        exit(EXIT_FAILURE);
    }

    if(fwrite(Record,sizeof(record),maxArray,file) != maxArray)
    {
        fprintf(stderr,"Errore durante scrittura dei dati sul file di output, chiusura immediata del programma.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

void read(const char* file_name)
{
    FILE *file = fopen(file_name,"rb");
    if(!file)
    {
        fprintf(stderr,"Errore durante apertura file di output per la lettura.\n");
        exit(EXIT_FAILURE);
    }

    record *readRecord = (record*)malloc(sizeof(record) * maxArray);
    if(fread(readRecord,sizeof(record),maxArray,file) != maxArray)
    {
        fprintf(stderr,"Errore durante lettura dati in file output.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<maxArray;i++)
    {
        printf("{%s , %d}\n",readRecord[i].key,readRecord[i].length);
    }
    
    fclose(file);
}