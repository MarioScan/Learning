/*

    Si voglia creare l'albero genealogico maschile a partire dal Bisnonno fino all'ultimo figlio. 

                                 Gianni Morandi
                               /                \ 
                            Giorgio             Marco  
                           /       \          /       \
                        Gnazio     Nino    Pancrazio   Luigitto
                      /      \                |        /     \ 
                 Francesco   Ciccio         Bilbo    Tobbi   Giuseppe

1) Crea albero
2) inserimento 
3) stampa albero
4) trova padre dato il nome del figlio
5) calcola altezza albero
6) stampa l'albero genealogico per anno di nascita
*/

#include <iostream>
#include "BTS.h"
#include "Persona.h"
using namespace std;

int main()
{
    /*
    Persona p("Mario",1930);
    cout << p << endl;
    p.print();
    cout << endl;*/

    //1)
    BTS<Persona*>* albero = new BTS<Persona*>();
    //2)
    albero
    ->insertRoot(new Persona("Gianni",1940))
    ->insertChild("Gianni", new Persona("Giorgio",1960))
    ->insertChild("Gianni", new Persona("Marco",1962))
    ->insertChild("Giorgio", new Persona("Gnazio",1982))
    ->insertChild("Giorgio", new Persona("Nino",1987))
    ->insertChild("Marco", new Persona("Pancrazio",1999))
    ->insertChild("Marco", new Persona("Luigitto",1998))
    ->insertChild("Gnazio", new Persona("Francesco",1999))
    ->insertChild("Gnazio", new Persona("Ciccio",2000))
    ->insertChild("Pancrazio", new Persona("Bilbo",2025))
    ->insertChild("Luigitto", new Persona("Tobbi",2005))
    ->insertChild("Luigitto", new Persona("Giuseppe",2003));

    //3)
    albero->print();

    //4)
    cout << "\n\nTrova padre:" << endl;
    albero->findFatherOf("Giuseppe");

    //5)
    cout << "\n\nAltezza dell'albero: " << albero->get_height() << endl;
    
    //6) 
    cout << "\n\nStampa albero genealogico per anno di nascita:" << endl; 
    albero->printPerYear();


    return 0;
}