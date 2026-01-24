/*

 Pila 🏯🛡️
PROVA D’ESAME – Programmazione 2
Si consideri una classe Guerriero che rappresenta un combattente medievale.
Attributi privati:
    nome (stringa)
    clan (stringa)
    forza (double): punteggio di forza

Metodi pubblici:
    - costruttore
    - get degli attributi
    - stampa(): codice: nome del clan - forza punti

Si consideri una classe Arma che rappresenta un’arma speciale.
    - Attributi privati e relativi get/set:
    - danno (int)
    - tipo (stringa)

Si consideri una classe GuerrieroArmato derivata da Guerriero con attributo:
    - arma: puntatore a Arma
Metodi pubblici:
    - get_danno_arma()
    - stampa():
        con arma: nome: nome del clan - forza punti [arma: tipo, danno: X]
        senza arma: codice: nome del clan - forza punti

Si implementi la Pila (lista concatenata) per gestire i guerrieri.
Il programma deve:

1) Leggere i dati da guerrieri.txt nel formato:
        codice nome clan forza danno tipo
2) Se danno = 0, il guerriero non ha arma.
3) Inserire i guerrieri nella pila.
4) Rimuovere tutti quelli con forza < 60 e stampare:
    Guerriero rimosso: Nome del Clan - Codice: ...

5) Stampare il contenuto della pila.
6) Calcolare il totale del danno delle armi possedute dai guerrieri rimasti.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Guerriero
{
    private:
        string nome;
        string clan;
        double forza;
    public:
        Guerriero(const string& name, const string& faction, double strength) : nome(name), clan(faction), forza(strength) {}
        ~Guerriero() {}
        
        const string& get_nome() const { return nome; }
        const string& get_clan() const { return clan; }
        double get_forza() const { return forza; }

        void set_nome(const string& newNome) {  nome = newNome; }
        void set_clan(const string& newClan) { clan = newClan; }
        void set_forza(double newForza) { forza = newForza; }

        friend ostream& operator<<(ostream&, const Guerriero&);
        virtual void stampa() const 
        {
            cout << *this;
        }
};

ostream& operator<<(ostream& os, const Guerriero& g)
{
    os << g.get_nome() << ", clan: " << g.get_clan() << " - " << g.get_forza();
    return os;
}

class ArmaSpeciale
{
    private:
        string tipo;
        double danno;
    public:
        ArmaSpeciale(const string& type, double dmg = 0.0) : tipo(type), danno(dmg) {}
        ~ArmaSpeciale() {}

        const string& get_tipo() const { return tipo; }
        double get_danno() const { return danno; }

        void set_tipo(const string& newTipo) { tipo = newTipo; }
        void set_danno(double newDanno) { danno = newDanno; }

        void stampa() const 
        {
            cout << " [" << tipo << ", " << danno << "]"; 
        }
};

class GuerrieroArmato : public Guerriero
{
    private:
        ArmaSpeciale* arma;
    public:
        GuerrieroArmato(const string& name, const string& faction, double strength, ArmaSpeciale* weapon) : Guerriero(name,faction,strength), arma(weapon) {}
        GuerrieroArmato(const string& name, const string& faction, double strength) : Guerriero(name,faction,strength), arma(nullptr) {}

        ~GuerrieroArmato() 
        { 
            if(arma) 
                delete arma;
        }

        double get_danno_arma() const { return arma ? arma->get_danno() : 0.0; } //return if(arma) -> arma->get_danno(); else 0.0;

        void stampa() const override
        {
            Guerriero::stampa();
            if(arma)
                arma->stampa();
        } 
};

template <typename T>
class Nodo
{
    private:
        T dato;
        Nodo<T>* next;
    public:
        Nodo(const T& data) : dato(data), next(nullptr) {}
        ~Nodo() { cout << "[DEBUG]: Chiamato distruttore Nodo." << endl; }

        const T& get_dato() const { return dato; }
        Nodo<T>* get_next() const { return next; }

        void set_next(Nodo<T>* new_next) { next = new_next; }
};

template <typename T>
class Pila
{
    private:
        Nodo<T>* top;
    public:
        Pila() : top(nullptr) {}

        bool isEmpty() const
        {
            return top==nullptr;
        }

        void push(const T& nuovoDato)
        {
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(!nuovo)
            {
                cerr << "Errore: impossibile creare nuovo nodo Lista." << endl;
                exit(1);
            }

            if(isEmpty())
            {
                top = nuovo;
                return;
            }

            nuovo->set_next(top);
            top = nuovo;
        }

        void pop()
        {
            if(isEmpty())
            {
                cout << "/!\\ Pila vuota /!\\" << endl;
                return;
            }

            Nodo<T>* temp = top;
            delete temp->get_dato();
            top = top->get_next();
            delete temp;
        }

        bool readFile(const string& nomeFile)
        {
            ifstream FileIn(nomeFile);
            if(!FileIn)
            {
                cerr << "Errore: impossibile aprire il file: \"" << nomeFile << "\" per la lettura." << endl;
                return false;
            }

            string buffer;
            while(getline(FileIn, buffer))
            {
                //creo variabili per leggere input che sappiamo del formato: nome clan forza danno tipo (se danno=0 non ha arma)
                istringstream iss(buffer);
                string nome, clan, tipo;
                double forza;
                double danno = 0.0;

                iss >> nome >> clan >> forza;

                // Provo a leggere arma e danno
                if(iss >> tipo >> danno)
                {
                    // C'è Arma speciale
                    ArmaSpeciale* arma = new ArmaSpeciale(tipo, danno);
                    GuerrieroArmato* g = new GuerrieroArmato(nome, clan, forza, arma);
                    push(g);
                }
                else
                {
                    // Nessuna arma
                    Guerriero* g = new Guerriero(nome, clan, forza);
                    push(g);
                }
            }

            FileIn.close();
            return true; //read riuscita
        }

        void stampa() const 
        {
            if(isEmpty())
            {
                cout << "/!\\ Pila vuota /!\\" << endl;
                return;
            }

            Nodo<T>* current = top;
            while(current)
            {
                current->get_dato()->stampa();
                cout << endl;
                current = current->get_next();
            }
        }

        void removeUnderscore(double key)
        {
            Nodo<T>* current = top;
            while(current)
            {
                if(current->get_dato()->get_forza() < key)
                {
                    cout << "Rimosso guerriero: ";
                    current->get_dato()->stampa();
                    cout << endl;
                }
                current = current->get_next();
            }
        }

        double totalDamage()
        {
            double total=0.0;
                        Nodo<T>* current = top;
            while(current)
            {
                GuerrieroArmato* weaponizedWarrior = dynamic_cast<GuerrieroArmato*>(current->get_dato());
                if(weaponizedWarrior)
                {
                    total += weaponizedWarrior->get_danno_arma();
                }
                current = current->get_next();
            }
            return total;
        }

        ~Pila() 
        { 
            cout << "[DEBUG]: Chiamato distruttore Pila." << endl; 
            while(!isEmpty())
                pop();
        }
};


int main()
{
    const string nome_file = "ClanDiGuerrieri.txt";
    
    Pila<Guerriero*>* guerrieri = new Pila<Guerriero*>();
    guerrieri->readFile(nome_file);
    guerrieri->stampa();
    cout << endl;
    guerrieri->removeUnderscore(70.0);
    cout << endl;
    cout << "Danno totale armi dei guerrieri rimanenti: " << guerrieri->totalDamage() << endl;

    return 0;
}

