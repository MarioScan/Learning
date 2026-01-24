#include <iostream>
using namespace std;

class Studente
{
    private:
        string nome;
        string cognome;
        float media;
        int matricola;

        int assign_matricola()
        {
            static int assignMatricola = 1001;
            return assignMatricola++;
        }

    public:
        Studente(const string& nm, const string& cog, float avg) 
        : nome(nm), cognome(cog), media(avg), matricola(assign_matricola()) {}
        ~Studente() { cout << "[DEBUG]: Chiamato distruttore Studente." << endl; }
        
        const string& get_nome() const { return nome; }
        const string& get_cognome() const { return cognome; }
        float get_media() const { return media; }
        int get_matricola() const { return matricola; }
        
        void set_nome(const string& new_nome) { nome = new_nome; }
        void set_cognome(const string& new_cog) { cognome = new_cog; }
        void set_media(float new_avg) { media = new_avg; }

        friend ostream& operator<<(ostream&, const Studente&); //esempio operator overload
        virtual void stampa() const 
        {
            cout << *this;
        }
};

ostream& operator<<(ostream& os, const Studente& stud)
{
    os << stud.get_matricola() << ": " << stud.get_nome() <<
     " " << stud.get_cognome() << " - " << stud.get_media();
    return os;
}

class BorsaDiStudio
{
    private:
        int importo; //si presume che l'importo sia sempre arrotondato all'intero
        int durata; //in mesi
    public:
        BorsaDiStudio(int imp, int tempo) : importo(imp), durata(tempo) {}
        ~BorsaDiStudio() {
            cout << "[DEBUG]: Chiamato distruttore BorsaDiStudio." << endl;  
        }
        
        int get_importo() const { return importo; }
        int get_durata() const { return durata; }

        void set_importo(int newImporto) { importo = newImporto; }
        void set_durata(int newDurata) { durata = newDurata; }

        void stampa() const
        {
            cout << " [borsa di " << importo << " euro]"; 
        }
};

class StudenteBorsista : public Studente
{
    private:
        BorsaDiStudio* borsa; 
    public: 
        StudenteBorsista(const string& nm, const string& cog, float avg, int imp, int tempo) 
        : Studente(nm,cog,avg), borsa(new BorsaDiStudio(imp,tempo)) {} 
        StudenteBorsista(const string& nm, const string& cog, float avg) 
        : Studente(nm,cog,avg), borsa(nullptr) {} 
        ~StudenteBorsista() 
        { 
            delete borsa;
            cout << "[DEBUG]: Chiamato distruttore StudenteBorsista." << endl;
        }

        int get_importo_borsa() const { 
            if(borsa) 
                return borsa->get_importo(); 
            else return 0; 
        }
        int get_durata_borsa() const { 
            if(borsa) 
                return borsa->get_durata(); 
            else return 0; 
        }

