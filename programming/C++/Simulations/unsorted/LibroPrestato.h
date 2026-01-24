#ifndef LIBROPRESTATO_H
#define LIBROPRESTATO_H

#include <iostream>
#include "Libro.h"
#include "Prestito.h"
using namespace std;

class LibroPrestato : public Libro
{
    private:
        Prestito* libro_in_prestito;
    public:
        LibroPrestato() : Libro(), libro_in_prestito(nullptr) {}
        LibroPrestato(const string& title, const string& author, float price, Prestito* borrowerUser) 
        : Libro(title,author,price), libro_in_prestito(borrowerUser) {}
        ~LibroPrestato() 
        {
            if(libro_in_prestito)
                delete libro_in_prestito;
        }

        int get_durata_prestito() const { return libro_in_prestito->get_durata_giorni(); }

        void stampa() const override
        {
            Libro::stampa();
            if(libro_in_prestito)
                libro_in_prestito->stampa();
        }
};


#endif