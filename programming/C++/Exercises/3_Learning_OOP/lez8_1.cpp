/*

    -----------------------
    |       Classi        |
    ----------------------- 

(3) 🔨 Costruttori & Distruttori

<-> Costruttore: inizializza l'oggetto

<->Distruttore: rilascia risorse quando l'oggetto viene distrutto

Creiamo un altro file per mostrare meglio questo meccanismo, usando come base l'esempio di programma di prima (lez_8.cpp):

*/


#include <iostream>
using namespace std;

class Persona
{
    private: 
        string nome;
        int eta;

    public:
        //Costruttore parametrico --> ci permette di costruire direttamente la nostra istanza in una sola procedura:
        //--> es. Persona p1("Mario",21);
        //Persona(string newNome, int newAge) { nome = newNome; eta = newAge; } //funziona ma è meglio fare:

        //Lista di inizializzazione del costruttore (constructor initializer list):
        Persona(string newNome, int newAge) : nome(newNome), eta(newAge) {} 
        /* Questo modo permette di inizializzare le variabili prima ancora di entrare nel costruttore:
        <-> È più efficiente (meno assegnazioni inutili).

        <-> È obbligatoria per membri const o riferimenti (&), perché quelli devono essere inizializzati alla creazione.
        */


        //Costruttore di default --> Se non inserisco nulla come parametro durante la creazione della instanza inserisce di default dei valori:
        Persona() { nome = "Sconosciuto", eta = -1; }

        //Distruttore --> si indica con  " ~ " davanti al nome e indica distruttore --> serve a liberare la memoria dalle risorse usate
        ~Persona() 
        { 
            /* specifico la delete solo nel caso in cui ho dei puntatori, 
                es. se avessi avuto negli attributi "int* data", qui farei una "delete[] data", 
            il distruttore farà il resto... */
            cout << "Chiamato distruttore... Memoria liberata da instanza con successo." << endl; 
            //nota: istanza e oggetto sono praticamente sinonimi.
        }
        /* Il compilatore esegue automaticamente il distruttore, se non ne viene definito uno, 
        lo crea automaticamente eleminando tuttavia solo variabili NON-pointers  */

        //setters
        void setNome(string newName) { nome = newName; }
        void setEta(int newAge) { eta = newAge; } 
      
        //getters
        string getNome() const { return nome; }
        int getEta() const { return eta; }

        //mia funzione di stampa
        void stampa() //metodo membro della classe
        {
            cout << "Informazioni persona:\nNome: " << getNome() << "\nEta: " << getEta() << endl;
            /* Si può anche usare this e scriverlo esplicitamente come:
                cout << "Informazioni persona:\nNome: " << this->getNome() << "\nEta: " << this->getEta() << endl;            
                ma il compilatore lo fa in automatico quindi non necessario,
                troveremo usi per this per passare l'oggetto ad un'altra funzione:
                --> es. altraFunzione(this); 
                o per scelte del programmatore, per aiutare la leggibilità etc.     
            */
        }
};

void print(const Persona& p) //metodo (funzione)  esterna alla classe
{
    cout << "Informazioni persona:\nNome: " << p.getNome() << "\nEta: " << p.getEta() << endl;
}

int main()
{
    //Bene, applichiamo queste nuove nozioni:

    Persona p1("Mario",21);
    p1.stampa();

    Persona p2;
    print(p2); 
    //due modi per usare funzione su elementi della classe

    //il distruttore ~Persona() viene richiamato automaticamente dal compilatore: è una buona norma non richiamarlo:
    // ❌ scrivere p1.~Persona(); darebbe comportamente INDEFINITO del compilatore ❌ 
    //il come farlo manualmente  non ci interessa per il momento e forse mai.

    return 0;
}

