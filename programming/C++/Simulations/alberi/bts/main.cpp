#include <iostream>
#include "Studente.h"
#include "bts.h"
using namespace std;

int main() 
{   /*
    Studente s1;
    cout << "Inserisci dati studente: MATRICOLA NOME COGNOME MEDIA:" << endl;
    cin >> s1; 
    cout << s1;
    Studente* s2 = &s1;
    BTS<Studente*> a;
    a.insert(new Studente(1004,"Mario","Rossi",24.5)); 
    a.insert(s2);
    a.stampa();*/

    BTS<Studente*> a;
    cout << "Benvenuto, caricamento Studenti dal file..." << endl;
    string fileIn = "input.txt";
    a.loadFromFile(fileIn);
    a.stampa();
    a.removeNode(25);
    a.stampa();
    cout << "\nAltezza albero: " << a.get_altezza() << endl;
    a.searchMatricola(1004);
    cout << "\nEvviva!" << endl;
    return 0;
}