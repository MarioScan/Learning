/*
Si richiede la progettazione di un sistema per la gestione di una biblioteca universitaria che fornisce in prestito libri e dvd a studenti e docenti.
* Si Implementi la classe "Item" (Prodotto), contenente almeno gli attributi "titte",
"publicationDate" e "Id".
* Si implementi la classe "Book" (Libro), derivata da "Item", contenente almeno l'attributo "author"
* Si implementi la classe "DVD" (dvd), sottoclasse di "Item", contenente almeno l'attributo "duration"
* Si implementi la classe "Student" (Studente) e "Professor" (Docente), contenente almeno gli attributi "name" e "surname". Inoltre, si implementi il metodo
"printitems" che mostri a schermo tutti i prodotti presi in prestito dal docente o dallo
studente nel formato:
* "Book - title -author - id" per i libri e
* "DVD - title - duration - id" per i dvd.

* Si Implementi la classe "Library" (Biblioteca), caratterizzata almeno dall'attributo
"name" e contenente almeno i metodi "borrowitem", che realizza la logica di prestito di un prodotto ad uno studente o docente. a "returnitem", che realizza la logica di restituzione di un prodotto.
La classe dovrà memorizzare studenti e docenti in uno o più array. Studenti e docenti saranno identificati attraverso l'indice dell'array.

Inoltre:
ogni studente può prendere in prestito al più 5 prodotti; ogni docente può prendere in prestito al più 10 prodotti;
* Si PUO utilizzare una coda al posto degli array.
* Si implementi un metodo "main" che crei manualmente qualche studente, docente e prodotto, Inoltre, il metodo deve mostrare
io come si presta qualche prodotto a docenti e studenti;
come si restituisce qualche prodotto:
come non sia possibile prestare più prodotti del dovuto;
tutti prodotti ancora in prestito ai docenti e studenti creati:
Utilizzare un solo file chiamato "main.cpp"
*/

#include <iostream>
#include <vector>
using namespace std;

class Item
{
    string title;
    int publicationDate; //format YYYY-MM-DD
    int id;

    int assign_id()
    {
        static int giveID = 10;
        return ++giveID;
    }

    public:
        Item(const string& t, int pub) : title(t), publicationDate(pub), id(assign_id()) {}
        ~Item() {}

        const string& get_title() const { return title; }
        int get_publicationDate() const { return publicationDate; }
        int get_id() const { return id; }
        
        virtual void print() const = 0;
};

class Book : public Item
{
    private:
        string author;
    public:
        Book(const string& title, const string& autore, int publicationDate)
        : Item(title, publicationDate), author(autore) {}
        ~Book() {}

        const string& get_author() const { return author; }

        void print() const override
        {
            cout << "Book - " << get_title() << " - " << author << " - " << get_id();
        }
};

class DVD : public Item
{
    private:
        int duration;
    public:
        DVD(const string& title, int durata, int publicationDate) : Item(title, publicationDate), duration(durata) {}
        ~DVD() {}

        int get_duration() const { return duration; }

        void print() const override
        {
            cout << "DVD - " << get_title() << " - " << duration << " - " << get_id();
        }
};

class Persona
{
    private:
        string name;
        string surname;
        vector<Item*> lista;
        int maxItems;

        bool isFull() { return lista.size() >= maxItems; }
    public:
        Persona(const string& nome, const string& cognome, int maxN) : name(nome), surname(cognome), maxItems(maxN) {}
        ~Persona() {}

        const string& get_name() const { return name; }
        const string& get_surname() const { return surname; }

        void stampaDatiUtente() const 
        {
            cout << name << " " << surname;
        }

        bool borrowItem(Item* item)
        {
            if(isFull())
            {
                cout << "Massimo numero di prestiti raggiunto!" << endl;
                return false;
            }

            lista.push_back(item);
            return true;
        }

        bool returnItem(int id)
        {
            cout << "Restituzione del libro con id \"" << id << "\":";
            for(int i=0;i<lista.size();i++)
            {
                if(lista.at(i)->get_id() == id)
                {
                    lista.erase(lista.begin() + i); //indico posizione a partire da 0 + i ;
                    return true;
                }
            }
            return false;
        }

