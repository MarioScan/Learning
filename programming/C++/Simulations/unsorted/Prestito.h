#ifndef PRESTITO_H
#define PRESTITO_H

#include <iostream>
using namespace std;

class Prestito
{
    private:
        string utente; //si presume nickname univoco
        int durata_giorni;
    public:
        Prestito() : utente(""), durata_giorni(0) {}
        Prestito(const string& user, int howManyDays) 
        : utente(user), durata_giorni(howManyDays) {}
        ~Prestito() {}
        
        const string& get_utente() const { return utente; }
        int get_durata_giorni() const { return durata_giorni;}

        void set_durata_giorni(int newDurata) { durata_giorni = newDurata; }

        friend ostream& operator<<(ostream&, const Prestito&);

        void stampa() const
        {
            cout << *this;
        }
};
ostream& operator<<(ostream& os, const Prestito& p)
{
    os << "[prestito a " << p.get_utente() << " per " << p.get_durata_giorni() << " giorni.]";
    return os;
}

#endif