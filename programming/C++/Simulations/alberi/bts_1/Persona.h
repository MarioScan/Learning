#ifndef P_H
#define P_H

#include <iostream>
using namespace std;

class Persona
{
    private:
        string nome;
        string cognome;
        int matricola;
    public:
        Persona(int mat, const string& name, const string& surname) : matricola(mat), nome(name), cognome(surname) {}
        ~Persona() {}
        
        int get_matricola() const { return matricola; }
        const string get_nome() const { return nome; }
        const string get_cognome() const { return cognome; }

        virtual void print() const = 0; //metodo astratto
};

class Studente : public Persona
{
    private:
        float media;
    public: 
        Studente(int mat, const string& nome, const string& cognome, float avg) : Persona(mat, nome, cognome), media(avg) {}
        ~Studente() {}

        float get_media() const { return media; }

        friend ostream& operator<<(ostream&, const Studente&);
        void print() const override
        {
            cout << *this; 
        }
};
ostream& operator<<(ostream& os, const Studente& s)
{
    os << "Studente - " << s.get_matricola() << " - " << s.get_nome() << " " << s.get_cognome() << " - " << s.get_media();
    return os;
}

class Docente : public Persona
{
    private:
        string materia;
    public:
        Docente(int mat, const string& nome, const string& cog, const string& subject) : Persona(mat,nome,cog), materia(subject) {}
        ~Docente() {}

        const string& get_materia() const { return materia; }

        friend ostream& operator<<(ostream&, const Docente&);
        void print() const override
        {
            cout << *this;
        }
};
ostream& operator<<(ostream& os, const Docente& d)
{
    os << "Docente - " << d.get_matricola() << " - " << d.get_nome() << " " << d.get_cognome() << " - " << d.get_materia();
    return os;
}


#endif