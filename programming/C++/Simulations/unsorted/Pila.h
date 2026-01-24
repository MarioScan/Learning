#ifndef PILA_H
#define PILA_H

#include <iostream>
#include "LibroPrestato.h"
using namespace std;

template <typename T>
class Nodo
{
    private:
        T dato;
        Nodo<T>* next;
    public:
        Nodo() : dato(), next(nullptr) {}
        Nodo(const T& data) : dato(data), next(nullptr) {}
        ~Nodo() {}
        const T& get_dato() const { return dato; }
        Nodo<T>* get_next() const { return next; } 
        void set_next(Nodo<T>* newNext) { next = newNext; }
};

template <typename T>
class Pila
{
    private:
        Nodo<T>* top;
    public:
        Pila() : top(nullptr) {}

        bool isEmpty()
        {
            return top == nullptr;
        }

        Pila<T>* push(const T& nuovoDato)
        {
            if(!nuovoDato)
            {
                cerr << "Errore: nuovoDato mancante" << endl;
                exit(1);
            }
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(!nuovo)
            {
                cerr << "Errore: impossibile creare nuovo nodo" << endl;
                exit(1);
            }

            if(isEmpty())
            {
                top = nuovo;
                return this;
            }

            nuovo->set_next(top);
            top = nuovo;
            return this;
        }

        void pop()
        {
            if(isEmpty())
            {
                cout << "Arrestato tentativo pop in pila vuota" << endl;
                return;
            }    

            Nodo<T>* temp = top;
            delete top->get_dato();
            top = top->get_next();
            delete temp;
        }

        void clear()
        {
            while(top)
            {
                Nodo<T>* temp = top;
                delete top->get_dato();
                top = top->get_next();
                delete temp;
            }
        }

        void stampa() const 
        {
            cout << "\nContenuto della pila:" << endl;
            Nodo<T>* current = top; //altrimenti perdo posizione di top  
            while(current)
            {
                current->get_dato()->stampa();
                current = current->get_next();
                cout << endl;
            }
        }

        ~Pila() 
        {
            if(!isEmpty())
                clear();
        }

        void removeUnderPrice(float key)
        {
            cout << "\n/!\\ Rimozione libri sotto il prezzo di [" << key << "] dalla pila." << endl; 
            while(top && top->get_dato()->get_prezzo() < key)
            {
                cout << "/!\\ Rimozione di: ";
                top->get_dato()->stampa();
                cout << endl;
                Nodo<T>* temp = top;
                delete top->get_dato();
                top = top->get_next();
                delete temp;
            }

            if(!top)
                return;

            Nodo<T>* current = top->get_next(); //altrimenti perdo posizione di top  
            
            while(current)
            {
                if(current->get_next() && current->get_next()->get_dato()->get_prezzo() < key)
                {
                    cout << "/!\\ Rimozione di: ";
                    current->get_next()->get_dato()->stampa();
                    cout << endl;
                    Nodo<T>* temp = current->get_next();
                    delete current->get_next()->get_dato();
                    current->set_next( current->get_next()->get_next());
                    delete temp;
                }
                current = current->get_next();
            }
        }

        int durataComplessivaPrestiti()
        {
            int totaleDurata = 0;
            Nodo<T>* current = top; //altrimenti perdo posizione di top  
            while(current)
            {
                LibroPrestato* temp = dynamic_cast<LibroPrestato*>(current->get_dato());
                if(temp)
                {
                    totaleDurata += temp->get_durata_prestito();
                }
                current = current->get_next();
            }
            return totaleDurata;
        }

        void mostraLibriPrestati()
        {
            Nodo<T>* current = top; //altrimenti perdo posizione di top  
            while(current)
            {
                LibroPrestato* temp = dynamic_cast<LibroPrestato*>(current->get_dato());
                if(temp)
                {
                    temp->stampa();
                    cout << endl;
                }
                current = current->get_next();
            }
        }

        /* //extra ma non funziona
        Pila<T*>* ribaltaPila()
        {
            Pila<T*>* ribaltata = new Pila<T*>();
            Nodo<T>* current = top;
            while(current)
            {
                ribaltata->push(current);
                current = current->get_next();
            }
            return ribaltata;
        }*/
};

#endif