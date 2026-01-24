/*

    Ricerca: Lineare, Binaria (rispettivamente ricerca iterativa e ricorsiva)

    --------------------------------------------
    |                  Ricerca                 |
    |        LINEARE             BINARIA       |
    |      (iterativa)         (ricorsiva)     |
    --------------------------------------------
*/

#include <iostream>
using namespace std;

int RicercaLineare(int array[], int dim, int key)
{
    int trovato;
    for(int i=0;i<dim;i++)
    {
        if(array[i] == key) 
            return i;
    }
    return -1;
}

int RicercaBinaria(int array[], int left, int right, int key)
{
    if(left > right)
        return -1; //non trovato 

    int middle = (left + right) / 2;
    if(array[middle] == key) 
        return middle; //trovato 
    
    if(key < array[middle])
        return RicercaBinaria(array,left, middle - 1,key);
    //else non necessario: se non è a sinistra allora è per forza a destra
    return RicercaBinaria(array,middle + 1,right,key);
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

int main()
{
    int array[] = {1,9,8,3,4,7,2,5,6};
    int n = sizeof(array) / sizeof(array[0]);
    cout << "Dimensione array: " << n << "\nArray: ";
    for(int i=0;i<n;i++)
    {
        cout << array[i] << " ";
    } 

    cout << "\n\n--- Ricerca lineare ---" << endl;
    /* --- Ricerca Lineare ---
        Necessaria quando gli elementi non sono ordinati
    */
    cout << "Inserisci numero da cercare: "; int key; cin >> key;
    int ris = RicercaLineare(array,n,key);
    if(ris> -1)
        cout << "Trovato numero in posizione: " << ris << "  (n.b.: si parte da 0)" << endl;
    else cout << "Numero non trovato, valore di ritorno non valido: " << ris << endl;

    //<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->

    cout << "\n<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->\n\nRiordiniamo array: " ; 
    SelectionSort(array,n);
    
    for(int i=0;i<n;i++)
    {
        cout << array[i] << " ";
    } 


    cout <<"\n\n--- Ricerca Binaria ---" << endl;
    /* --- Ricerca Binaria --- 
        Metodo migliore se gli elementi SONO ORDINATI
    */
    cout << "Inserisci numero da cercare: "; cin >> key; 
    int ris1 = RicercaBinaria(array,0,n-1,key);
    if(ris1 > -1)
        cout << "Trovato numero in posizione: " << ris << "  (n.b.: si parte da i=0)" << endl;
    else cout << "Numero non trovato, valore di ritorno non valido: " << ris << endl;

     
    return 0;
}