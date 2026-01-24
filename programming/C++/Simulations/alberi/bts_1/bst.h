#ifndef bts_h
#define bts_h

#include "Persona.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template <typename T>
class Nodo
{
    private:
        T data;
        Nodo<T>* left;
        Nodo<T>* right;
    public:
        Nodo(const T& dato) : data(dato), left(nullptr), right(nullptr) {}
        ~Nodo() {}

        const T& get_data() const { return data; }
        Nodo<T>* get_left() const { return left; }
        Nodo<T>* get_right() const { return right; }

        void set_dato(const T& newData) { data = newData; }
        void set_left(Nodo<T>* newLeft) { left = newLeft; }
        void set_right(Nodo<T>* newRight) { right = newRight; }        
};



template <typename T>
class BST
{
    private:
        Nodo<T>* root;
        
        Nodo<T>* insertHelper(Nodo<T>* nodo, const T& nuovoDato)
        {
            if(!nodo)
                return new Nodo<T>(nuovoDato);
            
            if(nuovoDato->get_matricola() < nodo->get_data()->get_matricola())
                nodo->set_left(insertHelper(nodo->get_left(),nuovoDato));
            if(nuovoDato->get_matricola() > nodo->get_data()->get_matricola())
                nodo->set_right(insertHelper(nodo->get_right(),nuovoDato));
            if(nuovoDato->get_matricola() == nodo->get_data()->get_matricola())
            {
                cerr << "Errore: non si possono avere due matricole uguali!" << endl;
                exit(1);
            }
            return nodo;
        }
        void printAllHelper(Nodo<T>* nodo)
        {
            if(!nodo)
                return;

            printAllHelper(nodo->get_left());
            nodo->get_data()->print(); cout << endl;
            printAllHelper(nodo->get_right());
        }

        bool searchPerMatricolaHelper(Nodo<T>* nodo, int matricola)
        {
            if(!nodo)
                return false;
            if(matricola == nodo->get_data()->get_matricola())
                return true;
            else if(matricola < nodo->get_data()->get_matricola())
                searchPerMatricolaHelper(nodo->get_left(), matricola);
                
            return searchPerMatricolaHelper(nodo->get_right(), matricola);
        }

        Nodo<T>* removePerMatricolaHelper(Nodo<T>* nodo, int matricola)
        {
            if(!nodo)
                return nodo; //nullptr

            if(matricola < nodo->get_data()->get_matricola())
                nodo->set_left(removePerMatricolaHelper(nodo->get_left(),matricola));
            else if(matricola > nodo->get_data()->get_matricola())
                nodo->set_right(removePerMatricolaHelper(nodo->get_right(),matricola));
                
            else //(matricola == nodo->get_data()->get_matricola())
            {
                cout << "[RIMOSSO]: "; nodo->get_data()->print(); cout << endl;
                //nodo foglia
                if(!nodo->get_left() && !nodo->get_right())
                {
                    delete nodo->get_data();
                    delete nodo;
                    return nullptr;
                }   
                //nodo ha un solo figlio
                else if(!nodo->get_right()) //figlio a sinistra
                {
                    Nodo<T>* temp = nodo->get_left();
                    delete nodo->get_data();
                    delete nodo;
                    return temp;
                }
                else if(!nodo->get_left()) //figlio a destra
                {
                    Nodo<T>* temp = nodo->get_right();
                    delete nodo->get_data();
                    delete nodo;
                    return temp;
                }
                //ha due figli 
                else
                {
                    Nodo<T>* minNode = findMin(nodo->get_right());
                    nodo->set_dato(minNode->get_data());
                    nodo->set_right(removePerMatricolaHelper(nodo->get_right(),minNode->get_data()->get_matricola())); //vado a eliminare il nodo che ho copiato in nodo con questa mossa
                }
            }
            return nodo;
        }
    public:
        BST() : root(nullptr) {}

        bool isEmpty() { return root == nullptr; }

        BST<T>* insert(const T& nuovoDato)
        {
            root = insertHelper(root, nuovoDato);
            return this;
        }

        Nodo<T>* findMin(Nodo<T>* nodo) const //non modifica nulla, è una copia del puntatore (safe to use)
        {
            while(nodo && nodo->get_left())
                nodo = nodo->get_left();
            return nodo;
        }

        BST<T>* removePerMatricola(int matricola)
        {
            cout << "\nRimozione matricola \"" << matricola << "\":" << endl; 

            if(!searchPerMatricola(matricola))
            {
                cout << "Elemento con matricola \"" << matricola << "\n non trovato." << endl;
                return this;
            }

            root = removePerMatricolaHelper(root, matricola);    
            return this;
        }

        bool searchPerMatricola(int matricola)
        {
            if(searchPerMatricolaHelper(root, matricola))
                return true;
            return false;   
        }

        void printAll()
        {
            cout << "\nStampa di tutto l'albero (visita inOrder):" << endl;
            printAllHelper(root);
        }

        void insertFromFile(const string& nomeFile)
        {
            ifstream file(nomeFile);
            if(!file)
            {
                cerr << "Errore: impossibile aprire file." << endl;
                return;
            }

            string buffer;
            while(getline(file,buffer))
            {
                stringstream ss(buffer);
                int matricola;
                string nome, cognome, materia;
                float media;

                ss >> matricola >> nome >> cognome;
                if(ss >> media) //se è numerico:
                    insert(new Studente(matricola, nome, cognome, media));
                else
                {
                    ss.clear(); //resetto (pulisco - clear) flag errori
                    //ss >> materia; //se solo una parola 
                    getline(ss, materia);
                    if(materia[0] == ' ')
                        materia = materia.substr(1); //rimuovo casella 0 con spazio
                    insert(new Docente(matricola, nome, cognome, materia));
                }
                

            }

            file.close();
        }
};


#endif