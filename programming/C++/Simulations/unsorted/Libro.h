#ifndef LIBRO_H
#define LIBRO_H

#include <iostream>
using namespace std;

class Libro
{
    private:
        string titolo;
        string autore;
        float prezzo;
        int codice;

        int assign_codice()
        {
            static int assignCode = 101;
            return assignCode++;
        }
    public:
        Libro(const string& title, const string& author, float price)
        : titolo(title), autore(author), prezzo(price), codice(assign_codice()) {} 
        Libro() : titolo(""), autore(""), prezzo(0.0), codice(-1) {}
        virtual ~Libro() {}
        const string& get_titolo() const { return titolo; }
        const string& get_autore() const { return autore; }
        float get_prezzo() const { return prezzo; }
        int get_codice() const { return codice; }
        
        void set_titolo(const string& newTitolo) { titolo = newTitolo; }
        //void set_autore(const string& newAutore) { autore = newAutore; }
        void set_prezzo(float newPrezzo) { prezzo = newPrezzo; }
        void set_codice() 
        { 
            if(codice == -1)
                codice = assign_codice();
            else cerr << "ERRORE: codice univoco gia' esistente." << endl;
        }

        friend ostream& operator<<(ostream&,const Libro&);
        virtual void stampa() const 
        {
            cout << *this;
        }
};

ostream& operator<<(ostream& os,const Libro& l)
{
    os << l.get_codice() << ": " << l.get_titolo() << " - " << l.get_autore() << " (" << l.get_prezzo() << ")";
    return os;
}

#endif