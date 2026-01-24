#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
using namespace std;

class Persona
{
    private:
        string nome;
        string cognome;
        int anno; 
    public:
        Persona(const string& name, const string& surname, int year)
        : nome(name), cognome(surname), anno(year) {}
        Persona() : nome(""), cognome(""), anno(0) {}
        ~Persona() {}

        const string& get_nome() const { return nome;}
        const string& get_cognome() const { return cognome; }
        int get_anno() const { return anno; }

        void set_nome(const string& newName) { nome = newName; }
        void set_cognome(const string& newCognome) { cognome = newCognome; }
        void set_anno(int newAnno) { anno = newAnno; }

        friend ostream& operator<<(ostream&, const Persona&);
        virtual void stampa() const 
        {
            cout << *this;
        }
};

ostream& operator<<(ostream& os, const Persona& p)
{
    os << p.get_nome() << " " << p.get_cognome() << ", " << 2025-p.get_anno() << " anni"; 
    return os;
}

#endif