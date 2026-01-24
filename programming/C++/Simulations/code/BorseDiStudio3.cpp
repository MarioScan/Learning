    #include <iostream>
    using namespace std;

    class Studente
    {
        private:
            string nome;
            string cognome;
            float media;
            int matricola;

            int assign_id()
            {
                static int id = 1000100;
                return ++id;
            }
        public:
            Studente() : nome(""), cognome(""), media(0.0), matricola(assign_id()) {}
            Studente(const string& name, const string& surname, float avg) : nome(name), cognome(surname), media(avg), matricola(assign_id()) {}
            ~Studente() {}
            Studente(const Studente& s2) : nome(s2.nome), cognome(s2.cognome), media(s2.media), matricola(s2.matricola) {} //si suppone serva per backup

            const string& get_nome() const { return nome; }
            const string& get_cognome() const { return cognome; }
            float get_media() const { return media; }
            int get_matricola() const { return matricola; }

            void set_nome(const string& newName) { nome = newName; }
            void set_cognome(const string& newSurname) { cognome = newSurname; }
            void set_media(float newMedia) { media = newMedia; }
            void set_matricola(int newMatricola) { matricola = newMatricola; }

            friend ostream& operator<<(ostream&, const Studente&);

            virtual void stampa() const
            {
                cout << *this;
            }
    };

    ostream& operator<<(ostream& os, const Studente& s)
    {
        os << s.matricola << " - " << s.nome << " " << s.cognome << " - " << s.media;
        return os; 
    }

    class BorsaDiStudio
    {
        private:
            int ammontare; 
            int durata;
        public:
            BorsaDiStudio(int amount, int length) : ammontare(amount), durata(length) {}
            ~BorsaDiStudio() {}

            int get_ammontare() const { return ammontare; }
            int get_durata() const { return durata; }

            friend ostream& operator<<(ostream& os, const BorsaDiStudio& b);
            void stampa()
            {
                cout << *this;
            }
    };
    ostream& operator<<(ostream& os, const BorsaDiStudio& b)
    {
        os << b.ammontare << " euro - " << b.durata << " mesi.";
        return os;
    }

    class StudenteBorsista : public Studente{
        private:
            BorsaDiStudio* borsa;
        public:
            StudenteBorsista() : Studente(), borsa(nullptr) {}
            StudenteBorsista(const string& nome, const string& cognome, float media, BorsaDiStudio* b) 
            : Studente(nome, cognome, media), borsa(b) {}
            StudenteBorsista(const string& nome, const string& cognome, float media) 
            : Studente(nome, cognome, media), borsa(nullptr) {}

            ~StudenteBorsista() { if(borsa) delete borsa; }

            int get_ammontare_borsa() const { return borsa->get_ammontare(); }
            int get_durata_borsa() const { return borsa->get_durata(); }

            void assegna_borsa(BorsaDiStudio* nuovaBorsa) { borsa = nuovaBorsa; }

            friend ostream& operator<<(ostream&, const StudenteBorsista&);
            void stampa() const override //se non utilizzo override metodo Studente stampa solo la parte studente -> slicing
            { 
                cout << *this;
            }
    };
    ostream& operator<<(ostream& os, const StudenteBorsista& s)
    {
        os << s.get_matricola() << " - " << s.get_nome() << " " << s.get_cognome()  << " - " << s.get_media() << " - "; 
        if(s.borsa) 
            os << *(s.borsa);
        else 
            os << "[Nessuna borsa].";

        return os; 
    }

    //===============================================================================================================

    template <class T>
    class Nodo
    {
        private:
            T dato;
            Nodo<T>* next;
            Nodo<T>* prev;
        public:
            Nodo(const T& data) : dato(data), next(nullptr), prev(nullptr) {}
            ~Nodo() {}

            const T& get_dato() const { return dato; }
            Nodo<T>* get_next() const { return next; }
            Nodo<T>* get_prev() const { return prev; }

            void set_next(Nodo<T>* n) { next = n; }
            void set_prev(Nodo<T>* n) { prev = n; }
    };

    template <class T>
    class Queue
    {
        private:
            Nodo<T>* front;
            Nodo<T>* rear; 
            int capacity;
            int count;
        public:
            Queue(int max) : capacity(max), count(0), front(nullptr), rear(nullptr) {}
            
            bool isEmpty() { return front == nullptr; }
            bool isFull() { return count >= capacity; }

            Queue<T>* enqueue(const T& nuovoDato)
            {
                if(isFull())
                {
                    cerr << "Queue is full." << endl;
                    return this;
                }

                Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
                if(!nuovo)
                {
                    cerr << "Impossible to create new node." << endl;
                    exit(1);
                }
                count++;
                if(isEmpty())
                {
                    front = rear = nuovo;
                    return this;
                }

                //insert from rear
                nuovo->set_prev(rear);
                rear->set_next(nuovo);
                rear = nuovo;
                return this;
            }

            void dequeue()
            {
                if(isEmpty())
                {
                    cout << "Unable to dequeue: queue is already empty!" << endl;
                    return;
                }

                //Queue -> FIFO First In First Out
                Nodo<T>* temp = front;
                delete front->get_dato();
                if(front->get_next())
                { 
                    front = front->get_next();
                    front->set_prev(nullptr);
                }
                else 
                    front = rear = nullptr;
                delete temp;
                count--;
            }

            void removeMatricola(int matricola)
            {
                cout << "Rimozione matricola \"" << matricola << "\":" << endl; 
                bool check=false; //there can only be one Matricola ...
                if(isEmpty())
                {
                    cout << "Cannot remove any element, as there are none in the Queue." << endl;
                    return; 
                }

                Nodo<T>* current = front;
                while(current && check == false)
                {   
                    if(current->get_dato()->get_matricola() == matricola)
                    {
                        check = true;
                        cout << "[RIMOSSO]: "; current->get_dato()->stampa();
                        //case 1: current is front
                        if(!current->get_prev())
                        {
                            Nodo<T>* temp = current;
                            delete current->get_dato();
                            current = current->get_next();
                            delete temp;
                            current->set_prev(nullptr);
                            front = current;
                        }

                        //case 2: current is at the end
                        else if(!current->get_next())
                        {
                            Nodo<T>* temp = current;
                            delete current->get_dato();
                            current->get_prev()->set_next(nullptr); //we disconnect this node from the queue.
                            rear = current->get_prev();
                            delete temp;
                        }

                        //case 3: current is in the middle
                        else
                        {
                            Nodo<T>* temp = current;
                            delete current->get_dato();
                            current->get_prev()->set_next(current->get_next()); //prev -> current -> next ---->> prev -> next 
                            current->get_next()->set_prev(current->get_prev()); //prev <- current <- next ---->> prev <- next
                            current = current->get_next();
                            delete temp;
                        }
                    }
                    else //if I didn't find anything, continue research...
                        current = current->get_next(); 
                }
                if(check==false)
                    cout << "Matricola non trovata." << endl;
                else count--;
            }

            void printAll()
            {
                cout << "\nStampa coda:" << endl;
                Nodo<T>* current = front;
                while(current)
                {
                    StudenteBorsista* sb = dynamic_cast<StudenteBorsista*>(current->get_dato());
                    if(sb)
                    {
                        cout << "StudenteBorsista - "; 
                        sb->stampa();
                    }
                    else
                    {
                        cout << "Studente - ";
                        current->get_dato()->stampa();
                    } 
                    cout << endl;
                    current = current->get_next();
                }
            }

            void clear()
            {
                if(isEmpty())
                    return;
                while(front)
                {
                    Nodo<T>* temp = front;
                    delete front->get_dato(); //we are dealing with a pointer list
                    delete temp;
                    front = front->get_next();
                }
                count = 0;
            }
            
            ~Queue() { clear(); } 
    };

    //===============================================================================================================

    int main()
    {
        StudenteBorsista s1("Gianni", "Gialli",28.9,new BorsaDiStudio(5000,40));
        s1.stampa();

        Queue<Studente*>* coda = new Queue<Studente*>(10);
        coda
        ->enqueue(new Studente("Gianni","Gialli",28.9))
        ->enqueue(new StudenteBorsista("Piero","Pink",25.6,new BorsaDiStudio(500,4)))
        ->enqueue(new StudenteBorsista("Emma","Marroni",20.0))
        ->enqueue(new Studente("Mario", "Rossi", 19.9))
        ->enqueue(new StudenteBorsista("Luigi", "Verdi", 26.7, new BorsaDiStudio(1500,10)));

        coda->printAll();
        coda->removeMatricola(1000102);
        coda->printAll();
        coda->dequeue();
        coda->printAll();



        return 0;
    }