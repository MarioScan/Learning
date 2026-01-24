#include <iostream>
#include "Persona.h"
#include "Paziente.h"
#include "Coda.h"
using namespace std;

int main()
{
   //const string& nome, const string& cognome, int anno, codicePriorita code, int waitingTime
    Coda<Paziente*>* paz = new Coda<Paziente*>();
    paz
    ->enqueue(new Paziente("Gianni", "U beddu", 1970, codicePriorita::V, 30))
    ->enqueue(new Paziente("Anna", "Rappa", 1999, codicePriorita::G, 20))
    ->enqueue(new Paziente("Luigi", "Bros", 1933, codicePriorita::R, 10))
    ->enqueue(new Paziente("A nanna", "bedda", 1945, codicePriorita::R, 20))
    ->enqueue(new Paziente("Nino", "Blu", 2020, codicePriorita::R, 30))
    ->enqueue(new Paziente("Giggio","Pasticcio",1984, codicePriorita::V, 35));

    return 0;
}