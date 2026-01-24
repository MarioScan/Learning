#ifndef STUDENTE_H
#define STUDENTE_H

#include <iostream>
using namespace std;

class Studente
{
    private:
        int matricola;
        string nome;
        string cognome;
        float media;
    public:
        Studente();
        Studente(int, const string&, const string&, float); 
        Studente(const Studente&);
        ~Studente();

        int get_matricola() const;
        const string& get_nome() const;
        const string& get_cognome() const;
        float get_media() const;
        
        void set_matricola(int newMatricola);
        void set_nome(const string& newNome);
        void set_cognome(const string& newCognome);
        void set_media(float newMedia);

        friend istream& operator>>(istream&, Studente&);

};
ostream& operator<<(ostream&, const Studente&);

#endif

