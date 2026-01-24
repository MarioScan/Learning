/*

    -----------------------
    |   Coda di Pazienti  |
    -----------------------
*/


#include <iostream>
using namespace std;

class Paziente
{
    private:
        int id;
        string nome;
        string condizione;
        bool isRecommended;
    public:
        Paziente(int identificator, const string& name, const string& condition) 
        : id(identificator), nome(name), condizione(condition), isRecommended(false) {}
        Paziente() : id(-1), nome("-1"), condizione("-1"), isRecommended(false) {}
        ~Paziente() { cout << "[DEBUG] Chiamato distruttore Paziente." << endl; }

        int get_id() const { return id; } 
        const string& get_nome() const { return nome; }
        const string& get_condizione() const { return condizione; }

        void set_id(int newId) { id = newId; }
        void set_nome(const string& newNome) { nome = newNome; }
        void set_condizione(const string& newCondizione) { condizione = newCondizione; }

        bool get_isRecommended() const { return isRecommended; }
        void set_isRecommended(bool recommended) { isRecommended = recommended; }

        friend ostream& operator<<(ostream& os, const Paziente& p);
};
ostream& operator<<(ostream& os, const Paziente& p)
{
    os << p.get_id() << " - " << p.get_nome() << " -> " << p.get_condizione() << (p.get_isRecommended() ? " [RACCOMANDATO]" : "") << endl;  
    return os;
}

template <typename T>
class Nodo
{
    private:
        T dato;
        Nodo<T>* next;
        Nodo<T>* prev; //serve per inserimento prioritario
    public:
        Nodo(const T& data) : dato(data), next(nullptr), prev(nullptr) {}

        const T& get_dato() const { return dato; } 
        Nodo<T>* get_next() const { return next; }
        Nodo<T>* get_prev() const { return prev; }
        void set_next(Nodo<T>* newNext) { next = newNext; } 
        void set_prev(Nodo<T>* newPrev) { prev = newPrev; }
};

template <typename T>
class Queue
{
    private: 
        Nodo<T>* front;
        Nodo<T>* rear;
    public:
        Queue() : front(nullptr), rear(nullptr) {}
        ~Queue() { cout << "[DEBUG] Chiamato distruttore Coda." << endl; }

        bool isEmpty()
        {
            return front==nullptr;
        }

        Queue<T>* enqueue(const T& nuovoDato)
        {
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(isEmpty())
            {
                front = rear = nuovo;
                return this;
            }

            rear->set_next(nuovo);
            nuovo->set_prev(rear);
            rear = nuovo;  
            return this;  
        }

        T dequeue()
        {
            if(isEmpty())
                return T();
            Nodo<T>* temp = front;
            front = front->get_next();
            
            if(front == nullptr)
                front = rear = nullptr;

            T dato = temp->get_dato();
            delete temp;

            return dato;
        }

        void swapNodes(Nodo<T>* A, Nodo<T>* B)
        {
            //1 -- Salvo puntatori agli altri nodi
            Nodo<T>* prev = A->get_prev();
            Nodo<T>* next = B->get_next();
            
            //2 -- Scambio i puntatori
            B->set_prev(prev);
            A->set_next(next); 
            //3 -- Connetto i due nodi
            B->set_next(A);
            A->set_prev(B);
            //4 -- Connetto i nodi adiacenti
            if(prev != nullptr)
                B->get_prev()->set_next(B); //prima 'P' puntava ad A
            else front = B; //se non c'è nulla prima (prev) allora B diventa il nuovo front

            if(A->get_next() != nullptr)
                A->get_next()->set_prev(A); //prima 'D' puntava a B
            else rear = A; //se non c'è nulla dopo (next) allora A diventa rear 
        }

        Queue<T>* enqueuePriority(const T& nuovoDato) 
        {
            enqueue(nuovoDato);
            rear->get_dato()->set_isRecommended(true);
            //Inserimento in fondo e termina se la coda ha solo un elemento
            if(front==rear)
                return this;

            /*  Superiamo  */
            Nodo<T>* vip = rear;
            Nodo<T>* prev = vip->get_prev();
           
            const int maxAdvance = 3;
            for (int i=0; i < maxAdvance && prev != nullptr; i++) 
            {
                Nodo<T>* temp;
                if(prev->get_dato()->get_isRecommended() == false) //paziente prima di vip non è vip
                {
                    swapNodes(prev,vip); //allora scambiali, vip lo supera
                    prev = vip->get_prev(); //avanza puntatore, vip adesso adocchia il paziente successivo a quello superato
                }
                else break; //paziente davanti è anch'esso vip... niente sorpasso
            }
            return this;
        }

        void stampa()
        {
            Nodo<T>* current = front;
            while(current != nullptr)
            {
                cout << *(current->get_dato());
                current = current->get_next();
            }
        }        
};

int main()
{
    /*
    1) Queue<Paziente*>* coda = new Queue<Paziente*>();
        Queue<Paziente*> sto creando una coda di puntatori a Paziente,
        *coda -> sto creando la coda dinamicamente sullo heap 
        Richiede delete coda 

    2) Queue<Paziente>* coda = new Queue<Paziente>();
        Coda di oggetti Paziente, non puntatori
        Ogni oggetto viene copiato all'interno della coda
        distruggere un singolo elemento comporta la distruzione dell'intero oggetto,
        non solo il puntatore.
        La coda è ancora dinamica, non permette il polimorfismo:
        -> perdiamo informazione del derivato
    */

    Queue<Paziente*>* coda = new Queue<Paziente*>(); 
    coda->enqueue(new Paziente(1,"Gianni Rana","Trapianto al cuore"))
    ->enqueue(new Paziente(2,"Armando Commando","Pronto soccorso"))
    ->enqueuePriority(new Paziente(3,"Luca Bianchi", "Gonorrea"))
    ->enqueue(new Paziente(4,"Mario Rossi", "Emorroidi emorragiche"))
    ->enqueue(new Paziente(5,"Fabio Montagna","TAC"))
    ->enqueuePriority(new Paziente(6,"Bello figo","Lobotomia"));

    coda->stampa();

    return 0;
}