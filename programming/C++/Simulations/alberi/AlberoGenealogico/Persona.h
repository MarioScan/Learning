#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
using namespace std;
//Si presume che una persona possa avere al massimo due figli per rispettare la tipologia di Albero di Ricerca BTS (Binary Tree Search)
//e che i figli sono connessi al Padre (puro scopo didattico)
class Persona
{
    private:
        string nome;
        int annoNascita; //YYYY
        //ha figli? 
        //Persona* padre;
        Persona* figlioSinistro;
        Persona* figlioDestro;

    public:
        //Persona(const string& name, int yearBirth, Persona* father) : nome(name), annoNascita(yearBirth), padre(father), figlioSinistro(nullptr), figlioDestro(nullptr) {}
        //caso di default senza padre (Bisnonno) lo consideremo come primo dell'albero Genealogico e quindi senza padre
        Persona(const string& name, int yearBirth) : nome(name), annoNascita(yearBirth), figlioSinistro(nullptr), figlioDestro(nullptr) {}
        ~Persona() { cout << "Chiamato distruttore Persona." << endl; }

        const string& get_nome() const { return nome; }
        int get_annoNascita() const { return annoNascita; }
        Persona* get_figlioSinistro() const { return figlioSinistro; } //dato o nullptr
        Persona* get_figlioDestro() const { return figlioDestro; }

        void set_nome(const string& newNome) { nome = newNome; }
        void set_annoNascita(int newAnno) { annoNascita = newAnno; }
        void set_figlioSinistro(Persona* newFiglioSinistro) { figlioSinistro = newFiglioSinistro; }
        void set_figlioDestro(Persona* newFiglioDestro) { figlioDestro = newFiglioDestro; }

        friend ostream& operator<<(ostream&,const Persona&);
        void print() const
        {
            cout << *this;
        }

        void printWithoutChildren() const
        {
            cout << get_nome() << " (" << get_annoNascita() << ")";
        }
};
ostream& operator<<(ostream& os,const Persona& p)
{
    os << p.get_nome() << " (" << p.get_annoNascita() << ")";
    os << " - Figli:";
    if(p.get_figlioSinistro() != nullptr)
        os << " " << p.get_figlioSinistro()->get_nome(); 
    if(p.get_figlioDestro() != nullptr)
        os << " " << p.get_figlioDestro()->get_nome();
    else if(!p.get_figlioDestro() && !p.get_figlioSinistro())
        os << " //"; 

    return os;
}

#endif