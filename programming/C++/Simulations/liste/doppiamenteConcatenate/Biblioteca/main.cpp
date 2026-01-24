#include <iostream>
#include "Libro.h"
#include "LibroPrestato.h"
#include "Lista.h"
using namespace std;

int main()
{
    Libro* l1 = new Libro("Willy Wonka","Billy Bob",1940);

    Lista<Libro*>* lista = new Lista<Libro*>(10);
    lista
    ->insert(new Libro("The Witcher", "Andrej Sapkowski", 1987))
    ->insert(new Libro("Lord of the Rings","Biblo Beggings",1978))
    ->insert(new LibroPrestato("Game of Thrones", "Jon Snow", 1967, new Prestito(50, "John Hilbert")))
    //->insert(new LibroPrestato(l1, new Prestito(60, "Edric Snow")))
    ->insert(new LibroPrestato("Willy Wonka", "Billy Bob", 1940, new Prestito(60, "Edric Sand")))
    ->insert(new LibroPrestato("La fiaba delle sirene", "Kat Anders",1934, new Prestito(50, "Willy White")))
    ->insert(new LibroPrestato("Colosseum's life", "Aedreus",49, new Prestito(120,"Will Smith")))
    ;
    lista->stampa();
    lista->removeBefore(1940);
    cout << endl;
    lista->stampa();
    cout << "Durata complessiva libri in prestito: " << lista->get_durata_totale_prestiti() << endl;
    
    cout << "Evviva" << endl;
    return 0;
}