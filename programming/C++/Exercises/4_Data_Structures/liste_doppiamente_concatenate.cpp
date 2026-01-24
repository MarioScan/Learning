/*
    ---------------------------------------
    |    LISTA DOPPIAMENTE CONCATENATA    | 
    ---------------------------------------

    🎯 Ogni nodo punta sia al successivo (next) che al precedente (prev)
    

    Creiamo i soliti elementi:
    
    1. Struttura Nodo con prev e next
    2. Costruttore e distruttore
    3. Funzione di Inserimento:
        in testa (inserisciInTesta)
        in coda (inserisciInCoda)
        ordinato (inserisciOrdinato)
    4. Rimozione:
        in testa (rimuoviInTesta)
        in coda (rimuoviInCoda)
        per valore (rimuoviTutti)
    5. Ricerca (cerca)
    6. Stampa:
        in avanti (stampa)
        all’indietro (stampaInversa)
    7. Distruzione completa della lista
    8. Protezione da memory leak    
*/

#include <iostream>
using namespace std;
//(1)
class Nodo
{
    public:
        int value;
        Nodo* next;
        Nodo* prev;

        Nodo(int valore) : value(valore) {}
};

class Lista
{
    private:
        Nodo* head;
        Nodo* tail;
    public:
        Lista() : head(nullptr), tail(nullptr) {}

        //(2) Distruttore di Lista
        ~Lista() 
        {
            cout << "Chiamato distruttore di Lista." << endl;
            while(head != nullptr)
            {
                Nodo* temp = head;
                head = head->next;
                delete temp;
            }
        }


        //(3) Funzione di inserimento:

        void push_head(const int& value)
        {
            Nodo* nuovo = new Nodo(value);
            nuovo->next = head;
            
            if(head != nullptr)
                head->prev = nuovo;
            else tail = nuovo; //primo nodo della lista 
            
            head = nuovo;
        }

        void push_tail(const int& value)
        {
            Nodo* nuovo = new Nodo(value);
            nuovo->prev = tail;
            if(tail != nullptr)
                tail->next = nuovo;
            else head = nuovo; //primo nodo della lista

            tail = nuovo;
        }

        void pushInOrder(const int& value)
        {
            //primo valore o valore più piccolo
            if(head == nullptr || value < head->value)
            {
                push_head(value);
                return;
            }

            //scorrimento per trovare il posto al nuovo nodo
            Nodo* current = head;
            while(current->next != nullptr && current->next->value < value)
            {
                current = current->next;
            }

            //dunque adesso creiamo e inseriamo il nodo nella posizione indicata da current
            Nodo* nuovo = new Nodo(value);
            nuovo->next = current->next;
            nuovo->prev = current; //nuovo si inserisce in mezzo a current e al successivo di esso

            if(current->next != nullptr)
                current->next->prev = nuovo;
            else tail = nuovo; //ho raggiunto la fine della lista
            
            current->next = nuovo;
        }

        //(4) Rimozione:
        
        void popFromHead()
        {
            if(head==nullptr)
                return; //lista vuota, nulla da eliminare
            
            Nodo* cancella = head;
            head = head->next;
            if(head != nullptr)
                head->prev = nullptr;
            else tail = nullptr; //se head = nullptr allora anche tail

            delete cancella;
        }

        void popFromTail()
        {
            if(tail == nullptr)
                return; //lista vuota: nulla da eliminare.

            Nodo* cancella = tail;
            tail = tail->prev;
            if(tail != nullptr)
                tail->next = nullptr; //stiamo cancellando il next (vecchia tail)
            else head = nullptr; //se tail è vuoto allora abbiamo finito la lista
            
            delete cancella;
        }

        void popValuesWith(const int& key)
        {
            if(head== nullptr)
                return;

            Nodo* current = head; //Nodo di scorrimento... 
            while(current != nullptr) //finché non finisco la lista
            {
                if(current->value == key)
                {
                    Nodo* cancella = current; //nodo da cancellare
                    //riconnetti next e prev
                    if(current->prev) //se ho qualcosa prima di current: allora connetti per evitare buchi nella lista
                        current->prev->next = current->next; 
                    else head = current->next; //non ho nulla prima allora procedo in avanti

                    //riconnetti prev e next
                    if(current->next) //se current ha un successore 
                        current->next->prev = current->prev; //allora connetto i due per evitare buco 
                    else tail = current->prev;

                    current = current->next; //scorri in avanti
                    delete cancella;
                }
                else current = current->next; //valore non trovato, vai avanti
            }
        }

        //5 ricerca:
        void find(const int& key) const //non modifico nulla
        {
            if(head==nullptr)
            {
                cout << "Lista vuota: nulla da cercare" << endl;
                return;
            }
            
            Nodo* current = head; //ricerca da cima
            while(current != nullptr) //si assume che non sia del tutto ordinato
            {
                if(current->value == key)
                {
                    cout << "Trovato valore: " << current->value << endl;
                    return; 
                }

                current = current->next;
            }
        }

        //(6) semplice stampa:
        void printFromHead() const
        {
            Nodo* current = head;
            cout << "Lista (da head): ";
            while(current != nullptr)
            {
                cout << current->value << " <-> ";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }  

        void printFromTail() const
        {
            Nodo* current = tail;
            cout << "Lista (da tail): ";
            while(current != nullptr)
            {
                cout << current->value << " <-> ";
                current = current->prev; 
            }
            cout << "nullptr" << endl;
        }
};


int main()
{
    /* Le mie funzioni di classe Lista:

    push_head(int); //inserimento in testa;
    push_tail(int); //inserimento in fondo;
    pushInOrder(int); //inserimento ordinato nella lista;

    popFromHead(); //elimina elemento in cima;
    popFromTail(); //elimina elemento in fondo;
    popValuesWith(int); //elimina tutti gli elementi con valore inserito

    printFromHead(); //stampa dalla cima
    printFromTail(); //stampa dal fondo

    + distruttore di lista 
    */
    Lista l;
    l.push_head(10);
    l.push_tail(20);
    l.pushInOrder(15);
    l.pushInOrder(1);
    l.pushInOrder(3);
    l.pushInOrder(8);
    l.pushInOrder(22);

    l.printFromHead();
    l.printFromTail();

    cout << "Inserisci elemento da cercare: "; int key; cin >> key; 
    l.find(key);
    cout << "Elimino tutti i valori con questa chiave di ricerca." << endl;
    l.popValuesWith(key);
    l.printFromHead();

    return 0;
}
