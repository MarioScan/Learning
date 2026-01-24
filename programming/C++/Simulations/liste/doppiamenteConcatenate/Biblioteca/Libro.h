#ifndef LIBRO_H
#define LIBRO_H
using namespace std;

#include <iostream>
class Libro
{
    private:
        string titolo;
        string autore;
        int anno;
        const int codice;

        int assign_codice()
        {
            static int assignCode = 100;
            return ++assignCode;
        }

    public:
        Libro() : titolo(""), autore(""), anno(0), codice(assign_codice()) {}
        Libro(const string& title, const string& author, int year) : titolo(title), autore(author), anno(year), codice(assign_codice()) {}
        Libro(const Libro& l) : titolo(l.titolo), autore(l.autore), anno(l.anno), codice(assign_codice()) {}
        ~Libro() {}

        const string& get_titolo() const { return titolo; }
        const string& get_autore() const { return autore; }
        int get_anno() const { return anno; }
        int get_codice() const { return codice; }

        void set_titolo(const string& newTitle) { titolo = newTitle; }
        void set_autore(const string& newAuthor) { autore = newAuthor; }
        void set_anno(int newYear) { anno = newYear; }
        //codice è const -> non modificabile. 

        Libro& operator=(const Libro& l)
        {
            if(this == &l)
                return *this;

            titolo = l.titolo;
            autore = l.autore;
            anno = l.anno;
            //codice è univoco
            return *this;
        }

        friend ostream& operator<<(ostream&, const Libro&);
        virtual void stampa() const 
        {
            cout << *this;
        }
};
ostream& operator<<(ostream& os, const Libro& l)
{
    os << l.get_titolo() << " di " << l.get_autore() << " (" << l.get_anno() << ") - codice: " << l.get_codice();
    return os;    
}

#endif