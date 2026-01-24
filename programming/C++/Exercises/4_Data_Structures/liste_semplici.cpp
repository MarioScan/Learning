/*
    1. 🎯 LISTA SEMPLICE / SINGOLA --> Ogni nodo punta al successivo


    🔧 Operazioni sui nodi:
        <+>  Inserimento (push_front, push_back)
        <+>  Cancellazione (delete_val)
        <+>  Ricerca (find)
        <+>  Stampa (print)
*/

#include <iostream>
using namespace std;


class Nodo
{
    public:
       int val;
       Nodo* next; 

    Nodo(int value) : val(value), next(nullptr) {}
};

class Lista
{
    private:
        Nodo* head;
    public:
        Lista() : head(nullptr) {}

        //distruttore lista
        ~Lista() 
        {
            cout << "Distruttore lista chiamato." << endl;
            while(head != nullptr)
            {
                Nodo* temp = head; 
                head = head->next; //scorre tutti gli elementi e li elimina: elimina il corrente e va al successivo;
                delete temp;
            }
        }

        //inserimento lista
        void push(int value)
        {
            Nodo* nuovo = new Nodo(value);
            nuovo->next = head;
            head = nuovo;
        }

        //stampa elementi
        void print()
        {
            Nodo* temp = head;
            while(temp != nullptr)
            {
                //operazione che vogliamo --> in questo caso stampa
                cout << temp->val << " -> "; 
                temp = temp->next;
            }
            cout << "nullptr" << endl; //aiuta a mostrare che abbiamo finito
        }

        //funzione di ricerca
        bool search(int key) const 
        {
            Nodo* temp = head;
            while(temp != nullptr)
            {
                if(temp->val == key)
                {
                    return true; //Elemento trovato.
                }
                temp = temp->next;
            }
            return false; //Elemento non trovato.
        }
        
        //rimuovi ultimo elemento
        void pop_head()
        {
            if(head == nullptr) return; //lista vuota

            Nodo* temp = head;
            head = head->next;
            delete temp;
        }

        //elimina tutti elementi con questo valore
        void pop_search(int key)
        {
            //in cima al nodo:
            while(head != nullptr && head->val == key)
            {
                Nodo* cancella = head;
                head = head->next;
                delete cancella;
            }

            //altri casi
            Nodo* current = head;
            while(current != nullptr && current->next != nullptr)
            {
                if(current->next->val == key) //trovato --> cancellalo
                {
                    Nodo* cancella = current->next;
                    current->next = current->next->next;
                    delete cancella;
                }
                else current = current->next; //scorrimento 
            }
        }
};


int main()
{
    Lista list;
    list.push(5);
    list.push(10);
    list.push(20);
    list.push(4);

    list.print();
    int key;
    cout << "inserisci elemento che vorresti cercare: "; cin >> key;
    cout << (list.search(key) ? "Elemento trovato." : "Elemento non trovato.") << endl;
    
    list.pop_head();
    cout << "Rimuovo ultimo elemento inserito nella lista:" << endl;
    list.print();

    cout << "Inserisco altri valori e poi distruggo tutti quelli di valore 4 nella lista:" << endl;
    list.push(4);
    list.push(40);
    list.push(2);
    list.push(4);
    list.push(10);
    list.push(4);

    list.print();
    //anniento i numeri 4:
    list.pop_search(4);

    list.print();
    cout << "Fine programma." << endl;
    //Distruttore lista...

    return 0;
}