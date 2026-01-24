
//Puntatori e riferimenti


#include <iostream>
using namespace std;

int somma(int,int);
int messaggio();

int somma(int a, int b) 
{ 
    return a + b; 
}

int messaggio()
{
    cout << "Questo messaggio e' stato stampato da una chiamata a funzione tramite puntatore!" << endl;
    return 1;
}


struct Punto{
    int x,y; 
};

int main()
{
    int es = 0;
    //Applicazione e verifica esistenza puntatore
    cout << "<-><-><-><-><-><-><-><-><-><-> INIZIO <-><-><-><-><-><-><-><-><-><->" << "\n                                (" << ++es << ")" << endl;
    int x = 5;
    int *ptr = &x; 
    cout << "Valore di x: " << x << "\nValore puntato da ptr: " << *ptr << "\nIndirizzo di memoria di x: " << &x << "\nIndirizzo di memoria di ptr: " << ptr << "\n\nControlliamo se sono uguali con un if:" << endl;

    if(ptr == &x) 
        cout << "ptr e' un puntatore a x --> " << "(ptr) = " << ptr << " = (x) = " << &x << endl;
    else cout << "ptr non e' un puntatore a x --> " << "(ptr) = " << ptr << " != (x) = " << &x << endl; 
    
    //Modifica valore attraverso puntatore 
    cout << "<-><-><-><-><-><-><-><-><-><->" << "  (" << ++es << ")  " << "<-><-><-><-><-><-><-><-><->" << endl;
    cout << "Cambiamo il valore di x usando il puntatore: x = " << x << endl;
    *ptr = x+2; 
    cout << "Adesso x vale: " << x << endl;
    
    //Modifica per riferimento
    cout << "<-><-><-><-><-><-><-><-><-><->" << "  (" << ++es << ")  " << "<-><-><-><-><-><-><-><-><->" << endl;
    cout << "--- Modifica per riferimento --- " << endl;
    cout << "Modifichiamo per riferimento adesso: " << endl;
    int& ref = x; 
    //ref non è una nuova variabile, ma semplicemente un altro nome per x: per questo bisogna sempre inizializzare subito una variabile ref (reference)
    ref = x*2;
    cout << "Adesso x vale: " << x << endl;

    //Array e puntatori 
    cout << "<-><-><-><-><-><-><-><-><-><->" << "  (" << ++es << ")  " << "<-><-><-><-><-><-><-><-><->" << endl;

    cout << "--- Array e Puntatori --- " << endl;

    int v[] = {1,2,3};
    int *p = v; //Punta all'inizio dello array v --> vediamo

    cout << "Array v: ";
    for(int i=0;i< (sizeof(v) / sizeof(*p)); i++) // sizeof(v[0]) o sizeof(*p) è la stessa cosa perché *p indica proprio v[0] ...
    {
        cout << *(p+i);
    }
    cout << endl;
    
    //Puntatori a funzioni
    cout << "<-><-><-><-><-><-><-><-><-><->" << "  (" << ++es << ")  " << "<-><-><-><-><-><-><-><-><->" << endl;
    cout << "--- Puntatori a funzioni --- " << "\nUtilizzo un puntatore che prende tra parentesi due interi e utilizza la funzione somma." << endl;
    
    int (*ptr1)(int,int) = somma;
    cout << "Somma di 3 + 4 utilizzando puntatore a funzione: " << ptr1(3,4) << endl;

    cout << "Altro esempio:" << endl;

    int (*ptr2)() = messaggio;
    ptr2();

    //Puntatori a strutture
    cout << "<-><-><-><-><-><-><-><-><-><->" << "  (" << ++es << ")  " << "<-><-><-><-><-><-><-><-><->" << endl;
    cout << "--- Puntatori a strutture --- " << endl;

    //...creazione struct sopra...

    Punto p1 = {1,2}; //stampa con p1.x --> in quanto accesso tramite oggetto 
    Punto *ptr3 = &p1; //stampa con ptr3->x --> in quanto accesso tramite puntatore a oggetto
    cout << "Ho creato il punto p1 = {" << p1.x << "," << p1.y << "}\n" << "Stampa del punto creato tramite un puntatore di tipo (struct) Punto -->\nX = " << ptr3->x << "\nY = " << ptr3->y << endl;

    cout << "\n<-><-><-><-><-><-><-><-><-><-> FINE <-><-><-><-><-><-><-><-><-><->" << endl;
    return 0;
}