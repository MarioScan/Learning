#ifndef BTS_H
#define BTS_H

#include "Studente.h"
#include <iostream>
#include <fstream> //lettura da file
#include <sstream> //necessario per facilitare lettura visto che file è diviso da virgole...
using namespace std;

template <class T>
class Nodo
{
    private:
        T dato;
        Nodo<T>* left;
        Nodo<T>* right;
    public:
        Nodo() : dato(), left(nullptr), right(nullptr) {}
        Nodo(const T& data) : dato(data), left(nullptr), right(nullptr) {}
        ~Nodo() {}

        const T& get_dato() const { return dato;}
        Nodo<T>* get_left() const { return left;}
        Nodo<T>* get_right() const { return right;}

        void set_dato(const T& newDato) { dato = newDato; }
        void set_left(Nodo<T>* newLeft) { left = newLeft;}
        void set_right(Nodo<T>* newRight) { right = newRight; }
};

template <class T>
class BTS
{
    private:
        Nodo<T>* root;
        Nodo<T>* insertHelper(Nodo<T>* nodo, const T& nuovoDato)
        {
            if(!nodo)
                return new Nodo<T>(nuovoDato);
            
            if(nuovoDato->get_matricola() <= nodo->get_dato()->get_matricola())
                nodo->set_left(insertHelper(nodo->get_left(),nuovoDato));
            else 
                nodo->set_right(insertHelper(nodo->get_right(),nuovoDato));
                
            return nodo; //ritorno nodo per mantenere struttura albero.
        }

        Nodo<T>* removeNodeHelper(Nodo<T>* nodo, float key) //rimuove tutti studenti sotto la media
        {
            if(!nodo)
                return nodo;
            
            nodo->set_left(removeNodeHelper(nodo->get_left(),key));
            nodo->set_right(removeNodeHelper(nodo->get_right(),key));

            if(nodo->get_dato()->get_media() < key)
            {
                cout << "[RIMOSSO]:" << *(nodo->get_dato()) << endl;
                //rimozione:
                //caso 1: no figli
                if(!nodo->get_left() && !nodo->get_right())
                {
                    delete nodo;
                    return nullptr;
                }

                //caso 2: un solo figlio
                else if(nodo->get_left() == nullptr) //non esiste figlio sx, esiste figlio dx:
                {
                    Nodo<T>* temp = nodo->get_right();
                    delete nodo;
                    return temp; //salva figlio destro
                } 

                else if(nodo->get_right() == nullptr)
                {
                    Nodo<T>* temp = nodo->get_right();
                    delete nodo;
                    return temp;
                }

                //caso 3: due figli
                else
                {
                    //trova successore
                    Nodo<T>* temp = nodoMinimo(nodo->get_right()); //salvo figlio più grande

                    nodo->set_dato(temp->get_dato()); //sovrascrivo il padre con i dati del figlio

                    nodo->set_right(removeNodeHelper(nodo->get_right(),key)); //ripeto ricorsione
                }
            }
            return nodo;
        }

        void stampaHelper(Nodo<T>* nodo) const //inOrder
        {
            if(!nodo)
                return;
            stampaHelper(nodo->get_left());
            cout << *(nodo->get_dato()) << endl;
            stampaHelper(nodo->get_right());
        }

        void clearHelper(Nodo<T>* nodo) //visita postOrder
        {
            if(!nodo)
                return;
            clearHelper(nodo->get_left());
            clearHelper(nodo->get_right());
            delete nodo;
        }

        int get_altezza_helper(Nodo<T>* nodo) const
        {
            if(!nodo)
                return 0;
            return 1 + max(get_altezza_helper(nodo->get_left()), get_altezza_helper(nodo->get_right()));
        }

        /*
        void searchMatricolaHelper(Nodo<T>* nodo, int key) 
        {
            if(!nodo)
                return;

            if(nodo->get_dato()->get_matricola() == key)
            {
                cout << "Trovato: " << *(nodo->get_dato()) << endl;
                return;
            }

            searchMatricolaHelper(nodo->get_left(),key);
            searchMatricolaHelper(nodo->get_right(),key);
        }*/

        Nodo<T>* searchMatricolaHelper(Nodo<T>* nodo, int key)
        {
            if(!nodo)
                return nullptr;
            
            if(nodo->get_dato()->get_matricola() == key)
                return nodo; //trovato

            Nodo<T>* left = searchMatricolaHelper(nodo->get_left(),key);
            if(left)
                return left;
            
            return searchMatricolaHelper(nodo->get_right(),key);
        }

    public:
        BTS() : root(nullptr) {}
        
        bool isEmpty() { return root == nullptr; }
        void insert(const T& nuovoDato)
        {
            root = insertHelper(root,nuovoDato);
        }

        Nodo<T>* nodoMinimo(Nodo<T>* nodo) //successore per rimozione figli
        {
            while(nodo && nodo->get_left())
                nodo = nodo->get_left();
            return nodo;
        }

        void removeNode(float key) //media minima
        {
            cout << "Rimozione studenti sotto la media di [" << key << "]:" << endl;
            root = removeNodeHelper(root,key);
        }

        void stampa() const// inOrder: left root right, (preOrder: root left right (prima nodo poi figli)), postOrder(left, right, root) (prima figli poi nodo))
        {
            cout << "\nStampa albero - inOrder:" << endl;
            stampaHelper(root);
        }

        void loadFromFile(const string& nomeFile)
        {
            ifstream file(nomeFile);
            if(!file)
            {
                cerr << "Errore durante apertura file, chiusura programma." << endl;
                exit(1);
            }

            string buffer;
            while(getline(file,buffer))
            {
                stringstream ss(buffer);
                string nome,cognome,matricola,media;

                getline(ss, matricola, ',');
                getline(ss, nome, ',');
                getline(ss, cognome, ',');
                getline(ss, media);

                insert(new Studente(stoi(matricola),nome,cognome,stof(media)));
            }

            file.close();
        }

        int get_altezza() const
        {
            return get_altezza_helper(root);
        }

        /*
        void searchMatricola(int key)
        {
            searchMatricolaHelper(root,key);
        }
        */
        
        void searchMatricola(int key)
        {
            Nodo<T>* temp = searchMatricolaHelper(root, key);
            if(temp)
                cout << "Trovato: " << *(temp->get_dato()) << endl;
            else 
                cout << "Studente non trovato." << endl;
        }

        void clear() {
            if(isEmpty())
                return;
            clearHelper(root);
            root = nullptr;
        }
        ~BTS() { clear(); }
};

#endif