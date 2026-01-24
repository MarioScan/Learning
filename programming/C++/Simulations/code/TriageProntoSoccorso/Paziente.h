#ifndef PAZIENTE_H
#define PAZIENTE_H

#include <iostream>
#include "Persona.h"
using namespace std;

enum class codicePriorita {R=0,G,V}; //Rosso Giallo Verde
ostream& operator<<(ostream&, const codicePriorita);

class Paziente : public Persona //nome cognome anno
{
    private:
        int id;
        codicePriorita codice;
        int attesa; //in minuti

        int assign_id()
        {
            static int id_dispenser = 100;
            return ++id_dispenser; 
        }

    public:
        Paziente() : Persona(), id(-1), codice(), attesa(-1) {}
        Paziente(const string& nome, const string& cognome, int anno, codicePriorita code, int waitingTime) 
        : Persona(nome,cognome,anno), codice(code), attesa(waitingTime), id(assign_id()) {}
        ~Paziente() {}

        int get_id() const { return id; }
        codicePriorita get_codice() const { return codice; }
        int get_attesa() const { return attesa; }

        void set_id() { if(id==-1) id = assign_id(); else cout << "ID gia' esistente." << endl; }
        void set_codice(codicePriorita newCode) { codice = newCode; }
        void set_attesa(int newTempoAttesa) { attesa = newTempoAttesa; }

        //friend ostream& operator<<(ostream&, const codicePriorita); //non è membro classe
        friend ostream& operator<<(ostream&, const Paziente&);
        
        void stampa() const override 
        {
            //cout << *this; //output: Rosso: id: 101, attesa: 10 min - Gianni U beddu, 97anni.
            cout << id << ": ";
            Persona::stampa();
            cout << " - [" << codice << "] - attesa: " << attesa << " minuti.";
        }
};
ostream& operator<<(ostream& os, const codicePriorita c)
{   
    switch(c)
    {
        case codicePriorita::R : 
            os << "Rosso"; break;
        case codicePriorita::G :
            os << "Giallo"; break;
        case codicePriorita::V : 
            os << "Verde"; break;
        default:
            os << "ERRORE"; break;
    }
    return os;
}
ostream& operator<<(ostream& os, const Paziente& p)
{
    os << p.get_codice() << ": id: " << p.get_id() << ", attesa: " << p.get_attesa() << " min - ";
    os << static_cast<const Persona&>(p);
    return os; 
}

#endif