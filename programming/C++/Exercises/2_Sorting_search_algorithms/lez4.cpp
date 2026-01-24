
/*<2> Algoritmi:

Ordinamenti base: Bubble, Selection, Insertion

Ordinamenti ricorsivi: MergeSort, QuickSort
*/

#include <iostream>
#include <cstdlib> //uso per funzioni rand() e srand() per generare numeri casuali per la mia matrice.
#include <ctime> //libreria per funzione time()
using namespace std;

void stampa(int[], const int&);
void random(int[], const int&);
void BubbleSort(int[],const int&);
void SelectionSort(int[],const int&);
void InsertionSort(int[], const int&);
void merge(int[], int[],int[], int, int);
void mergeSort(int[], int);
int partition(int[], int, int);
void QuickSort(int[],int,int);

void stampa(int arr[], const int& dim) 
{
    cout << "Stampa array:" << endl;
    for(int i=0;i<dim;i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << endl; 
    }
}

void random(int arr[], const int& dim) 
{
    cout << "\n\n------------------------------------------\nRandomizziamo gli elementi nell'array...\n" << endl;
    for(int i=0;i<dim;i++)
    {
        arr[i] = rand() % 20 + 1;
        cout << arr[i] << ", ";
    }
    cout << "\n------------------------------------------\n" << endl;
}

//Le mie funzioni di ordinamento... 

void BubbleSort(int a[], const int& dim)
{
    for(int i=0;i<dim-1;i++)
    { //scorre tutto l'array, all'ultimo posto non c'è nulla da scambiare alla sua destra, quindi fino a dim-1. 
        for(int j=0; j<dim-i-1;j++) //dopo ogni ciclo, l'ultimo elemento è necessariamente quello più grande/piccolo della lista (ordine crescente/decrescente).
        {
            if(a[j]>a[j + 1])
                swap(a[j],a[j+1]);
        }
    }
}

void SelectionSort(int arr[], const int& dim)
{
    for(int i=0;i<dim - 1;i++) //controlla l'intera lista fino all'elemento prima della fine.
    {
        int min = i; //salva indice minore, partendo dalla nostra i 
        for(int j=i+1;j<dim;j++) //controlla dall'elemento successivo a quello i-esimo  
        {
            if(arr[j] < arr[min])
                min = j; //indice j diventa il nuovo elemento minore --> continua poi per tutta la lista, troveremo elemento più piccolo
        }
        swap(arr[i],arr[min]); //scambiamo di posto la nostra cella i con quella di indice minore 
    }
}


void InsertionSort(int a[], const int& dim)
{
    for(int i=1;i<dim;i++) //ciclo degli elementi da ordinare
    {
        int key = a[i];
        int k=i-1;
        while(k>=0 && a[k] > key)
        {
            a[k+1] = a[k]; //alla fine permette di slittare tutti gli elementi di un posto per il nuovo elemento da inserire
            k--;
        }
        a[k+1] = key;
    }
}

void merge(int leftArray[], int RightArray[], int array[], int leftSize, int RightSize) //unisce in maniera ordinata due array
{
    int i = 0, l = 0, r = 0; //indice finale array, left index , right index

    //Confronto dei due array:
    while(l < leftSize && r < RightSize)
    {
        if(leftArray[l] < RightArray[r])
            array[i++] = leftArray[l++];
        else // >= 
            array[i++] = RightArray[r++];
    }
    //inserimento eventuali elementi da sinistra () 
    while(l < leftSize)
        array[i++] = leftArray[l++];
    
    //e da destra...
    while(r < RightSize)
        array[i++] = RightArray[r++]; 
}

void mergeSort(int array[], int length) //divide i due array finché non ho solo sotto-array di 1 elemento ciascuno
{
    if(length <= 1)
        return; //caso base: array già ordinato.
    
    int middle = length / 2; 

    //Creazione dei due sotto-array
    int* leftArray = new int[middle];
    int* rightArray = new int[length - middle];

    int i = 0, j = 0;
    
    //Copia elementi nei due sotto-array
    for(; i < length; i++)
    {
        if(i < middle)
            leftArray[i] = array[i];
        else 
            rightArray[j++] = array[i];
    }

    //Uso ricorsione della funzione:
    mergeSort(leftArray,middle);
    mergeSort(rightArray,length - middle);

    //Unione ed ordinamento:
    merge(leftArray,rightArray,array,middle,length-middle);

    //libero la memoria dinamica dei due array di appoggio
    delete[] leftArray;
    delete[] rightArray; 
}

