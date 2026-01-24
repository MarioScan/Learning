/*

    ------------------------------
    | Liste prodotti e venditori |
    ------------------------------

*/

#include <iostream>
using namespace std;

class Prodotto
{
    private:
        int codice_prodotto;
        double prezzo;
    public:
        Prodotto(int code, double price) : codice_prodotto(code), prezzo(price) {}
        Prodotto() : codice_prodotto(-1), prezzo(0.0) {}
        virtual ~Prodotto() {}
        int get_codice() const { return codice_prodotto; }
        double get_prezzo() const { return prezzo; } 
        void set_codice(int newCodice) { codice_prodotto = newCodice; }
        void set_prezzo(double newPrezzo) { prezzo = newPrezzo; }

        friend ostream& operator<<(ostream& os, const Prodotto& p);

        virtual void leggi()
        {
            cout << "Inserisci codice prodotto: "; cin >> this->codice_prodotto;
            cout << "Inserisci prezzo prodotto: "; cin >> this->prezzo;  
        }

        void stampa() const
        {
            cout << *this << endl;
        }
};
ostream& operator<<(ostream& os, const Prodotto& p)
{
    os << p.get_codice() << ": " << p.get_prezzo() << " euro." << endl;
    return os;
}

int currentDate() //simulo funzione di tempo
{
    return 20250709; // 09/07/2025 scritto nel formato yyyy/mm/dd per confronto semplice
}

class ProdottoAlimentare : public Prodotto
{
    private:
        int scadenza; 
    public:
        ProdottoAlimentare(int codice, double prezzo, int expiringDate) : Prodotto(codice,prezzo), scadenza(expiringDate) {}
        ~ProdottoAlimentare() {}

        int get_scadenza() const { return scadenza; }
        void set_scadenza(int newScadenza) { scadenza = newScadenza; }

        void leggi() override
        {
            Prodotto::leggi();
            cout << "Inserisci scadenza prodotto: "; cin >> scadenza; 
        }

        bool isExpired()
        {
            return scadenza < currentDate(); 
        }
};
enum FasciaEta
{
    FASCIA_0_3 = 0,
    FASCIA_3_6 = 3,
    FASCIA_6_9 = 6,
    FASCIA_9_12 = 9
};
class ProdottoPerBambini : public Prodotto
{
    private: 
        FasciaEta fascia_eta;
    public:
        ProdottoPerBambini(int code, double price, FasciaEta eta) : Prodotto(code, price), fascia_eta(eta) {}
        ProdottoPerBambini() : Prodotto(), fascia_eta(FASCIA_0_3) {}
        ~ProdottoPerBambini() {}

        const FasciaEta& get_fascia_eta() const { return fascia_eta; }
        void set_fascia_eta(FasciaEta newFascia) { fascia_eta = newFascia; }

        void leggi() override
        {
            Prodotto::leggi();
            cout << "Inserisci fascia eta' del prodotto, fascie disponibili: 0) Fascia 0-3 3) Fascia 3-6 6) Fascia 6-9 9) Fascia 9-12. Inserisci: "; 
            int scelta;
            cin >> scelta;
            fascia_eta = static_cast<FasciaEta>(scelta);
        }
};

class Venditore
{
    private:
        static int ultimoCodice;
        int code_venditore;
        Prodotto** prodotti;
        int numProdotti;
        int capacita;

        void addSpace()
        {
            capacita *= 2;
            Prodotto** nuovo = new Prodotto*[capacita];
            for(int i=0;i<numProdotti;i++)
            {
                nuovo[i] = prodotti[i];
            }
            delete[] prodotti;
            prodotti = nuovo;
        }

    public: 
        Venditore() : code_venditore(ultimoCodice++), prodotti(new Prodotto*[4]), numProdotti(0), capacita(4) {}
        ~Venditore() 
        { 
            for(int i=0;i<numProdotti;i++)
                delete *(prodotti+i);
            delete[] prodotti;
        }

