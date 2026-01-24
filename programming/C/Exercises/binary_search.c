#include <stdio.h>
#include <stdlib.h>


/* Algoritmo di ricerca binaria 
 in maniera ricorsiva.
*/
int binary_search(int[], int, int, int);

int binary_search(int arr[], int key, int left, int right)
{
    //int mid = (left + right) / 2; //funziona, ma porta rischio di OverFlow se si lavora con grandi dati...
    //si preferisce utilizzare di norma, questa espressione, che va a ridurre il rischio di OverFlow:
    int mid = left + (right - left) / 2; //significato equivalente ma l'espressione (right - left) permette di lavorare con dati più piccoli riducendo rischio di Overflow
    
    if(left > right)
        return -1; //valore non trovato.
    
    if(arr[mid] == key)
        return mid; //trovato!
    else if(arr[mid] > key) //la chiave si trova dal lato sinistro della meta' dell'array
        return binary_search(arr,key,left,mid-1);
    else if(arr[mid] < key) //la chiave si trova dal lato destro della meta' array
        return binary_search(arr,key,mid+1,right);
}

int main()
{
    int a[] = {1,2,5,7,9,12,14,17,18,20,23,24,25,27,29,30}; //dim = 16

    int key = 27; //valore che voglio trovare
    int left = 0; //la ricerca è su tutto l'array
    int right = sizeof(a)/sizeof(a[0]); //dimensione dell'array

    int r = binary_search(a,key,left,right);
    if(r)
        printf("Elemento trovato nella cella %d\n",r);
    else printf("Elemento non trovato.\n");
    return 0;
}