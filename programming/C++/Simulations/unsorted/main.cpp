#include <iostream>
#include "Libro.h"
#include "Prestito.h"
#include "LibroPrestato.h"
#include "Pila.h"
using namespace std;

int main()
{
    /* //check
    Libro l("C++ Avanzato","Mario Rossi",29.99);
    l.stampa();

    Prestito p("Anna",10);
    p.stampa();
    
    cout << endl;
    LibroPrestato lp("C++ Avanzato","Mario Rossi",29.99, new Prestito("Anna",10));
    lp.stampa();

    Nodo<LibroPrestato*> lp = new LibroPrestato("C++ Avanzato","Mario Rossi",29.99, new Prestito("Anna",10));
    lp.get_dato()->stampa();

    Nodo<LibroPrestato*>* lp = new Nodo<LibroPrestato*>( new LibroPrestato("C++ Avanzato","Mario Rossi",29.99, new Prestito("Anna",10)));
    lp->get_dato()->stampa();
    */

    //Inserimento di 8 elementi nella pila
    Pila<Libro*>* miaPila = new Pila<Libro*>(); //attivo polimorfismo
    miaPila
    ->push(new Libro("C++ Avanzato","Mario Rossi",29.99))
    ->push(new LibroPrestato("Python per tutti","Luigi Verdi", 19.98, new Prestito("Anna",10)))
    ->push(new Libro("Algoritmi","Marta Bianchi",14.99))
    ->push(new Libro("Database","Marco Neri",34.49))
    ->push(new LibroPrestato("Arte della Guerra", "Sun Tzu",14.99,new Prestito("Zaeraeth",60)))
    ->push(new LibroPrestato("Sistemi Operativi","Emma Marroni",29.99, new Prestito("Lara Croft",200)))
    ->push(new Libro("The Witcher","Andrej Sapkowski",14.99))
    ->push(new LibroPrestato("La verita' e' menzogna","Re Nicomario",19.99, new Prestito("Mario203",70)))
    ;
    miaPila->stampa();

    miaPila->removeUnderPrice(19);

    cout << "Totale giorni libri in prestito: " << miaPila->durataComplessivaPrestiti() << endl;

    miaPila->mostraLibriPrestati(); 

    //miaPila = miaPila->ribaltaPila(); //extra, ma non funziona 

    return 0;
}