        Venditore(const Venditore& v) : code_venditore(v.code_venditore), prodotti(nullptr), numProdotti(v.numProdotti), capacita(v.capacita)
        {
            prodotti = new Prodotto*[capacita];
            for(int i=0; i<numProdotti; i++)
            {
                prodotti[i] = new Prodotto(*v.prodotti[i]);
            }
        }

        int get_code_venditore() const { return code_venditore; }

        friend ostream& operator<<(ostream& os, const Venditore& v);
        
        double calcolaPrezzoTotale() const
        {
            double somma=0.0;
            for(int i=0;i<numProdotti;i++)
            {
                somma+= prodotti[i]->get_prezzo();
            }
            return somma;
        }

        double calcolaValoreMagazzino() const
        {
            double somma = calcolaPrezzoTotale();
            
            for(int i=0;i<numProdotti;i++)
            {   
                ProdottoAlimentare* pa = dynamic_cast<ProdottoAlimentare*>(prodotti[i]);
                if(pa != nullptr && pa->isExpired() == true)
                {
                    somma -= pa->get_prezzo();
                }
            }
            return somma;
        }

        void aggiungiProdotto(Prodotto* p)
        {
            if(numProdotti == capacita)
                this->addSpace();
            prodotti[numProdotti++] = p;
        }

        void leggi()
        {
            cout << "Inserisci codice venditore: "; 
            cin >> code_venditore;
        }


};
int Venditore::ultimoCodice = 1001; //inizializzazione variabile static

ostream& operator<<(ostream& os, const Venditore& v)
{
    os << "Codice venditore: " << v.get_code_venditore() << "\nProdotti:" << endl;

    for(int i=0;i<v.numProdotti;i++)
    {
        os << *(v.prodotti[i]);
    }

    return os;
}



int main()
{
    Venditore v1;
    Venditore v2;
    Venditore v3;
    Venditore v4;

    v1.aggiungiProdotto(new Prodotto(10, 10.50));
    v1.aggiungiProdotto(new ProdottoAlimentare(102, 5.30, 20260101)); // buono
    v1.aggiungiProdotto(new ProdottoAlimentare(103, 6.90, 20240101)); // scaduto
    v1.aggiungiProdotto(new ProdottoPerBambini(104, 12.99, FASCIA_0_3));
    v1.aggiungiProdotto(new ProdottoPerBambini(105, 8.75, FASCIA_3_6));

    // -------- Venditore 2 --------
    v2.aggiungiProdotto(new Prodotto(201, 20.00));
    v2.aggiungiProdotto(new ProdottoAlimentare(202, 3.50, 20250801)); // buono
    v2.aggiungiProdotto(new ProdottoAlimentare(203, 4.20, 20230101)); // scaduto
    v2.aggiungiProdotto(new ProdottoPerBambini(204, 15.60, FASCIA_6_9));
    v2.aggiungiProdotto(new Prodotto(205, 7.40));

    // -------- Venditore 3 --------
    v3.aggiungiProdotto(new ProdottoAlimentare(301, 6.60, 20241212)); // scaduto
    v3.aggiungiProdotto(new Prodotto(302, 11.00));
    v3.aggiungiProdotto(new ProdottoPerBambini(303, 9.99, FASCIA_9_12));
    v3.aggiungiProdotto(new ProdottoPerBambini(304, 14.70, FASCIA_0_3));
    v3.aggiungiProdotto(new Prodotto(305, 5.55));

    //stampa
    cout << v1 << endl;
    cout << "Prezzo totale: " << v1.calcolaPrezzoTotale() << " euro." << endl;
    cout << "Valore magazzino: " << v1.calcolaValoreMagazzino() << " euro.\n" << endl;

     cout << v2 << endl;
    cout << "Prezzo totale: " << v2.calcolaPrezzoTotale() << " euro" << endl;
    cout << "Valore magazzino: " << v2.calcolaValoreMagazzino() << " euro\n" << endl;

    cout << v3 << endl;
    cout << "Prezzo totale: " << v3.calcolaPrezzoTotale() << " euro" << endl;
    cout << "Valore magazzino: " << v3.calcolaValoreMagazzino() << " euro\n" << endl;


    return 0;
}