        void stampa() const override
        {
            Studente::stampa();
            if(borsa!=nullptr)
                this->borsa->stampa();
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
        const int maxDim;
        int count=0;
    public:
        Queue(int dim) : maxDim(dim), front(nullptr), rear(nullptr) {}
        
        bool isEmpty() const
        {
            return front == nullptr;
        }        

        bool isFull() const
        {
            return  count >= maxDim;
        }
        Queue<T>* enqueue(const T& newData)
        {
            if(isFull()) //check 1
            {
                cout << "/!\\ Coda piena /!\\" << endl;
                return this;
            }
        
            count++;
            Nodo<T>* nuovo = new Nodo<T>(newData);

            if(!nuovo) //check 2 
            {
                cerr << "Impossibile creare nuovo nodo" << endl;
                exit(1);
            }

            if(isEmpty())
            {
                front = rear = nuovo;
                return this;
            }

            //la coda segue tipologia FIFO - First In First Out 
            
            rear->set_next(nuovo);
            rear = nuovo;
            return this;
        }

        void dequeue() //FIFO
        {
            if(isEmpty())
                return;
            
            Nodo<T>* temp = front;
            delete front->get_data();
            
            if(!front->get_next())
                rear = front = nullptr;
            else front = front->get_next();
        
            delete temp;
            count--;
        }

        void clearQueue()
        {
            if(isEmpty())
            {
                cout << "Coda vuota." << endl;
                return;
            }
            
            while(front)
            {
                Nodo<T>* temp = front;
                front = front->get_next();
                delete temp;
            }
            rear = front = nullptr;
            count=0;
        }

        void removeUnworthy(int key)
        {
            if(isEmpty())
            {
                cout << "Coda vuota." << endl;
                return;
            }

            bool check=false;
            Nodo<T>* current = front;
            //primo scorrimento per vedere se ci sono elementi da rimuovere
            while(current)
            {
                if(current->get_data()->get_media() < key)
                {
                    check = true;
                    break; //non occorre continuare a scorrere
                }
                current = current->get_next();
            }
            //se non c'è nulla da rimuovere ritorna
            if(check == false)
                return;
            
            /*  ------ Brain in work ------   */
            cout << "Avviso: Rimossi studenti con media inferiore a " << key << " :\n" << endl; 
            
            while(front && front->get_data()->get_media() < key)
            {
                front->get_data()->stampa();
                cout << endl;
                dequeue();
            }
            if(isEmpty()) //fuori dal ciclo per alleggerire il while
                return; //controllo di nuovo.

            current = front;
            Nodo<T>* succ = current->get_next();
             
            while(succ)
            {
                if(succ->get_data()->get_media() < key)
                {
                    succ->get_data()->stampa();
                    cout << endl;
                    current->set_next(succ->get_next());
                    delete succ->get_data();
                    delete succ;
                    
                    succ = current->get_next();
                    if(!succ)
                        rear = current;

                    count--;
                }
                else //non trova nulla allora scorro di uno 
                {
                    current = succ;
                    succ = succ->get_next(); 
                }
            }
            cout << endl;
        }

        void stampa() const
        {
            cout << "Stampa lista studenti:" << endl;
            if(isEmpty())
            {
                cout << "Coda vuota." << endl;
                return;
            }

            Nodo<T>* current = front;
            while(current)
            {
                current->get_data()->stampa();
                current = current->get_next();
                cout << endl;
            }
        }

        int AmmontareBorse() const
        {
            if(isEmpty())
            {
                cout << "Coda vuota." << endl;
                exit(0);
            }
            
            int totale=0;
            Nodo<T>* current = front;

            while(current)
            {
                StudenteBorsista* studBorsista = 
                    dynamic_cast<StudenteBorsista*>(current->get_data());
                if(studBorsista)
                    if(studBorsista->get_importo_borsa() > 0)
                        totale+=studBorsista->get_importo_borsa();
                //se è nullo vuol dire che è solo uno studente
                current = current->get_next();
            } 
            
            //precisione con libreria <iomanip> --> cout << << fixed << setprecision(1) << totale << endl;
            // se era un float: totale = ((int)(totale*10)) / 10.0f;

            return totale;
        }        
        
        
        ~Queue() 
        { 
            clearQueue();
            cout << "[DEBUG]: Chiamato distruttore Coda." << endl; 
        }
};

int main()
{
    Queue<Studente*>* studenti = new Queue<Studente*>(10);
    studenti
    ->enqueue(new StudenteBorsista("Mario","Rossi",25.5))
    ->enqueue(new StudenteBorsista("Anna","Verdi",28.0,880,12))
    ->enqueue(new Studente("Luca","Bianchi",26.0))
    ->enqueue(new Studente("Sara","Neri",27.5))
    ->enqueue(new StudenteBorsista("Gianni","Trufaldino",20,5000,10))
    ->enqueue(new StudenteBorsista("Laura","Marroni",29.0,600,6));

    studenti->stampa();

    studenti->removeUnworthy(25);

    studenti->stampa();
    cout << "Totale degli importi delle borse di studio: " << studenti->AmmontareBorse() << " euro." << endl;


    return 0;
}