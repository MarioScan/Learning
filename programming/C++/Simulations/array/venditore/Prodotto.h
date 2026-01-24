#ifndef PRODOTTO_H
#define PRODOTTO_H

/*
Classe Prodotto:
La classe deve rappresentare un generico prodotto e deve contenere:
-    un intero codice (identificativo del prodotto),
-    un double prezzo (in euro).

Metodi richiesti:
-    costruttore di default (imposta i dati a zero),
-    costruttore con parametri (codice, prezzo),
-    metodi get e set per codice e prezzo,
-    overloading dell’operatore << per stampare le informazioni del prodotto,
-    un metodo void leggi() per leggere i dati da input.

--- Sottoclassi di Prodotto: ---

1)  ProdottoAlimentare
        Attributo aggiuntivo: data di scadenza.
        Metodo bool verifica() → restituisce true se il prodotto non è scaduto, false altrimenti.

2)  ProdottoPerBambini
        Attributo aggiuntivo: fascia d’età (valori possibili: 0-3, 3-6, 6-9, 9-12).

        Suggerimenti:
-    La scadenza dei prodotti può essere gestita in modo semplice (anche come stringa o data fittizia).
-    È possibile organizzare venditori e prodotti in file di testo da leggere con il metodo leggi().
-    Per garantire codici univoci (sia per venditori che prodotti) è consigliato l’uso di variabili statiche.
*/

#include <iostream>
#include "Date.h" //libreria tempo
using namespace std;
class Prodotto
{
    private:
        int codice_prodotto; //deve essere univoco per ogni prodotto 
        double prezzo;

        int assign_code() 
        {
            static int code = 1001;
            return code++;
        }
    public:
        Prodotto() : codice_prodotto(-1), prezzo(-1.0) {}
        Prodotto(double price) : codice_prodotto(assign_code()), prezzo(price) {}
        virtual ~Prodotto() { cout << "[DEBUG]: Chiamato Distruttore Prodotto." << endl; }
        virtual Prodotto* clona() const { return new Prodotto(*this); } //deep copy -> rispetta Polimorfismo

        int get_codice() const { return codice_prodotto; }
        double get_prezzo() const { return prezzo; }

        //void set_codice(int newCode) { codice = newCode; }
        void set_prezzo(double newPrice) 
        { 
            if(codice_prodotto == -1) //caso inserimento prodotto dopo creazione per default.
                codice_prodotto = assign_code();
            prezzo = newPrice; 
        }

        friend ostream& operator<<(ostream&,const Prodotto&);
        virtual void print() const
        {
            cout << *this;
        }
};
ostream& operator<<(ostream& os,const Prodotto& p)
{
    os << p.get_codice() << " (€" << p.get_prezzo() << ")";
    return os;
}


class ProdottoAlimentare : public Prodotto     //private Prodotto //non intendo ereditare ProdottoAlimentare. --> invece si, perdo polimorfismo se faccio private
{
    private:
        int dataScadenza; //YYYY-MM-DD
    public:
        ProdottoAlimentare() : Prodotto(), dataScadenza(-1) {}
        ProdottoAlimentare(double price, int ExpiringDate) : Prodotto(price), dataScadenza(ExpiringDate) {}
        ~ProdottoAlimentare() { cout << "[DEBUG]: Chiamato Distruttore ProdottoAlimentare." << endl; }
        Prodotto* clona() const { return new ProdottoAlimentare(*this); }

        int get_dataScadenza() const { return dataScadenza; }
        void set_dataScadenza(int newExpiringDate) { dataScadenza = newExpiringDate; }

        bool verificaProdotto()
        {
            return dataScadenza >= get_current_date(); //si -> OK, no -> SCADUTO
        }

        void print() const override
        {
            Prodotto::print();
            cout << " - expire: " << dataScadenza; 
        }
};

enum class FasciaEta{ ZERO_TRE = 1, TRE_SEI, SEI_NOVE, NOVE_DODICI }; // 1 - 4

class ProdottoPerBambini : public Prodotto  
{   
    private:
        FasciaEta fascia;
    public:
        ProdottoPerBambini() : Prodotto(), fascia() {}
        ProdottoPerBambini(double price, FasciaEta f) : Prodotto(price), fascia(f) {}
        ~ProdottoPerBambini() { cout << "[DEBUG]: Chiamato Distruttore ProdottoPerBambini." << endl; }
        Prodotto* clona() const { return new ProdottoPerBambini(*this); }

        FasciaEta get_fascia() const { return fascia; } //ritorna valore 1 - 4
        void set_fascia(FasciaEta newFascia) { fascia = newFascia; }
        
        void print() const override
        {
            Prodotto:print();
            cout << " - fascia eta': ";
            switch(fascia)
            {
                case FasciaEta::ZERO_TRE:   cout << "0-3"; break;
                case FasciaEta::TRE_SEI: cout << "3-6"; break;
                case FasciaEta::SEI_NOVE: cout << "6-9"; break;
                case FasciaEta::NOVE_DODICI: cout << "9-12"; break;
                default:
                    cout << "ERRORE"; return; break;
            }
        }

};



#endif