        void printItems() const 
        {
            for(int i=0; i<lista.size(); i++)
            {
                lista.at(i)->print();
                cout << endl;
            }
        }
};

class Student : public Persona
{
    public:
        Student(const string& nome, const string& cognome) : Persona(nome, cognome, 5) {}
        ~Student() {}
};

class Professor : public Persona
{
    public:
        Professor(const string& nome, const string& cognome) : Persona(nome, cognome, 10) {}
        ~Professor() {}
};

class Library
{
    private:
        string name;
        vector<Persona*> lista;
    public:
        Library(const string& nome) : name(nome) {}
        
        bool isEmpty() { return lista.size() <= 0; }

        bool addUser(Persona* p)
        {
            for(int i=0; i<lista.size(); i++)
            {
                if(lista.at(i) == p)
                {
                    cout << "Persona gia' presente nella lista." << endl;
                    return false;
                }
            }
            lista.push_back(p);
            return true;
        }

        bool borrowItem(int idPersona, Item* item)
        {
            if(idPersona < 0 || idPersona >= lista.size())
            {

            }

            lista.at(idPersona)->borrowItem(item);
                return true;
        }

        void returnItem(int idPersona, int idItem)
        {
            if(idPersona < 0 || idPersona >= lista.size())
            {
                cout << "Indice array non valido." << endl;
                return;
            }

            if(lista.at(idPersona)->returnItem(idItem))
                    cout << " Libro restituito."; 
                else cout << " Libro non trovato.";
            cout << endl;
        }

        void printBorrows(int idPersona)
        {
            if(idPersona < 0 || idPersona >= lista.size())
            {
                cout << "Indice array non valido." << endl;
                return;
            }

            lista.at(idPersona)->printItems();
        }

        void printAll()
        {
            cout << "Stampa ogni lista di libri presi in prestito di ogni utente:" << endl;
            for(int i=0;i<lista.size();i++)
            {
                lista.at(i)->stampaDatiUtente(); 
                cout << ":" << endl;
                lista.at(i)->printItems();
                cout << endl;
            }
        }
        
        
        ~Library() { if(isEmpty()) return; else lista.clear(); }
};


int main()
{
    Book b1("The Witcher 1", "Andrej Sapkowski", 1992);
    Book b2("Game of Thrones", "George R.R. Martin", 1980);
    Book b3("Flames and swords", "Andrej Sapkowski", 1993);
    Book b4("The guardian of innocents", "Andrej Sapkowski", 1993);
    Book b5("The Lady of the Lake", "Andrej Sapkowski", 1993);
    Book b6("A matter of Destiny", "John Baldo", 1980);

    DVD d1("Shrek", 150, 1990);
    DVD d2("Bollywood Return", 240, 1980);
    DVD d3("God of War the Movie", 180, 2025);
    DVD d4("The song of the Ocean", 200, 2020);
    DVD d5("Angels and Demons", 210, 1978);

    Student s1("Mario", "Rossi");
    Student s2("Luigi", "Verdi");

    Professor p1("Matteo", "Marroni");
    Professor p2("Giada", "Green");

    Library l("Libreria catanese");
    l.addUser(&s1); //0
    l.addUser(&s2); //1
    l.addUser(&p1); //2
    l.addUser(&p2); //3

    l.borrowItem(0, &b1); //id 11 
    l.borrowItem(0, &b2); //id 12 
    l.borrowItem(1, &b3);
    l.borrowItem(1, &b4);
    l.borrowItem(2, &b5);
    l.borrowItem(2, &b6); //id 16 ...
    l.borrowItem(3, &d1);
    l.borrowItem(3, &d2);
    l.borrowItem(0, &d3);
    l.borrowItem(1, &d4);
    l.borrowItem(2, &d5); //id 21 

    l.printAll();

    cout << "-----------" << endl;

    l.returnItem(0, 12);
    l.returnItem(0, 13);
    l.returnItem(1, 13);
    l.returnItem(2, 16);
    l.returnItem(3, 18);

    cout << "-----------" << endl;

    l.printAll();
    
    return 0;
}