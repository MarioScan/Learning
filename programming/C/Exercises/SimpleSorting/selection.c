#include <stdio.h>

/* Selection Sort */
//PROPOTIPO
void my_selection_sort(int *, int);

//DEFINIZIONE
void my_selection_sort(int *a, int n)
{
    //scorrimento array
    for(int i=0;i<n;i++)
    {
        int min = i; //min serve per conservare l'indice, senza non sarebbe facile determinare in quale cella si trova il valore...
        //scorrimento ricerca
        for(int j=i+1;j<n;j++)
        {
            if(a[min] > a[j])
            {
                //swap elementi 
                int temp = a[j];
                a[j] = a[min];
                a[min] = temp;
            }
        }
    }
}
//////////////////////
int main()
{
    int array[] = {8,7,9,6,2,3,4,5,1};
    int n = sizeof(array)/sizeof(array[0]);
    my_selection_sort(array,n);
    for(int i=0;i<n;i++)
        printf("%d ",*(array+i));
    return 0;
}

/* FUNZIONAMENTO SELECTION_SORT:
*
*  i=0      [8] 4 6 [1] 2 7 5 3
*  i=1      1 [4] 6 8 [2] 7 5 3
*  i=2      1 2 [6] 8 4 7 5 [3]
*  i=3      1 2 3 [8] [4] 7 5 6
*  i=4      1 2 3 4 [8] 7 [5] 6
*  i=5      1 2 3 4 5 [7] 8 [6]
*  i=6      1 2 3 4 5 6 [8] [7]
*  i=7      1 2 3 4 5 6 7 8
*
*/