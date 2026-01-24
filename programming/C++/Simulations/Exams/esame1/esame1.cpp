/*

    Esame code di studenti

*/
#include <iostream>
#include <string>
using namespace std;

class Studente
{
    private:
        string matricola;
        string nome;
        string cognome;
        double media;
    public:
    Studente(const string& matr,const string& name,const string&surname,const double& average) : matricola(matr), nome(name), cognome(surname), media(average) {}
    Studente() : matricola("-1"), nome("-1"), cognome("-1"), media(-1.0) {}
    ~Studente() { cout << "Chiamato distruttore Studente." << endl; }

    const string& get_matricola() const { return matricola; }
    const string& get_nome() const { return nome; } 
    const string& get_cognome() const { return cognome; }
    double get_media() const { return media; }
    
    void set_matricola(const string& newMatricola) { matricola = newMatricola; }
    void set_nome(const string& newNome) { nome = newNome; }
    void set_cognome(const string& newCognome) { cognome = newCognome; }
    void set_media(double newMedia) { media = newMedia; }


    virtual void stampa() const
    {
        cout << this->matricola << ": " << this->nome << " " << this->cognome << " - " << this->media;
    }
};

class BorsaDiStudio
{
    private:
        double importo;
        int durata; //si suppone che siano dati in mesi
    public:
        BorsaDiStudio(double Importo,int Durata) : importo(Importo), durata(Durata) {}
        BorsaDiStudio() : importo(0), durata(0) {}
        ~BorsaDiStudio() { cout << "Chiamato distruttore BorsaDiStudio." << endl; }

        const double& get_importo() const { return importo; }
        const int& get_durata() const { return durata; }

        void set_importo(double newImporto) { importo = newImporto; }
        void set_durata(int newDurata) { durata = newDurata; }
};

class StudenteBorsista : public Studente
{
    private:
        BorsaDiStudio* borsa;
    public:
        StudenteBorsista(const string& matricola,
                        const string& nome,
                        const string& cognome,
                        double media,
                        double importo,
                        int durata) 
        : Studente(matricola,nome,cognome,media) , borsa(nullptr) 
        {
            borsa = new BorsaDiStudio(importo, durata);
        }
        ~StudenteBorsista() 
        { 
            cout << "Chiamato distruttore StudenteBorsista." << endl; 
            if(borsa)  
                delete borsa;
        }
        
        double get_importo_borsa() const { 
            if(borsa)
                return borsa->get_importo();
            return 0.0;
         }

        void stampa() const override 
        { 
            Studente::stampa(); 
            if(borsa && borsa->get_importo() > 0) //se non esiste e vi accedo causa SEGMENTATION FAULT
                cout << " [Borsa di " << borsa->get_importo() << " euro (" << borsa->get_durata() << " mesi)]"; 
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
};

template <typename T>
class Coda
{
    private: 
        Nodo<T>* front;
        Nodo<T>* rear;
        const int dimensione;
        int count;
    public:
        Coda(const int& dim) : front(nullptr), rear(nullptr), dimensione(dim), count(0) {}
        
        bool isEmpty() const
        {
            return front==nullptr;
        }

        bool isFull() const
        {
            return count >= dimensione;
        }

        bool enqueue(const T& dato)
        {
            Nodo<T>* nuovo = new Nodo<T>(dato);
            if(isEmpty())
            {
                front = rear = nuovo;
                count++;
                return true;
            }
            
            if(isFull())
            {
                return false;
            }

            //allora, inseriamo:
            rear->set_next(nuovo);
            rear = nuovo;
            count++;
            return true;
        }

        void dequeue()
        {
            if(isEmpty())
                return;
            
            Nodo<T>* current = front; //ricordiamo che le code hanno standard LIFO
            front = front->get_next();
            if(front==nullptr)
                rear = nullptr;
            
            delete current;
            
            count--;
        }

        void removeUnder25()
        {
            while(front!=nullptr && (front->get_dato()->get_media()) < 25.0 )
            {
                cout << "AVVISO:\n[RIMOSSO] Studente: ";
                front->get_dato()->stampa();
                cout << endl;
                dequeue();
            }

            Nodo<T>* current = front;
            if(!current)
                return;
            Nodo<T>* succ = front->get_next();

            while(succ != nullptr)
            {
                if( (succ->get_dato()->get_media()) < 25.0 )
                {
                    cout << "[RIMOSSO] Studente: ";
                    succ->get_dato()->stampa();
                    cout << endl;
                    current->set_next( succ->get_next() );
                    delete succ;
                    succ = current->get_next();
                    count--;
                    if(succ == nullptr)
                        rear = current;
                }
                else
                {
                    current = succ;
                    succ = succ->get_next();
                }
            }
        }

        void stampa() const
        {
            Nodo<T>* current = front;
            while(current != nullptr)
            {
                current->get_dato()->stampa();
                cout << endl;
                current = current->get_next();
            }
        }

        double ammontareBorse() const
        {
            double totale = 0.0;
            Nodo<T>* current = front;
            while(current)
            {
                StudenteBorsista* sb = dynamic_cast<StudenteBorsista*>(current->get_dato());
                if (sb != nullptr)
                    totale += sb->get_importo_borsa();

                current = current->get_next();
            }
            return totale;
        }
                
        ~Coda() 
        {
            cout << "Chiamato distruttore Coda." << endl;
            while(!isEmpty())
                dequeue();
        }


};

int main()
{
    Coda<Studente*> coda(10); //se coda piena: cout << "Impossibile inserire nuovo Studente: raggiunto massimo numero elementi coda: " << count << " su " << dimensione << endl;
    coda.enqueue(new Studente("1001","Mario","Rossi",25.5));
    coda.enqueue(new StudenteBorsista("1002","Anna","Verdi",28.0,880,12));
    coda.enqueue(new Studente("1003","Luca","Bianchi",26.0));
    coda.enqueue(new Studente("1004","Sara","Neri",27.5));
    coda.enqueue(new StudenteBorsista("1005","Marco","Gialli",24.0,500,6));
    coda.enqueue(new StudenteBorsista("1006","Laura","Marroni",29.0,600,12));
    coda.enqueue(new StudenteBorsista("1007","Gianni","Fucsia",24.9,1000,24));

    coda.stampa();
    cout << endl;
    coda.removeUnder25();

    coda.stampa();

    cout << "\nAmmontare borse di studio: " << coda.ammontareBorse() << endl;

    return 0;
}