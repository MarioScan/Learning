#include <iostream>
using namespace std;



class Persona 
{
    private:
        string nome;
        string cognome;

    public:
        Persona(const string& name="", const string& surname="") : nome(name), cognome(surname) {}
        ~Persona() { cout << "[DEBUG] Distruttore Persona chiamato." << endl; } //non è necessario perché non sto scrivendo nulla ma voglio visualizzarlo
        
        const string& get_nome() const { return nome; }
        const string& get_cognome() const { return cognome; }

        void set_nome(const string& new_name) { nome = new_name; }
        void set_cognome(const string& new_surname) { cognome = new_surname; }

        virtual void stampa() const
        {
            cout << "Nome completo: " << nome << " " << cognome; 
        }
};

class Paziente : public Persona
{
    private: 
        int codicePaziente;
        string diagnosi;

        int assign_id()
        {
            static int ID_paziente = 0;
            return ID_paziente++;
        }

    public:
        Paziente(const string& name="", const string& surname="", const string& diagnosis="") : Persona(name,surname) , codicePaziente(assign_id()), diagnosi(diagnosis) {}
        ~Paziente() { cout << "[DEBUG] Distruttore Paziente chiamato." << endl; } 

        const string& get_diagnosi() const { return diagnosi; }
        int get_codicePaziente() const { return codicePaziente; }

        void set_diagnosi(const string& new_diagnosi) { diagnosi = new_diagnosi; }

        void stampa() const override 
        {
            cout << "Scheda Paziente n°" << codicePaziente << endl;
            Persona::stampa();
            cout << "\nDiagnosi: " << diagnosi << endl;
        }
};

template <typename T>
class Nodo
{
    private:
        T data; 
        Nodo<T>* next;
    public:
        Nodo(const T& dato) : data(dato), next(nullptr) {}

        const T& get_data() const { return data; }
        Nodo<T>* get_next() const { return next; }

        void set_next(Nodo<T>* new_next) { next = new_next; }
};

template <typename T>
class ListaPazienti
{
    private:
        Nodo<T>* head;
    public:
        ListaPazienti() : head(nullptr) {}
        
        //tutti i metodi del nostro programma

        bool isEmpty()
        {
            return head==nullptr; 
        }

        void inserisciPazienti(const T& nuovoDato)
        {
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(!nuovo)
            {
                cerr << "[! ERRORE !]: Impossibile creare nuovo nodo." << endl;
                exit(1);
            }

            if(isEmpty())
            {
                head = nuovo;
                return;
            }

            //inserimento dal fondo:
            Nodo<T>* current = head->get_next();
            Nodo<T>* prev = head;
            while(current!=nullptr) //scorro fino alla fine della lista
            {
                prev = current; //va avanti di uno
                current = current->get_next(); //va avanti di uno
            }

            prev->set_next(nuovo);
            nuovo->set_next(nullptr);
        }

        bool svuotaLista()
        {
            bool flag = false;

            while(!isEmpty())
            {
                Nodo<T>* temp = head;
                head = head->get_next();
                delete temp;
            }

            return true; //se arriva fino a return vuol dire che non è andato in crash :p
        }

        void rimuoviPazientiConDiagnosi(const string& keyDiagnosi)
        {
            cout << "[Rimozione pazienti con diagnosi: " << keyDiagnosi << "]\n" << endl;
            Nodo<T>* current = head->get_next(); // [] [X] [] []
            Nodo<T>* prev = head; // [X] [] [] []
            while(current)
            {
                if(current->get_data()->get_diagnosi() == keyDiagnosi)
                {
                    prev->set_next(current->get_next()); //connette precedente a successivo di current --> [a] [] [b] []
                    Nodo<T>* temp = current; 
                    current = current->get_next(); //[] [old] [new] []
                    delete temp;            
                }
                else //vado avanti
                {
                    prev = current;
                    current = current->get_next(); 
                }
            } 
        }

        void stampaTutti() const
        {
            Nodo<T>* current = head;
            while(current!=nullptr)
            {
                current->get_data()->stampa();
                cout << endl;
                current = current->get_next();
            }
        }

        ~ListaPazienti() 
        { 
            cout << "[DEBUG] Chiamato distruttore ListaPazienti." << endl; 
            this->svuotaLista();
        }
};

int main()
{
    ListaPazienti<Paziente*>* lista = new ListaPazienti<Paziente*>();
    
    lista->inserisciPazienti(new Paziente("Mario", "Rossi", "Frattura"));
    lista->inserisciPazienti(new Paziente("Anna", "Verdi", "Influenzato"));
    lista->inserisciPazienti(new Paziente("Luca", "Bianchi", "Covid"));
    lista->inserisciPazienti(new Paziente("Sara", "Neri", "Influenzato"));

    lista->stampaTutti();
    lista->rimuoviPazientiConDiagnosi("Influenzato");
    lista->stampaTutti();

    delete lista;
    return 0;
}