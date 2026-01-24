/*
Classe Venditore
-    La classe deve contenere:
-    un intero codiceVenditore,
-    un array dinamico di Prodotto (l’elenco dei prodotti venduti),
-    un intero numProdotti (numero effettivo di prodotti).

Metodi richiesti:
-    costruttore di default (dati inizializzati a zero),
-    costruttore con parametro (solo il codice del venditore),
-    (opzionale) costruttore di copia,
-    overloading dell’operatore << per stampare codice venditore ed elenco prodotti,
-    double calcolaPrezzoTotale() → somma dei prezzi di tutti i prodotti,
-    double calcolaValoreMagazzino() → somma dei prezzi dei prodotti non scaduti,
-    void aggiungiProdotto(Prodotto*) → aggiunge un prodotto all’elenco (se c’è spazio),
-    void leggi() per leggere i dati del venditore da input.

⚠️ Nota: la classe Venditore utilizza la composizione, 
quindi all’interno dei suoi metodi deve sfruttare i metodi già definiti nella classe Prodotto.
*/

#ifndef VENDITORE_H
#define VENDITORE_H

#include <iostream>
#include "Prodotto.h"
using namespace std;

class Venditore
{
    private:
        int num_prodotti; //numero di prodotti nell' array
        int codice_venditore;
        Prodotto** array_prodottiVenduti;
        int capacita;

        int assign_vendor_code()
        {
            static int assignVendorCode = 1;
            return assignVendorCode++;
        }

        void moreSpace()
        {
            if(num_prodotti < capacita)
                return; //array non pieno.
        
            capacita *=2;
            Prodotto** temp = new Prodotto*[capacita];
            for(int i=0;i<capacita;i++)
                temp[i] = nullptr;
            for(int i=0; i<num_prodotti; i++)
                temp[i] = array_prodottiVenduti[i]; //passaggio puntatori all'array temp
            delete[] array_prodottiVenduti; //distruggo array di puntatori, non gli elementi puntati (quelli sono puntati adesso daa temp)!
           
            array_prodottiVenduti = temp;
            //delete[] temp; //non serve più
        }

        void inizializzaArray()
        {
            if(array_prodottiVenduti != nullptr)
                return; 

            capacita = 10;
            array_prodottiVenduti = new Prodotto*[capacita];
            for(int i=0;i<capacita;i++)
                array_prodottiVenduti[i] = nullptr;
        }

    public:
        Venditore() : num_prodotti(), codice_venditore(assign_vendor_code()), capacita(10), array_prodottiVenduti(nullptr) {}
    
        void clearArray()
        {
            for(int i=0; i< num_prodotti; i++)
                delete array_prodottiVenduti[i];
            delete[] array_prodottiVenduti;

            num_prodotti = capacita = 0;
        }
    
        ~Venditore()
        {
            cout << "Chiamato distruttore Venditore: ";
            clearArray();
            cout << "OK" << endl;
        }

        //getters
        int get_num_prodotti() const { return num_prodotti; }
        int get_codice_venditore() const { return codice_venditore; }
        int get_capacita() const { return capacita; }
        Prodotto** get_array_prodottiVenduti() const { return array_prodottiVenduti; } //prodotto* o nullptr

        bool isEmpty() const
        {
            return array_prodottiVenduti==nullptr;
        }
        //copia con operator==
        Venditore& operator=(const Venditore& other_vendor)
        {
            if(this == &other_vendor) //se puntatore venditore è uguale all'indirizzo di other_vendor allora è già stato passato
                return *this;

            if(!isEmpty())
                clearArray();
            
            //check OK -> inizializzo attributi
            this->num_prodotti = other_vendor.num_prodotti;  
            this->codice_venditore = assign_vendor_code();
            this->capacita = other_vendor.capacita;
            this->array_prodottiVenduti = new Prodotto*[capacita];
            
            //fill array
            for(int i=0; i<capacita; i++)
                array_prodottiVenduti[i] = nullptr; //mi assicuro di non uscire fuori 
            for(int i=0;i<num_prodotti;i++) //se ha buon fine (other_vendor.array_prodottiVenduti[i] != nullptr) usa funzione clona
                array_prodottiVenduti[i] = other_vendor.array_prodottiVenduti[i] ? other_vendor.array_prodottiVenduti[i]->clona() : nullptr;
            return *this;
        }

        friend ostream& operator<<(ostream&,const Venditore&);

        void print() const 
        {
            cout << *this << endl;
        }

        double calcolaPrezzoTotale() const; //somma totale
        double calcolaValoreMagazzino() const; //somma dei prezzi dei prodotti non scaduti
        void aggiungiProdotto(Prodotto*);
};

ostream& operator<<(ostream& os,const Venditore& v)
{
    os << "Venditore n." << v.get_codice_venditore() << " (" << v.get_num_prodotti() << ").";
    cout << "\n |-> Stampa prodotti:";
    for(int i=0; i < v.get_num_prodotti(); i++)
    {
        cout << " prod." << i << " " << v.get_array_prodottiVenduti()[i]->get_codice(); 
    }
    return os;
}

double Venditore::calcolaPrezzoTotale() const
{
    double totale=0;
    for(int i=0; i < num_prodotti; i++)
    {
        totale += array_prodottiVenduti[i]->get_prezzo(); 
    }
    return totale;
}

double Venditore::calcolaValoreMagazzino() const
{
    double totale=0;
    for(int i=0; i < num_prodotti; i++)
    {
        ProdottoAlimentare* prod_alim = dynamic_cast<ProdottoAlimentare*>(array_prodottiVenduti[i]);
        if(prod_alim && prod_alim->verificaProdotto())
            totale += array_prodottiVenduti[i]->get_prezzo();
        else if(!prod_alim)
            totale += array_prodottiVenduti[i]->get_prezzo();
    }
    return totale;
}

void Venditore::aggiungiProdotto(Prodotto* p)
{
    if(p == nullptr)
    {
        cerr << "errore: tentativo inserimento prodotto NULL nell'array." << endl;
        exit(1);
    }
    if(array_prodottiVenduti == nullptr) //array puntatori vuoto
        inizializzaArray();
    moreSpace(); //fa check in automatico
    array_prodottiVenduti[num_prodotti++] = p; //passa per puntatore
}


#endif