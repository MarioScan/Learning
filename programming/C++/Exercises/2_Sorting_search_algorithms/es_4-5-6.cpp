/*
Scrivi un programma in C++ che:

1. Legge n interi da file e li memorizza in un array

2. Applica l’algoritmo MergeSort

3. Applica la ricerca binaria per un numero scelto dall’utente

4. Stampa se il numero è presente, in quale posizione

5. Analizza il tempo teorico delle operazioni svolte
*/


#include <iostream>
#include <fstream>
using namespace std;

int* readFile(string, int&);
void printArray(int*, const int&);
void mergeSort(int*,int);
void merge(int*,int*,int*,int, int);
void binarySearch(int*,const int&,const int&);
int binarySearching(int*,int,int,const int&);

int* readFile(string nomeFile, int& dim)
{
    ifstream file(nomeFile);
    if(!file)
    {
        cerr << "Errore apertura file input." << endl;
        exit(0);
    }

    int num, contaNum = 0;
    while(file >> num) //vediamo quanti elementi ci sono (file >> num legge cosa c'è nel file)
        contaNum++;
    
    dim = contaNum;
    int* array = new int[dim];

    file.clear(); //ripristino file da eventuali errori scritti durante la lettura
    file.seekg(0,ios::beg); //porto il file a posizione 0, da beginning 

    // specifica la base: ios::beg, ios::cur, ios::end --> beginning, current, end  
    for(int i=0;i<dim;i++)
        file >> array[i];

    file.close();

    //dim modificato precedentemente
    return array;
}

void printArray(int* array, const int& dim)
{
    cout << "Stampa array:" << endl;
    for(int i=0;i<dim;i++)
    {
        cout << "array["<< i << "] = " << array[i] << endl;
    }
    cout << "Numero elementi array: " << dim << endl;
}

void merge(int* leftArray, int* rightArray, int* array, int leftSize, int rightSize)
{
    //indici dei tre array
    int i=0, left = 0, right = 0;

    //unione ed ordinamento
    while(left < leftSize && right < rightSize)
    {
        if(leftArray[left] < rightArray[right])
            array[i++] = leftArray[left++];
        else 
            array[i++] = rightArray[right++];
    }
    //elementi rimanenti
    while(left < leftSize)
        array[i++] = leftArray[left++];
    
    while(right < rightSize)
        array[i++] = rightArray[right++];
}

void mergeSort(int* array, int length)
{
    if(length<=1)
        return; 
    
    int middle = length / 2;

    //creazione dei due sotto-array:
    int* leftArray = new int[middle];
    int* rightArray = new int[length - middle];

    int i = 0 , j = 0 ;

    //Copia elementi nei due sotto-array
    for(; i < length; i++)
    {
        if(i < middle) //è nel lato sinistro? 
            leftArray[i] = array[i];
        else //no --> allora è lato destro:
            rightArray[j++] = array[i];
    }

    //Ricorsione...
    mergeSort(leftArray,middle);
    mergeSort(rightArray,length - middle);

    //Unione dei due array con ordinamento
    merge(leftArray,rightArray,array,middle,length-middle); //due sotto array, array a cui appartengono e dimensione ciascuna

    //libero memoria
    delete[] leftArray;
    delete[] rightArray;
}



void binarySearch(int* array,const int& dim,const int& key)
{
    if(key < 0) 
    {
        cout << "Errore: chiave di ricerca può solamente essere positiva, riprova." << endl;
        return;
    }

    int ris = binarySearching(array,0,dim-1,key);
    if(ris > 0)
    {
        cout << "Almeno un elemento corrispondente alla ricerca trovato nella cella numero: " << ris << endl;    
    }
    else cout << "Elemento non trovato." << endl;
}

int binarySearching(int* array,int left,int right,const int& key)
{
    if(left > right)
        return -1; //non trovato
    
    int middle = (left+right) / 2;
    
    if(array[middle] == key)
        return middle; //trovato
    
    if(key < array[middle])
        return binarySearching(array,left,middle-1,key);
    
    if(key > array[middle])
        return binarySearching(array,middle+1,right,key);

    return -2; //errore 

}


int main()
{
    //1)
    int n;
    string file = "array.txt";

    int* array = readFile(file,n);
    printArray(array,n);

    //2)
    cout << "Ordinamento array con algoritmo MergeSort..." << endl;
    mergeSort(array,n);
    printArray(array,n);

    //3 e 4)
    int key;
    cout << "Inserisci un valore da cercare nell'array: "; cin >> key;
    binarySearch(array,n,key);

    //5) 
    /*
        ___________________________________________________________________________________________________________________________________________
        | Operazione       | Complessità Tempo                      | Complessità Spazio                                                          |
        |------------------|----------------------------------------|-----------------------------------------------------------------------------|
        | readFile()       |   O(n)  (Lineare)                      |  O(n) (alloc. array)                                                        |
        | printArray()     |   O(n)  (Lineare)                      |  O(1) (solo stampa)                                                         |
        | mergeSort()      |   O(n log n)  (semi-lineare)           |  O(n) (sotto-array + ricorsività (ogni chiamata viene messa sullo stack))   |
        | binarySearch     |    O(1)                                |  O(1) (stampa e if)                                                         |
        | binarySearching()|   O(log n)  (Logaritmico)              |  O(log n) ricorsività (ogni chiamata viene messa sullo stack)               |
        |------------------|----------------------------------------|-----------------------------------------------------------------------------|
        | Totale:          | O(n log n) tempo dominante (MergeSort) |  O(log n) --> caso peggiore dominante (BinarySearching)                     |
        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    */
    return 0;
}