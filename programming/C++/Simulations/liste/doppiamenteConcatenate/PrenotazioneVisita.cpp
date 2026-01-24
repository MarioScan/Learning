#include <iostream>
using namespace std;

class Persona
{
    private:
        string nome;
        string cognome;
    public:
        Persona(const string& name, const string& surname) : nome(name), cognome(surname) {}
        ~Persona() { cout << "[DEBUG]: Chiamato distruttore Persona." << endl; } //inutile, creato solo per visualizzare la distruzione

        const string& get_nome() const { return nome; }
        const string& get_cognome() const { return cognome; }

        void set_nome(const string& newNome) { nome = newNome; }
        void set_cognome(const string& newCog) { cognome = newCog; }

        virtual void stampa() const 
        {
            cout << "Nome: " << nome << "; Cognome: " << cognome << "." << endl; 
        }
};

class Paziente : public Persona
{
    private: 
        int codicePaziente;

        int assign_id()
        {
            static int ID = 1;
            return ID++;
        }

    public:
        Paziente(const string& name, const string& surname) : Persona(name,surname), codicePaziente(assign_id()) {}
        ~Paziente() { cout << "[DEBUG]: Chiamato distruttore Paziente." << endl; } //anch'esso inutile, solo visualizzazione distruzione

        int get_codicePaziente() const { return codicePaziente; }

        void stampa() const override
        {
            cout << "Paziente nº" << codicePaziente << ":" << endl;
            Persona::stampa();
        }
};

class Prenotazione
{
    private:
        Paziente* paz;
        string data;
        string orario;
    public:
        Prenotazione(Paziente* patient, const string& date, const string time) : paz(patient), data(date), orario(time) {}
        ~Prenotazione() { cout << "[DEBUG]: Chiamato distruttore Prenotazione." << endl; delete paz; }

        Paziente* get_paziente() const { return paz; }
        const string& get_data() const { return data; }
        const string& get_orario() const { return orario; }

        void set_paziente(Paziente* newPaziente) { paz = newPaziente; }
        void set_data(const string& newData) { data = newData; } 

        friend ostream& operator<<(ostream&, Prenotazione*);

        void stampa() const 
        {
            cout << this;
        }
};

ostream& operator<<(ostream& os, Prenotazione* prenotaz)
{
    cout << "Prenotazione giorno: " << prenotaz->get_data() << " ore: " << prenotaz->get_orario() << endl;
    prenotaz->get_paziente()->stampa();
    return os; 
}

template <typename T>
class Nodo
{
    private: 
        T dato;
        Nodo<T>* next;
        Nodo<T>* prev;
    public:
        Nodo(const T& data) : dato(data), next(nullptr), prev(nullptr) {}
        ~Nodo() { cout << "[DEBUG]: Chiamato distruttore Nodo." << endl; }

        const T& get_dato() const { return dato; }
        Nodo<T>* get_next() const { return next; }
        Nodo<T>* get_prev() const { return prev; }
        
        void set_next(Nodo<T>* new_next) { next = new_next; }
        void set_prev(Nodo<T>* new_prev) { prev = new_prev; }
};

template <typename T>
class Lista
{
    private:
        Nodo<T>* head;
        Nodo<T>* tail;
    public:
        Lista() : head(nullptr), tail(nullptr) {}
        
        bool isEmpty()
        {
            return head==nullptr;
        }

        Lista<T>* insert(const T& nuovoDato) //Inserimento in coda
        {
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(!nuovo)
            {
                cerr << "Impossibile creare nuovo nodo." << endl;
                exit(1);
            }
            nuovo->set_next(nullptr);

            if(isEmpty())
            {
                head = tail = nuovo;
                return this;
            }

            nuovo->set_prev(tail);
            tail->set_next(nuovo);
            tail = nuovo;
            
            return this;
        }

        bool removeAll()
        {
            while(head)
            {
                Nodo<T>* temp = head;
                head = head->get_next();
                delete temp;
            }
            tail = head; //nullptr
            if(tail!=nullptr || head !=nullptr)
            {
                return false; //removeAll fallita
            }
            return true; //successo
        }

        bool removeSurname(const string& key)
        { //head -> prenotazione -> paziente -> vedi cognome == key ? 
            Nodo<T>* current = nullptr; 
            if(head && head->get_dato()->get_paziente()->get_cognome() == key)
            {
                Nodo<T>* temp = head;
                head = head->get_next();
                current = head;
                if (head)
                    head->set_prev(nullptr);
                else
                    tail = nullptr; // la lista è vuota 
                delete temp;
            }
            else current = head->get_next(); //blocco if non utilizzato, aggiorno qui perché abbiamo già controllato questo nodo (head)
            
            while(current!=nullptr)
            {
                Nodo<T>* prev = current->get_prev();
                Nodo<T>* next = current->get_next();

                if(current->get_dato()->get_paziente()->get_cognome() == key)
                {
                    //prendo il precedente e lo connetto al successivo
                    if(prev) 
                        prev->set_next(next); //non sono all'inizio
                    else head = next; //sono all'inizio
                    
                    if(next) 
                        next->set_prev(prev); //non sono alla fine
                    else tail = prev; //sono alla fine 

                    delete current;
                }
                current = next; //se non ho nulla da eliminare continuo a scorrere
            }
            return true; //remove con chiave ha avuto successo, non importa se sono stati eliminati elementi o meno
        }

        ~Lista() 
        { 
            //svuota elementi uno ad uno:
            removeAll();
            cout << "[DEBUG]: Chiamato distruttore Lista." << endl; 
        }

        void stampa() const 
        {
            cout << "Lista prenotazioni:" << endl;
            if(!head)
            {
                cout << "lista vuota!" << endl;
                return;
            }
            Nodo<T>* current = head;
            while(current!=nullptr)
            {
                cout << current->get_dato() << endl;
                current = current->get_next();
            }
        }
};

int main()
{
    Lista<Prenotazione*>* miaLista = new Lista<Prenotazione*>();
    miaLista->insert(new Prenotazione(new Paziente("Mario","Rossi"),"05/08/2025","09:00"))
    ->insert(new Prenotazione(new Paziente("Anna","Verdi"),"05/08/2025","10:15"))
    ->insert(new Prenotazione(new Paziente("Gianni","Neri"),"05/08/2025","11:30"))
    ->insert(new Prenotazione(new Paziente("Marco","Neri"),"06/08/2025","10:00"))
    ->insert(new Prenotazione(new Paziente("Giacomo","Rossi"),"07/08/2025","17:30"));

    miaLista->stampa(); //OK

    string key = "Rossi";
    cout << "\nRimozione cognome \"" << key << "\":\n" << (((miaLista->removeSurname(key)) == true) ? "Avvenuta con successo." : "Operazione fallita.") << endl;
    
    cout << endl; 
    miaLista->stampa();

    string key2 = "Verdi";
    cout << "\nRimozione cognome \"" << key2 << "\":\n" << (((miaLista->removeSurname(key2)) == true) ? "Avvenuta con successo." : "Operazione fallita.") << endl;
    
    cout << endl; 
    miaLista->stampa();

    string key3 = "Neri";
    cout << "\nRimozione cognome \"" << key3 << "\":\n" << (((miaLista->removeSurname(key3)) == true) ? "Avvenuta con successo." : "Operazione fallita.") << endl;
 

    cout << endl; 
    miaLista->stampa();

    return 0;
}