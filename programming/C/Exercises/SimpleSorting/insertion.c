#include <stdio.h>
#include <stdlib.h>

/* Insertion sorting */
//PROPOTIPO DI FUNZIONE
void my_insertion_sort(int *,int);

//DEFINIZIONE DI FUNZIONE
void my_insertion_sort(int *a,int n)
{
    //scorrimento array
    for(int i=0;i<n;i++)
    {
        int temp = a[i+1]; //se i=0 temp sarà uguale a a[1];
        //confronto con temp
        //confronto tutti i valori a sinistra e sposto a destra i valori che corrispondono al confronto 
        for(int j=i;j>0;j--) //devo partire da j=i-1 perché devo comparare tutti i valori a sinistra di temp
        {
            if(temp < a[j])
            {
                a[j+1]=a[j];
                a[j] = temp;
            }
        }
    }
}
///////////////////////////////////////
int main()
{
    int array[] = {1,5,3,4,2,6,8,7,9};
    int n = sizeof(array)/sizeof(array[0]);
    my_insertion_sort(array,n);
    for(int i=0;i<n;i++)
        printf("%d ",array[i]);
    return 0;
}

/* FUNZIONAMENTO INSERTION_SORT:
*
*  i=0      [8] 4 6 1 2 7 5 3
*  i=1      [4 8] 6 1 2 7 5 3
*  i=2      [4 6 8] 1 2 7 5 3
*  i=3      [1 4 6 8] 2 7 5 3
*  i=4      [1 2 4 6 8] 7 5 3
*  i=5      [1 2 4 6 7 8] 5 3
*  i=6      [1 2 4 5 6 7 8] 3
*  i=7      [1 2 3 4 5 6 7 8]
*
*/