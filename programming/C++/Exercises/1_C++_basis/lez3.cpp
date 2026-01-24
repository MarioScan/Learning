#include <iostream>

//ALLOCAZIONE DINAMICA E LIBERAZIONE DELLA MEMORIA

struct Punto
{
    int x,y;
};

int main()
{
    //Allocazione dinamica di un intero
    std::cout << "1) new/delete" << std::endl;

    int *ptr = new int; //allocazione dinamica della memoria  --> new int alloca un intero in memoria heap e restituisce un puntatore a quell'intero
    std::cout << "Stampa puntatore dopo creazione: " << *ptr << std::endl;
    *ptr = 10; //assegnamo 10 all'intero cui punta il nostro puntatore
    std::cout << "Stampa puntatore dopo assegnazione del valore: " << *ptr << std::endl;
    delete ptr;
    std::cout << "Delete del puntatore effettuato." << std::endl;

    //Array dinamici
    std::cout << "2) Array dinamici" << std::endl;

    int *arr = new int[5]; //array dinamico di 5 interi
    std::cout << "Stampa array: ";
    for(int i=0;i< (sizeof(arr) / sizeof(arr[0])); i++)
    {
        *(arr+i) = 0;
        std::cout << (*(arr+i) + (i*2)) << " ";
    }
    std::cout << std::endl;

    delete[] arr; //delete arr undefined behavior (comportamento imprevedibile) --> importante scrivere "delete[]"
    
    /* 🔍 il C++ alloca spazio per 5 int nell'heap e salva internamente la dimensione, 
    così che quando chiami delete[] arr, sappia quanti distruttori deve chiamare (se fossero oggetti complessi). */

    Punto *p = new Punto{3,4};
    std::cout << "Punto p = {" << p->x << "," << p->y << "}" << std::endl;
      
    
    return 0;
}