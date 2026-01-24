#include <iostream>
using namespace std;

class Studente
{
    private:
        string nome;
        string cognome;
        double media;
        int matricola;
    
        int assign_matricola()
        {
            static int assignMat = 1001;
            return assignMat++;
        }

    public:
        Studente(const string& name, const string& surname, double avg) : nome(name), cognome(surname), media(avg), matricola(assign_matricola()) {}
        ~Studente() { cout << "[DEBUG]: Chiamato distruttore Studente." << endl; }

        const string& get_nome() const { return nome; }
        const string& get_cognome() const { return cognome; }
        double get_media() const { return media; }
        int get_matricola() const { return matricola; }

        void set_nome(const string& newName) { nome = newName; }
        void set_cognome(const string& newSurname) { cognome = newSurname; }
        void set_media(double newAvg)  { media = newAvg; }

        friend ostream& operator<<(ostream&,const Studente&);
        virtual void stampa() const 
        {
            cout << *this;
        }
};

ostream& operator<<(ostream& os, const Studente& stud)
{
    os << stud.get_matricola() << ": " << stud.get_nome() << " " << stud.get_cognome() << " - " << stud.get_media();
    return os;
}

class BorsaDiStudio
{
    private:
        int importo;
        int durata;
    public: 
        BorsaDiStudio(int amount, int timespan) : importo(amount), durata(timespan) {}
        ~BorsaDiStudio() { cout << "[DEBUG]: Chiamato distruttore Borsa di studio." << endl; }

        int get_importo() const { return importo; }
        int get_durata() const { return durata; }
        void set_importo(int newImporto) { importo = newImporto; }
        void set_durata(int newDurata) { durata = newDurata; }

        friend ostream& operator<<(ostream&,const BorsaDiStudio&);

        void stampa() const
        {
            cout << *this;
        }
};

ostream& operator<<(ostream& os,const BorsaDiStudio& stipendium)
{
    os << " [borsa di " << stipendium.get_importo() << " euro]"; 
    return os;
}

class StudenteBorsista : public Studente
{
    private:
        BorsaDiStudio* borsa;
    public:
        StudenteBorsista(const string& name, const string& surname, double avg,int amount=0, int timespan=0) : Studente(name,surname,avg) 
        {
            if(amount && amount > 0 && timespan && timespan > 0)
                borsa = new BorsaDiStudio(amount,timespan);
            else borsa = nullptr;
        } 
        ~StudenteBorsista() 
        { 
            cout << "[DEBUG]: Chiamato distruttore StudenteBorsista." << endl; 
            if(borsa)
                delete borsa;
        }

        int get_importo_borsa() const 
        { 
            if(borsa)
                return borsa->get_importo();
            else return 0; 
        }

        int get_durata_borsa() const
        {
            if(borsa)
                return borsa->get_durata();
            else return 0;
        }

        void stampa() const override
        {
            Studente::stampa();
            if(borsa)
                borsa->stampa();
            cout << endl;
        }

};

template <typename T>
class Nodo
{
    private:
        T dato;
        Nodo<T>* next;
    public:
        Nodo(const T& data) : dato(data), next(nullptr) {}

        const T& get_dato() const { return dato; }
        Nodo<T>* get_next() const { return next; }
        void set_next(Nodo<T>* newNext) { next = newNext; }

        ~Nodo() 
        { 
            cout << "[DEBUG]: Chiamato distruttore Nodo." << endl; 
        }
};

template <typename T>
class Queue
{
    private:
        Nodo<T>* front;
        Nodo<T>* rear;
        int size;
        int count=0;
        
        
    public:
        Queue(int dim) : size(dim), front(nullptr), rear(nullptr) {}
        
        bool isEmpty() const
        {
            return front==nullptr;
        }

        bool isFull() const
        {
            return count >= size;
        }
        
        Queue<T>* enqueue(const T& nuovoDato)
        {
            //caso 1: coda piena
            if(isFull())
            {
                cout << "/!\\ Coda piena /!\\\nVerranno presi solo i primi 10 elementi inseriti" << endl;
                return this;
            }

            //caso 2: coda non piena, creazione nodo -> errore
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(!nuovo)
            {
                cerr << "Errore: impossibile creare nuovo nodo.\n";
                exit(1);
            } 

            //caso 3: coda vuota
            if(isEmpty())
            {
                front = rear = nuovo;
                return this;
            }

            //caso 4: tutto ok, procediamo

            //scorro fino alla fine
            Nodo<T>* current = front;
            while(current)
            {
                current = current->get_next();
            }

            rear->set_next(nuovo);
            rear = nuovo; 
            count++;
            return this;
        }

