#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include "LibroPrestato.h"
using namespace std;

template <class T>
class Nodo
{
    private:
        T dato;
        Nodo<T>* next;
        Nodo<T>* prev;
    public:
        Nodo() : dato(), next(nullptr), prev(nullptr) {}
        Nodo(const T& data) : dato(data), next(nullptr), prev(nullptr) {}
        ~Nodo() {}

        const T& get_dato() const { return dato; }
        Nodo<T>* get_next() const { return next; }
        Nodo<T>* get_prev() const { return prev; }

        void set_next(Nodo<T>* newNext) { next = newNext; }
        void set_prev(Nodo<T>* newPrev) { prev = newPrev; }
};

template <class T>
class Lista
{
    private: 
        Nodo<T>* head;
        Nodo<T>* tail;
        int maxNodes;
        int counter = 0; 
    public:
        Lista(int max) : maxNodes(max), head(nullptr), tail(nullptr) {}

        bool isEmpty() { return head == nullptr; }
        bool isFull() { return counter >= maxNodes; }

        Lista<T>* insert(const T& nuovoDato) //inserimento in testa
        {
            if(isFull())
            {
                cout << "Lista piena!";
                return this;
            }
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(!nuovo)
            {
                cerr << "Errore, impossibile inserire nuovo nodo" << endl;
                exit(1);
            }
            counter++;

            if(isEmpty())
            {
                head = tail = nuovo;
                return this;
            }

            nuovo->set_next(head);
            head->set_prev(nuovo);
            head = nuovo;
            return this;
        }

        void removeTail() 
        {
            if(isEmpty())
                return;
            
            Nodo<T>* temp = tail;
            tail = tail->get_prev(); 
            tail->set_next(nullptr);
            delete temp;
            counter--;
        }

        void removeHead()
        {
            if(isEmpty())
                return;
            
            Nodo<T>* temp = head;
            head = head->get_next();
            head->set_prev(nullptr);
            delete temp;
            counter--;
        }
        void removeBefore(int key)
        {
            cout << "Rimozione libri prima di anno: " << key << endl; 
            if(isEmpty())
            {
                cout << "Nulla da rimuovere." << endl;
                return;
            }
            Nodo<T>* current = head;
            while(current)
            {
                Nodo<T>* succ = current->get_next();
                Nodo<T>* temp = current;
                if(current->get_dato()->get_anno() < key)
                {
                    cout << "[RIMOSSO]: ";
                    current->get_dato()->stampa();
                    cout << endl;
                    if(current->get_prev() && current->get_next())
                    {
                        current->get_prev()->set_next(current->get_next());
                        current->get_next()->set_prev(current->get_prev());
                    }
                    else if(!current->get_next())
                    {
                        current->get_prev()->set_next(nullptr);
                        tail = current->get_prev();
                    }
                    else if(!current->get_prev())
                    {
                        current->get_next()->set_prev(nullptr);
                        head = current->get_next();
                    }
                    delete temp;
                }
                current = succ;
            }
        }
        /*
        void removeBefore(int key)
        {
            cout << "Rimozione libri prima di anno: " << key << endl; 
            if(isEmpty())
            {
                cout << "Nulla da rimuovere." << endl;
                return;
            }

            while(head && head->get_dato()->get_anno() < key)
            {
                Nodo<T>* temp = head;
                cout << "[RIMOSSO]: ";
                head->get_dato()->stampa();
                cout << endl;
                delete head->get_dato();
                head = head->get_next();
                head->set_prev(nullptr);
                delete temp;
            }
            Nodo<T>* current = head->get_next();
            while(current)
            {
                Nodo<T>* temp = current;
                if(current->get_dato()->get_anno() < key)
                {
                    cout << "[RIMOSSO]: ";
                    current->get_dato()->stampa();
                    cout << endl;
                    if(current->get_prev() && current->get_next())
                    {
                        current->get_prev()->set_next(current->get_next());
                        current->get_next()->set_prev(current->get_prev());
                    }
                    else if(!current->get_next())
                    {
                        current->get_prev()->set_next(nullptr);
                        tail = current->get_prev();
                    }
                    delete current->get_dato();
                    delete temp;
                }
                current = current->get_next();
            }
        }*/

        void clear() {
            while(!isEmpty())
                removeTail();

            counter = 0;
        }

        ~Lista() { clear(); }


        void stampa() const 
        {
            Nodo<T>* current = head;
            while(current)
            {
                current->get_dato()->stampa();
                cout << endl;
                current = current->get_next();
            }
        }

        int get_durata_totale_prestiti() const 
        {
            Nodo<T>* current = head;
            int totale = 0;
            while(current)
            {
                LibroPrestato* lp = dynamic_cast<LibroPrestato*>(current->get_dato());
                if(lp)
                    totale+=lp->get_libroInPrestito()->get_durata();
                current = current->get_next();
            }
            return totale;
        }

};


#endif