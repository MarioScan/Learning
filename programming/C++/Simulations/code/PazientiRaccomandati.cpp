#include <iostream>
using namespace std;

class Patient
{
    private:
        string name; //si presume che il nome sia completo di nome + cognome
        string condition;
        int id;
        bool priority;

        int assign_id()
        {
            static int giveID = 1001;
            return giveID++;
        }
    
        public:
            Patient(const string& nome, const string& condizione, bool prioritario=false) 
            : name(nome), condition(condizione), id(assign_id()), priority(prioritario) {}
            
            const string& get_name() const { return name; }
            const string& get_condition() const { return condition; }
            int get_id() const { return id; }
            bool get_priority() const { return priority; }

            void set_name(const string& newName) { name = newName; }
            void set_condition(const string& newCondition) { condition = newCondition; }
            //si presume non si possa cambiare l'ID in quanto univoco.
            void set_priority(bool newPriority) { priority = newPriority; }
            
            friend ostream& operator<<(ostream&,const Patient&);

            void stampa()
            {
                cout << *this;
            }
};

ostream& operator<<(ostream& os,const Patient& p)
{
    os << "Paziente n." << p.get_id() << " - " << p.get_name() << "  [";
    if(p.get_priority() == true)
        cout << " PRIORITARIO]" << endl;
    else cout << "Ordinario]" << endl;
    return os;
}

template <typename T>
class Nodo
{
    private:
        T data;
        Nodo<T>* next;
    public:
        Nodo(const T& dato) : data(dato), next(nullptr) {}
        ~Nodo() { cout << "[DEBUG]: Chiamato distruttore Nodo." << endl; }

        const T& get_data() const { return data; }
        Nodo<T>* get_next() const { return next; }
        void set_next(Nodo<T>* newNext) { next = newNext; }
};

template <typename T>
class Queue
{
    private: 
        Nodo<T>* front; 
        Nodo<T>* rear; 
    public:
        Queue() : front(nullptr), rear(nullptr) {}

        bool isEmpty()
        {
            return front==nullptr;
        }

        Queue<T>* enqueue(const T& nuovoDato)
        {
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(!nuovo)
            {
                cerr << "[DEBUG]: Error unable to create a new node." << endl;
                exit(1);
            }

            if(isEmpty())
            {
                front = rear = nuovo;
                return this;
            }

            //inserimento in coda
            rear->set_next(nuovo);
            rear = nuovo;
            return this;
        }

        void dequeue()
        {
            if(isEmpty())
            {
                return;
            }

            Nodo<T>* trash = front;
            delete trash->get_data();
            front = front->get_next();
            delete trash;
        }

        Queue<T>* recommendedEnqueue(const T& nuovoDato)
        {
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(!nuovo)
            {
                cerr << "[DEBUG]: Error unable to create a new node." << endl;
                exit(1);
            }

            if(isEmpty())
            {
                front = rear = nuovo;
                return this;
            }

            /* ----- Inserimento speciale ----- */

        Nodo<T>* current = front;
        Nodo<T> *before1 = nullptr, *before2 = nullptr, *before3 = nullptr, *before4 = nullptr; 
        int count=0;
        while (current && current->get_next() != nullptr)
        {

            if(count==0) 
            {
                before1 = current;
                count++;
            }
            else if(count==1)
            {
                before2 = before1;
                before1 = current;
                count++;
            }
            else if(count==2)
            {
                before3 = before2;
                before2 = before1;
                before1 = current;
                count++;
            }
            else
            {
                before4 = before3;
                before3 = before2;
                before2 = before1;
                before1 = current; 
                count++;
            }

            if(current->get_next() != nullptr)
                current = current->get_next();
        }

        //inserisco dato nella coda, vediamo quanti pazienti sorpassa (max 3):
        enqueue(nuovoDato);

        // [] [...] [before4] [before3] [before2] [before1] [current] --> rimane tale se before1 è prioritario
        if(current && current->get_data()) //controllo se tutto ok 
        {
            if(before1 && before1->get_data()->get_priority() == false) //sorpassiamo before1 --> // [] [...] [before4] [before3] [before2] [current] [before1] 
            {
                if(before2 && before2->get_data()->get_priority() == false) //sorpassiamo before2 // [] [...] [before4] [before3] [current] [before2] [before1] 
                {
                    if(before3 && before3->get_data()->get_priority() == false) //sorpassiamo before3 // [] [...] [before4] [before3] [before2] [before1] [current] 
                    {
                        if(before4)
                            before4->set_next(current);
                        before3->set_next(before2);
                        before2->set_next(before1);
                        before1->set_next(nullptr);
                        rear = before1;
                    }
                    else
                    {
                        before3->set_next(current);
                        current->set_next(before2);
                        before2->set_next(before1);
                        before1->set_next(nullptr);
                        rear = before1;
                    }
                }
                else 
                {
                    before2->set_next(current);
                    current->set_next(before1);
                    before1->set_next(nullptr);
                    rear = before1;
                }
            }
            //else{}  //altrimenti rimane in fondo, il successivo è anch'esso prioritario :/
        } 
        return this;
    }


        ~Queue() 
        {
            cout << "[DEBUG]: Chiamato distruttore Queue." << endl;
            while(!isEmpty())
                dequeue();
            front = rear = nullptr;
        }
};

int main()
{
    Queue<Patient*>* pazienti = new Queue<Patient*>();
    pazienti->
    enqueue(new Patient("Gianni Rana", "Trapianto al cuore"))
    ->enqueue(new Patient("Armando Commando", "Pronto soccorso"))
    ->recommendedEnqueue(new Patient("Luca Bianchi", "Gonorrea"))
    ->enqueue(new Patient("Mario Rossi", "Emorroidi emorragiche"))
    ->enqueue(new Patient("Fabio Montagna", "TAC"));
    
    return 0;
}