#ifndef CODA_H
#define CODA_H

#include "Paziente.h"
#include <iostream>
using namespace std;

template <typename T>
class Nodo
{
    private:
        T dato;
        Nodo<T>* next;
        Nodo<T>* prev;
    public:
        Nodo(const T& data) : dato(data), next(nullptr), prev(nullptr) {}
        ~Nodo() {}
        
        const T& get_dato() const { return dato; }
        Nodo<T>* get_next() const { return next; }
        Nodo<T>* get_prev() const { return prev; }

        void set_dato(const T& newDato) { dato = newDato; }
        void set_next(Nodo<T>* newNext) { next = newNext; }
        void set_prev(Nodo<T>* newPrev) { prev = newPrev; }
};

template <typename T> //FIFO
class Coda
{
    private:
        Nodo<T>* front;
        Nodo<T>* rear;
    public:
        Coda() : front(nullptr), rear(nullptr) {}
        
        bool isEmpty()
        {
            return front==nullptr;
        }

        Coda<T>* enqueue(const T& nuovoDato)
        {
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(!nuovo)
            {
                cerr << "Impossibile creare nuovo nodo." << endl;
                exit(1);
            }

            if(isEmpty())
            {
                front = rear = nuovo;
                return this;
            }

            //inserimento in coda (FIFO)
            nuovo->set_prev(rear);
            rear->set_next(nuovo);
            rear = nuovo;
            sort();
            return this;
        }

        T dequeue()
        {
            if(isEmpty())
            {
                cerr << "Tentativo dequeue in coda vuota, errore." << endl;
                exit(1);
            }

            T r = front->get_dato();
            Nodo<T>* temp = front;
            //delete front->get_dato(); //non è puntatore!!
            front = front->get_next();
            delete temp;
            return r;
        }

        void dequeueNode(Nodo<T>* node)
        {
            if(isEmpty)
                return;
            if(!node)
            {
                cerr<<"nodo non valido errore."<< endl;
                exit(1);
            }

            if(node->get_prev() && node->get_next())
            {
                node->get_prev->set_next(node->get_next());
                node->get_next->set_prev(node->get_prev());
                delete node;
                return;
            }

            if(node->get_prev()) //primo coda
            {
                node->get_prev()->set_next(nullptr);
                front = node->get_prev();
            }

            else if(node->get_next()) //ultimo coda
            {
                node->get_next->set_prev(nullptr);
                rear = node->get_next();
            }

            delete node;
        }

        void clear()
        {
            while(!isEmpty())
            {
                Nodo<T>* temp = front;
                //delete front->get_dato(); //non è puntatore!!
                front = front->get_next();
                delete temp;
            }
        }

        ~Coda() { clear(); }  

        void stampa() const
        {
            Nodo<T>* current = front;
            while(current)
            {
                current->get_dato()->stampa();
                cout << endl;
                current = current->get_next();
            }
        }

        void sort();
        void turni();

};

template <typename T>
void Coda<T>::sort() // !!!! viene eseguito ad ogni enqueue !!!!
    {
        if(isEmpty() || front->get_next() == nullptr)
            return; //no sort needed.

        Nodo<T>* current = front->get_next();
        while(current)
        {
            Nodo<T>* key = current;
            Nodo<T>* prev = current->get_prev();
            //scorri finché non trova un codice più grande o uguale al nuovo elemento
            //per int: Rosso (0) < Giallo(1) < Verde(2)
            while (key && prev && static_cast<int>(key->get_dato()->get_codice()) < static_cast<int>(prev->get_dato()->get_codice()))
            {
                //iniziamo swap
                Nodo<T>* succ = key->get_next();
                
                //scollego current dai suoi adiacenti
                if(key->get_prev())
                    prev->set_next(key->get_next());
                if(key->get_next())
                    succ->set_prev(key->get_prev());
                
                //connetto key al posto di prev
                key->set_prev(prev->get_prev());
                key->set_next(prev);

                if(prev->get_prev())
                    prev->get_prev()->set_next(key);
                else
                    front = key; //ho raggiunto la cima della coda
                prev->set_prev(key);

                //aggiorno per prossimo confronto
                prev = key->get_prev(); 
            }
            current = current->get_next();
        }
        //aggiorno rear
        rear = front;
        while(rear->get_next())
            rear = rear->get_next();
    }

template <typename T>
void Coda<T>::turni()
{
    static int codice=0; //R = 0 , G = 1, V = 2 
    int conta=0;

    
}


    //scorrimento: R=0, G=1, V=2 
    /*
        Il regolamento dell'ospedale ci impone di trattare in ordine:
        2 Rossi
        1 Giallo
        1 verde 
        ripeti ciclo
    */

#endif