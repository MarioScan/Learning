

/*
    ---------------------
    |     TEMPLATES     | -->  Templates e codice generico 
    --------------------- 

🎯 Perché esistono?
I template permettono di scrivere codice generico, riutilizzabile con qualsiasi tipo.

(1) 📌 Funzioni template
💡 Permettono una facile scrittura generica, riutilizzabile e una forte alternativa alla 
tecnica del sovraccaricamento delle funzioni (2) <---
            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

(3) 🧱 Classi template

Box<int> b1(5);
Box<string> b2("Mario");

👑 Vantaggi
    <-> Riduce codice duplicato
    <-> Potente con vector, map, list
    <-> Ottimo per scrivere strutture dati personalizzate
*/

#include <iostream>
using namespace std;

//(1) -> Templates 
template <typename T>
T massimo(T a, T b) 
{
    return (a > b) ? a : b;
}

//(2) -> Sovraccarico di una funzione 
int somma(int a, int b);
double somma(double a, double b);
string somma(string a, string b);


//(3) -> Classi template 
template <typename T>
class Box 
{
    private: //Ogni membro di classe è default se non specificato altrimenti, quindi potrei anche omettere questa private e verrebbe comunque considerato come tale
        T valore;
    public:
        Box(T v) : valore(v) {}
        void stampa() const { cout << "Contenuto: " << valore << endl; }

        const T& getValore() const { return valore; }
        void setValore(const T& newValue) { valore = newValue; }
};

int main()
{
    //1 --> Usiamo le nostre funzioni template con qualsiasi tipo 
    int x = massimo(3, 7);        // int
    cout << "Massimo tra due interi: " << x << endl;

    double y = massimo(3.5, 2.1); // double
    cout << "Massimo tra due double: " << y << endl;

    string z = massimo("Ciao","Mondo!"); //quale stringa è maggiore 
    cout << "Massimo tra due stringhe: " << z << endl;

    //2 --> Vediamo come una funzione sovraccaricata è del tutto sostituibile da un Template
    //nulla da aggiungere.

    //3 --> Proviamo la nostra Classe template:
    Box<int> b1(42);  
    b1.stampa();
    Box<int>* b2 = new Box<int>(50);
    b2->stampa();
    delete b2;

    return 0;
}


/* Tutti i modi per inizializzare una class template (per esempio di interi):

    -------------------------------------------------------------------------------------------------------------------
    |  Forma	                       |  Sintassi esempio	               |    Note                                  |
    -------------------------------------------------------------------------------------------------------------------
    |  Classica                        |  Box<int> b(10);	               |  Standard                                |
    |  Uniform initialization (C++11+) |  Box<int> b{10};                  |  Più sicura, evita conversioni implicite |
    |  Copia implicita / assegnazione  |  Box<int> b = Box<int>(10);       |  Usata spesso con ritorni da funzione    |
    |  auto                            |  auto b = Box<int>(10);           |  Comodo, ma devi scrivere Box<int>(...)  |
    |  Puntatore dinamico	           |  Box<int>* b = new Box<int>(10);  |  Ricordati delete                        |
    -------------------------------------------------------------------------------------------------------------------


*/