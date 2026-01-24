#ifndef LIBROPRESTATO_H
#define LIBROPRESTATO_H

#include <iostream>
#include "Libro.h"
#include "Prestito.h"
using namespace std;

class LibroPrestato : public Libro
{
    private:
        Prestito* libroInPrestito;
    public:
        LibroPrestato() : Libro(), libroInPrestito(nullptr) {}
        LibroPrestato(const string& titolo, const string& autore, int anno, Prestito* borrowed) 
        : Libro(titolo,autore,anno), libroInPrestito(borrowed) {}
        ~LibroPrestato() {
            if(libroInPrestito)
                delete libroInPrestito;
        }

        Prestito* get_libroInPrestito() const { return libroInPrestito; }


        //friend ostream& operator<<(ostream&, const LibroPrestato&);
        void stampa() const override
        {
            Libro::stampa();
            cout << " - prestato a: ";
            if(libroInPrestito)
                libroInPrestito->stampa();
        }
};
#endif