        void dequeue()
        {
            if(isEmpty())
            {
                return;
            }

            Nodo<T>* temp = front;
            delete temp->get_dato();
            
            if(!front->get_next()) //previene accesso non consentito (anti segmentation fault)
                rear = front = nullptr;
            else front = front->get_next();
             
            delete temp;
            count--;
        }

        ~Queue() 
        { 
            cout << "[DEBUG]: Chiamato distruttore Queue." << endl;
            while(!isEmpty())
                dequeue();
            count=0;
        }

        void stampa() const 
        {
            cout << "Stampa lista studenti:" << endl;
            if(isEmpty())
            {
                cout << "/!\\ Coda vuota /!\\" << endl;
                return;
            }

            Nodo<T>* current = front;
            while(current)
            {
                current->get_dato()->stampa();
                StudenteBorsista* studBorsa = dynamic_cast<StudenteBorsista*>(current->get_dato());
                if(!studBorsa)
                    cout << endl;
                current = current->get_next();
            }
        }

        int totaleBorse()
        {
            if(isEmpty())
                return -1;
            
            Nodo<T>* current = front;
            int totale=0;
            while(current)
            {
                StudenteBorsista* studBorsa = dynamic_cast<StudenteBorsista*>(current->get_dato());
                if(studBorsa)
                    totale += studBorsa->get_importo_borsa();
                current = current->get_next();
            }
            return totale;
        }
         
        void removeUndergrade(int grade)
        {
            //caso 1: coda vuota
            if(isEmpty())
            {
                cout << "/!\\ Coda vuota /!\\" << endl;
                return;
            }

            cout << "\n[WARNING]: Rimozione studenti sotto la media di: " << grade << "." << endl;

            //caso 3 - parte 1: controllo se elemento da rimuovere si trova in testa
            bool check = false;
            while(front && front->get_dato()->get_media() < grade)
            {
                //stampa
                check = true;
                front->get_dato()->stampa();
                StudenteBorsista* studBorsa = dynamic_cast<StudenteBorsista*>(front->get_dato());
                if(!studBorsa)
                    cout << endl;
                
                dequeue(); //rimuove front
            }

            //caso 3 - parte 2: controllo il resto della coda 
            Nodo<T>* current = front;
            while(current)
            {
                Nodo<T>* succ = current->get_next();
                if(succ && succ->get_dato()->get_media() < grade)
                {
                    check = true;
                    succ->get_dato()->stampa();
                    StudenteBorsista* studBorsa = dynamic_cast<StudenteBorsista*>(succ->get_dato());
                    if(!studBorsa)
                        cout << endl;

                    current->set_next(succ->get_next());
                    delete succ->get_dato();
                    delete succ;
                }
                else current = current->get_next(); //avanza solo se non rimuovo 
                //perchè? noi stiamo controllando il next di current -> quindi se rimuoviamo il successivo ne avremo un altro al prossimo
                //ciclo, vuol dire che se vado avanti saltiamo nodi:
                // [current] [succ] [] []
                // [current] [X] [] []
                // [current] [newSucc] []
            }
            if(check==false)
            {
                cout << "Nessuno studente trovato sotto la media di: " << grade << "." << endl;
            }
            cout << endl;
        }
};

int main() 
{
    Queue<Studente*>* studenti = new Queue<Studente*>(10);
    studenti
    ->enqueue(new Studente("Mario","Rossi",23))
    ->enqueue(new StudenteBorsista("Anna","Verdi",28.0,880,12))
    ->enqueue(new StudenteBorsista("Luca","Bianchi",26))
    ->enqueue(new StudenteBorsista("Sara","Neri",27.5))
    ->enqueue(new StudenteBorsista("Marco","Gialli",24.0,500))
    ->enqueue(new Studente("Marco","Fumagalli",18))
    ->enqueue(new StudenteBorsista("Gino","Topogino",30,3000,12))
    ->enqueue(new StudenteBorsista("Ketchup","Siracha",20));

    studenti->stampa();
    cout << "Ammontare totale delle borse di studio: " << studenti->totaleBorse() << endl;
    studenti->removeUndergrade(25);
    studenti->stampa();
    return 0;
}