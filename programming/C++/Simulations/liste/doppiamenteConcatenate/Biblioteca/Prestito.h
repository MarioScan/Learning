#ifndef PRESTITO_H
#define PRESTITO_H

#include <iostream>
using namespace std;

class Prestito
{
    private:
        int durata; //giorni
        string nome_studente;
    public:
        Prestito() : durata(0), nome_studente("") {}
        Prestito(int time, const string& studentName) : durata(time), nome_studente(studentName) {}
        ~Prestito() {}

        int get_durata() const { return durata; }
        const string& get_nome_studente() const { return nome_studente; }

        void set_durata(int newTime) { durata = newTime; }
        void set_nome_studente(const string& newStudName) { nome_studente = newStudName; }

        friend ostream& operator<<(ostream&, const Prestito&);
        void stampa() const 
        {
            cout << *this;
        }
};

ostream& operator<< (ostream& os, const Prestito& p)
{
    os << p.get_nome_studente() << " - " << p.get_durata() << " giorni.";
    return os;
}

#endif