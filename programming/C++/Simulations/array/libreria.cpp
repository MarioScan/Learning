#include <iostream>
#include <vector>
using namespace std;

class Item
{
    private:
        string title;
        int publication_year;
        int id;

        int assign_id()
        {
            static int id_assigner=100;
            return ++id_assigner;
        }
        public:
            Item(const string titolo, int annoPub) : title(titolo), publication_year(annoPub), id(assign_id()) {}
            ~Item() {}

            const string& get_title() const { return title; }
            int get_publication_year() const { return publication_year; }
            int get_id() const { return id; }

            virtual void print() const = 0; //metodo astratto
            /* Stampa:
                BOOK - ID - Autore - Titolo ; 
                DVD - ID - Titolo - Durata; 
            */
};

class Book : public Item
{
    private:
        string author;
    public: 
        Book(const string& title, int publicationDate, const string& autore) : Item(title, publicationDate), author(autore) {}
        ~Book() {}

        const string& get_author() const { return author; }

        void print() const override
        {
            cout << "Book - " << get_id() << " - " << author << " - " << get_title();
        }
};

class DVD : public Item
{
    private:
        int length; //in minuti
    public:
        DVD(const string& title, int publicationDate, int durata) : Item(title, publicationDate), length(durata) {}
        ~DVD() {}

        int get_length() const { return length; }

        void print() const override
        {
            cout << "DVD - " << get_id() << " - " << get_title() << " - " << length;
        }
};

//====================================================================================================================================

class Persona
{
    private:
        string name;
        string surname;
        vector<Item*> items;
        int maxItems;
    public:
        Persona(const string& nome, const string& cognome, int max) : name(nome), surname(cognome), maxItems(max) {}
        ~Persona() {}

        const string& get_name() const { return name; }
        const string& get_surname() const { return surname; }
        
        bool borrowItem(Item* item) 
        {
            if(items.size() >= maxItems)
            {
                cout << "Limite raggiunto di items: " << items.size() << " su " << maxItems;
                return false;
            } 
            items.push_back(item);
            return true; //successo
        }

        bool returnItem(int id) //per id
        {
            for(int i=0; i< items.size(); i++)
            {
                if(items.at(i)->get_id() == id)
                {
                    items.erase(items.begin() + i);
                    return true;
                }
            }
            return false; //non trovato
        }

        void printItems()
        {
            cout << "\nOggetti presi in prestito da " << name << " " << surname << ":" << endl; 
            for(int i=0; i< items.size(); i++)
            {
                items.at(i)->print();
                cout << endl;
            }
        }
};

class Studente : public Persona
{
    public:
        Studente(const string& nome, const string& cognome) : Persona(nome, cognome, 5) {}
        ~Studente() {}
};

class Docente : public Persona
{
    public:
        Docente(const string& nome, const string& cognome) : Persona(nome, cognome, 10) {}
        ~Docente() {}
};

//====================================================================================================================================

class Library
{
    private:
        const string& library_name;
        vector<Persona*> persone;
    public:
        Library(const string& nome) : library_name(nome) {}
        
        const string& get_library_name() const { return library_name; }

        bool isEmpty() 
        {
            return persone.size() == 0;
        }

        void clearAll()
        {
            if(isEmpty())
                return;
            persone.clear();
        }

        void addUser(Persona* p)
        {
            for(int i=0; i< persone.size(); i++)
            {
                if(persone.at(i) == p) //confronto indirizzi
                {
                    cout << "Utente gia' esistente!" << endl;
                    return;
                }
            }
            persone.push_back(p);
        }

        void borrowItem(int idPersona, Item* item)
        {
            bool check=false;
            if(idPersona < 0 || idPersona >= persone.size())
            {
                cout << "Id non valido." << endl;
                return;
            }
            persone.at(idPersona)->borrowItem(item);
        }

        void returnItem(int idPersona, int idItem)
        {
            if(idPersona < 0 || idPersona >= persone.size())
            {
                cout << "Id non valido." << endl;
                return;
            }
            persone.at(idPersona)->returnItem(idItem);
        }

        void printUserBorrows(int idPersona) const
        {
            if(idPersona < 0 || idPersona >= persone.size())
            {
                cout << "Id non valido." << endl;
                return;
            }
            persone.at(idPersona)->printItems();
        }

        void printAll() const
        {
            cout << "Stampa tutti i libri in prestito della Libreria:" << endl;
            for(int i=0; i< persone.size(); i++)
            {
                persone.at(i)->printItems();
            }
        }
        
        ~Library() { clearAll(); }
};

//====================================================================================================================================


int main() 
{
    //1 

    Book b1("The Witcher", 1989, "Andrej Sapkowski");
    Book b2("Art of War", 168, "Sun Tzu");
    Book b3("Game of Thrones", 1988, "George Martin");
    Book b4("The Witcher", 1989, "Andrej Sapkowski");
    Book b5("Game of Thrones", 1988, "George Martin");

    DVD d1("Superman", 2015, 120);
    DVD d2("Avengers", 2004, 200);
    DVD d3("Batman", 2012, 150);
    DVD d4("Lord of the Ring", 2002, 160);

    /*
    b1.print(); cout << endl;
    b4.print(); cout << endl;
    d2.print(); cout << endl;
    d3.print(); cout << endl;*/

    //2 
    Studente p1("Mario", "Rossi");
    Studente p2("Luigi", "Verdi");
    Docente p3("Gianna", "Gialli");
    Docente p4("Emma","Marroni");

    /*
    p1.borrowItem(&b1);
    p1.borrowItem(&b2);
    p1.borrowItem(&d1);
    p2.borrowItem(&b3);
    p2.borrowItem(&d2);
    p3.borrowItem(&d3);
    p3.borrowItem(&d4);
    p4.borrowItem(&b4);
    p4.borrowItem(&b5);

    p1.printItems();
    p2.printItems();
    p3.printItems();
    p4.printItems();*/

    //3
    Library l("Libreria studentesca");
    l.addUser(&p1); //0
    l.addUser(&p2); //1
    l.addUser(&p3); //2
    l.addUser(&p4); //3

    l.borrowItem(0,&b1);
    l.borrowItem(0,&b2);
    l.borrowItem(0,&b3);
    l.borrowItem(1,&b4);
    l.borrowItem(1,&d1);
    l.borrowItem(2,&b5);
    l.borrowItem(2,&d2);
    l.borrowItem(3,&d3);
    l.borrowItem(3,&d4);

    
    l.printAll();

    cout << "\n" << endl;
    l.printUserBorrows(0);

    l.returnItem(0,101);
    l.returnItem(0,102);

    l.printUserBorrows(0);
    return 0;
}