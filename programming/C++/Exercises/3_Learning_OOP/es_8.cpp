/*  
    -----------------
    |   ESERCIZIO   |
    -----------------

🛑 Obiettivo:
1) Definisci una classe Libro che rappresenta un libro. La classe deve avere:
string titolo
string autore
int anno

Implementa:

2) Costruttore di default e parametrico

3) Metodi set e get per tutti gli attributi

4) Un metodo stampaScheda() che stampa le info del libro

----------------
Output atteso:

Titolo: Il Nome della Rosa
Autore: Umberto Eco
Anno: 1980
----------------
*/

#include <iostream>
using namespace std;

class Libro
{
    private:
        string titolo;
        string autore;
        int anno;
    public:
        Libro(string title, string author, int year) : titolo(title), autore(author), anno(year) {} 
        Libro() { titolo = "Sconosciuto", autore = "Sconosciuto", anno = -1; }
        ~Libro() { cout << "Distruttore chiamato, memoria liberata." << endl; }

        //getters
        string getTitolo() const { return titolo; }
        string getAutore() const { return autore; }
        int getAnno() const { return anno; }

        //setters
        void setTitolo(string newTitle) { titolo = newTitle; }
        void setAutore(string newAuthor) { autore = newAuthor; } 
        void setAnno(int newYear) { anno = newYear; } 

        //metodo interno alla classe
        void stampaScheda() 
        {
            cout << "Titolo: " << titolo << "\nAutore: " << autore << "\nAnno: " << anno << endl;
        }
};


int main()
{
    Libro l1("Il nome della rosa","Umberto Eco",1980);
    l1.stampaScheda();

    return 0;
}