int partition(int array[], int start, int end)
{
    int pivot = array[end]; //prendiamo come standard il pivot come ultimo elemento dell'array (si può anche scegliere diversamente)
    int i = start - 1; //tiene traccia dell'ultima posizione più piccola del pivot

    for(int j = start; j < end ; j++)
    {
        if(array[j] < pivot)
        {
            i++;
            swap(array[i],array[j]); //Ordina elementi 
        }
    }

    //Alla fine posizioniamo il pivot tra le due zone ->
    // X < pivot > Y             con X = x1,x2,...,xn e, analogamente Y = y1,y2,...,yn
    i++;
    swap(array[i],array[end]);

    return i; //ritorna posizione pivot
}

void QuickSort(int array[], int start, int end)
{
    if (end <= start)
        return; //caso base: sotto-array di 0-1 elementi 
    
    int pivot = partition(array,start,end);
    QuickSort(array, start, pivot-1); //Ordina lato sinistro del pivot (pivot escluso!)
    QuickSort(array, pivot + 1, end); //Ordina lato destro del pivot (pivot escluso!)
}

int main()
{
    //per randomizer
    srand(time(nullptr));

    int n = 10;
    int* arr = new int[n];
    random(arr,n); //in questo caso lo usiamo per creare elementi nel nostro array...
    stampa(arr,n);

    cout << "\n--- Ordinamento crescente con BubbleSort ---" << endl;
    /* --- Bubble Sort ---
    <-> Funzionamento:
        ad ogni step si controlla se due elementi adiacenti sono in ordine, altrimenti vengono scambiati;
        così via per tutti gli altri, e poi si procede nuovamente, tante volte quanti sono gli elementi della lista.
    <-> Tempo di ordinamento:
        O(n^2)
    <-> Complessità dello spazio:
        O(1) --> Spazio costante 

    PRO:
        - è facile da comprendere;
    CONTRO:
        - è uno degli algoritmi di ordinamento MENO EFFICIENTI.
    */
    BubbleSort(arr,n);
    stampa(arr,n);

    cout << "\n--- Ordinamento crescente con SelectionSort ---" << endl;
    /* --- Selection Sort ---
    <-> Funzionamento:
        Consiste nel prendere il primo elemento e cercare il più piccolo/grande di questi all'interno di tutta la lista, 
        e così via per tutti gli altri elementi.
    <-> Tempo di ordinamento:
        O(n^2)
    <-> Complessità dello spazio:
        O(1) --> Spazio costante      
    */
    random(arr,n);
    SelectionSort(arr,n);
    stampa(arr,n);
    
    cout << "\n--- Ordinamento crescente con InsertionSort ---" << endl;
    /* --- Insertion Sort ---
    <-> Funzionamento:
        Consiste nel prendere un elemento alla volta e risistemare questo elemento, tra gli elementi già ordinati dell'array.
    <-> Tempo di ordinamento:
        O(n²), efficace più che altro su array quasi ordinati   
    <-> Complessità dello spazio: 
        O(1) --> Spazio costante    
    */
    random(arr,n);
    InsertionSort(arr,n);
    stampa(arr,n);

    cout << "\n--- Ordinamento crescente con MergeSort ---" << endl;
    /* --- MergeSort ---
    <-> Funzionamento:
        Consiste nel dividere l'array a metà finché non abbiamo sotto-array di dimensione 1, 
        poi li riconnettiamo ai rispettivi precedenti sotto-array ordinandoli.
    <-> Tempo di ordinamento:
        O(n log n)
    <-> Complessità dello spazio:
        O(n) --> Spazio Lineare
        
        PRO: 
        - tempo di ordinamento efficiente --> O(n log n)
        - efficiente con dati grandi
        CONTRO:
        - può usare tanta memoria (uso di array temporanei)
    */
    random(arr,n);
    mergeSort(arr,n);
    stampa(arr,n);

    cout << "\n--- Ordinamento crescente con QuickSort ---" << endl;
    /* --- QuickSort ---
    <-> Funzionamento: 
        - muove piccoli elementi a sinistra di un pivot
        - ricorsivamente divide l'array in 2 partizioni
    <-> Complessità a run-time (tempo di ordinamento): 
        - Miglior caso  =   O(n log n) 
        - Caso medio    =   O(n log n) 
        - Caso peggiore =   O(n^2) --> Avviene se l'array è già quasi o del tutto ordinato. 
    <-> Complessità dello spazio:
        O(log n) --> Spazio logaritmico 

    PRO: 
        - richiede poca memoria;
        - può essere molto veloce se l'array non è ordinato
    CONTRO:
        - può essere lento (worse-case O(n^2) se l'array è già parzialmente o completamente ordinato.

    */
   random(arr,n);
   //int sizeArr = sizeof(arr) / sizeof(arr[0]); //Errore: Non puoi. C++ non tiene traccia della dimensione degli array allocati dinamicamente.
   //cout << "SizeArr: " << sizeArr << endl; //bisogna usare n come dimensione!
   QuickSort(arr,0, n - 1);
   stampa(arr,n);


    delete[] arr;

    return 0;
}