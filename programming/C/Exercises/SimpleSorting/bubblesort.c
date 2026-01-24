#include <stdio.h>

/* Algoritmo di ordinamento Bubble Sort */
//Propotipo funzione
void my_bubble_sort(int *,int);

//Definizione funzione
void my_bubble_sort(int *a,int n)
{
    //scorrimento array
    for(int i=0;i<n;i++)
    {
        //scorrimento scambio
        for(int j=0;j<n-i-1;j++) //perché j<n-i-1 --> ad ogni iterazione l'elemento più pesante viene portato nell'ultima cella dell'array, perciò non bisogna più accedervi, e così anche la penultima nella seconda etc.
        {
            int temp = a[j+1];
            if(temp < a[j])
            {
                //swap dei valori
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
/////////////////////////
int main()
{
    int arr[] = {9,7,8,4,6,5,3,1,2};
    int n = sizeof(arr) / sizeof(*(arr+0));
    my_bubble_sort(arr,n);
    for(int i=0;i<n;i++)
        printf("%d ",*(arr+i));
    return 0;
}

/* FUNZIONAMENTO BUBBLESORT:
*
*    i=0  [8 4] 6 1 2 7 5 3
*    i=0  4 [8 6] 1 2 7 5 3
*    i=0  4 6 [8 1] 2 7 5 3
*    i=0  4 6 1 [8 2] 7 5 3
*    i=0  4 6 1 2 [8 7] 5 3
*    i=0  4 6 1 2 7 [8 5] 3
*    i=0  4 6 1 2 7 5 [8 3]
*    i=1  [4 6] 1 2 7 5 3 8
*
*/ 