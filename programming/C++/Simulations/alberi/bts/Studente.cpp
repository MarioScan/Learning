#include <iostream>
#include "Studente.h"
using namespace std;


Studente::Studente() : matricola(0), nome(""), cognome(""), media(0.0) {}
Studente::Studente(int mat, const string& n, const string& cog, float avg) 
: matricola(mat), nome(n), cognome(cog), media(avg) {}
Studente::Studente(const Studente& s) : matricola(s.matricola), nome(s.nome), cognome(s.cognome), media(s.media) {}
Studente::~Studente() {}

int Studente::get_matricola() const { return matricola; }
const string& Studente::get_nome() const { return nome; }
const string& Studente::get_cognome() const { return cognome; }
float Studente::get_media() const { return media; }

void Studente::set_matricola(int newMatricola) { matricola = newMatricola; }
void Studente::set_nome(const string& newNome) { nome = newNome; }
void Studente::set_cognome(const string& newCognome) { cognome = newCognome;}
void Studente::set_media(float newMedia) { media = newMedia; }

ostream& operator<<(ostream& os, const Studente& s)
{
    os << s.get_matricola() << ": " << s.get_nome() << " " << s.get_cognome() << " - " << s.get_media();
    return os;
}

istream& operator>>(istream& is, Studente& s)
{
    is >> s.matricola >> s.nome >> s.cognome >> s.media;
    return is; 
}
