#include <iostream>
#include "Persona.h"
#include "bst.h"
using namespace std;

int main() 
{
    Studente s1(1004,"Mario","Rossi",24.5);
    Docente d1(10043, "Giallo", "Gallo", "Prog2");

    /*s1.print();
    cout << endl;
    d1.print();
    cout << endl;*/

    BST<Persona*>* bst = new BST<Persona*>();
    
    /*bst
    ->insert(new Studente(1004,"Mario","Rossi",24.5)) //passare insert(&s1) funziona ma non posso fare delete nodo->get_dato() nella erase o causa crash!
    ->insert(new Docente(10043, "Giallo", "Gallo", "Prog2"));
    */

    string nomeFile = "input.txt";
    bst->insertFromFile(nomeFile);

    bst->printAll();
    bst->removePerMatricola(1004);
    bst->printAll();

    cout << "Evviva" << endl;
    return 0;
}