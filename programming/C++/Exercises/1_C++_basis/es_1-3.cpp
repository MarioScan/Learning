/* Scrivi un programma che:

Legge n da tastiera.

Alloca dinamicamente un array di n interi.

Chiede all’utente i numeri e li salva nell’array.

Calcola e stampa la media.

Libera la memoria. */

#include <iostream>

int main()
{
    //1
    int n;
    do{
        std::cout << "Benvenuto, inserisci dimensione array (2-10): "; std::cin >> n; 
        if(n < 2 || n > 10)
        {
            std::cout << "Valori non validi: riprova." << std::endl;
        }
    }while(n < 2 || n > 10);
    
    //2
    int* arr = new int[n];
    
    std::cout << "Vuoi inserire >> " << n << "numeri >> nello array. Procediamo:" << std::endl;
    for(int i=0;i<n;i++)
    {
        std::cout << "array["<< i <<"] = "; std::cin >> arr[i];
    }
    float* media= new float;
    *media = 0;
    std::cout << "Controlliamo array con i valori inseriti:" << std::endl;
    for(int i=0;i<n;i++)
    {
        std::cout << "array[" << i << "] = " << arr[i] << std::endl;
        *media+=arr[i];
    }
    *media /= n;
    std::cout << "Media dei valori delle celle dello array --> " << *media << std::endl;

    delete media;
    delete[] arr;

    /* EXTRA: null pointers (nullptr) */

    //int* punta = new int; 
    //*punta = nullptr; //Non valido
    int* punta = nullptr; 
    //std::cout << "Puntatore \"punta\" = " << *punta << std::endl; //ERRORE: SEGMENTATION FAULT!! puntatore tenta accesso a nulla, crash sistema.
    //*punta = 10; //ERRORE! stai cercando di scrivere in un indirizzo che non esiste.
    punta = new int;
    *punta = 10;
    std::cout << "Puntatore \"punta\" = " << *punta << std::endl; //adesso funziona.
    
    delete punta;

    return 0;
}

