#include <stdio.h>
#include <stdlib.h> //funzione atoi 
/* Propotipo di funzione... */
int nfat(int n);

/* Definizione di funzione... */
int nfat(int n)
{
    if(n<1)
        return 1;
    printf("nfat(%d)\n",n);
    return n * nfat(n-1);
/* Il programma continuerà finché la condizione non sarà negativa, 
Esempio pratico:
n = 3:
3 * nfat(2) = 6 
6 * nfat(1) = 6*/
}

int main(int argc, char *argv[])
{
    if(argc<2)
    {
        printf("Inserisci un parametro per avviare il programma. Riprova.\n");
        return -1;
    }
    int n=1;
    n*=nfat(atoi(argv[1]));
    printf("Prodotto del numero fattoriale (%s!): %d\n",argv[1],n);
    return 0;
}