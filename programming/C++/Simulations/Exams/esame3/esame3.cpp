/*
    -----------------------
    |   Studenti e pile   |
    -----------------------
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Studente
{
    private:
        int matricola;
        string nome;
        string cognome;
        double media;
    public:
        Studente(int mat, const string& nm, const string& cog, double avg) 
        : matricola(mat), nome(nm), cognome(cog), media(avg) {}
        ~Studente() { cout << "[DEBUG] Chiamato distruttore Studente." << endl; }
        Studente() : matricola(-1),nome("-1"),cognome("-1"),media(-1.0) {}

        int get_matricola() const { return matricola; }
        const string& get_nome() const { return nome; }
        const string& get_cognome() const { return cognome; }
        double get_media() const { return media; }

        //friend ostream& operator<<(ostream& os, Studente& s);
        virtual void stampa() const
        {
            cout << matricola << ": " << nome << " " << cognome << " - media " << media;
        }
};
/*
ostream& operator<<(ostream& os, Studente& s)
{
    os << s.get_matricola() << ": " << s.get_nome() << " " << s.get_cognome() << " - media " << s.get_media();
    return os;  
}*/

class BorsaDiStudio
{
    private:
        double importo;
        int durata;
    public:
        BorsaDiStudio(double amount, int time) : importo(amount), durata(time) {}
        ~BorsaDiStudio() { cout << "[DEBUG] Chiamato distruttore BorsaDiStudio." << endl; }
        BorsaDiStudio() : importo(0.0), durata(0) {}

        double get_importo() const { return importo; }
        int get_durata() const { return durata; }

        void set_importo(double newImporto) { importo = newImporto; }
        void set_durata(int newDurata) { durata = newDurata; }
};

class StudenteBorsista : public Studente
{
    private:
        BorsaDiStudio* borsa;
    public:
        StudenteBorsista(int mat, const string& nm, const string& cog, double avg, BorsaDiStudio* p = nullptr)
        : Studente(mat,nm,cog,avg), borsa(p) {}
        ~StudenteBorsista()         
        { 
            cout << "[DEBUG]: Chiamato distruttore StudenteBorsista." << endl; 
            if(borsa)  
                delete borsa;
        }
        StudenteBorsista() : Studente(), borsa(nullptr) {}

        double get_importo_borsa() const { return borsa->get_importo(); }
        
        void stampa() const
        {
            /*
            cout << static_cast<Studente&>(*this);
            if(borsa && borsa->get_importo() > 0)
                cout << " [borsa di "<< borsa->get_importo() << "]" << endl;*/

            Studente::stampa();
            if(borsa && borsa->get_importo() > 0)
                cout << " [borsa di " << borsa->get_importo() << "]";
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
class Stack
{
    private:
        Nodo<T>* top;
    public:
        Stack() : top(nullptr) {}

        bool isEmpty() const
        {
            return top==nullptr;
        }

        Stack& push(T nuovoDato)
        {
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            nuovo->set_next(top);
            top = nuovo; 
            return *this;
        }

        T pop()
        {
            if(isEmpty())
                return T();
            Nodo<T>* temp = top;
            T data = temp->get_dato();
            top = top->get_next();
            delete temp;
            return data;
        }         
        
        ~Stack() 
        { 
            cout << "[DEBUG]: Chiamato distruttore Stack." << endl;
            while(!isEmpty())
                this->pop(); 
        }


        bool readFile(const string& nomeFile)
        {
            ifstream file(nomeFile); 
            if(!file)
            {
                return false;
            }

            int matricola;
            string nome, cognome;
            double media;
            double importo;
            int durata;

            while(file >> matricola >> nome >> cognome >> media >> importo >> durata)
            {
                Studente* studente;
                if(importo > 0)
                {
                    BorsaDiStudio* borsa = new BorsaDiStudio(importo,durata);
                    studente = new StudenteBorsista(matricola, nome, cognome, media, borsa);
                }
                else studente = new Studente(matricola, nome, cognome, media);
            
                //si intende lo Stack
                this->push(studente);
            }
            file.close();
            return true; //operazione terminata con successo
        }

        void rimuoviUnder25()
        {
            //controllo in testa
            if(top != nullptr && top->get_dato()->get_media() < 25.0)
            {
                cout << "Studente insufficiente rimosso: ";
                top->get_dato()->stampa();
                cout << endl;
                this->pop();
            }

            if(isEmpty())
                return;
            

            Nodo<T>* current = top;
            while(current->get_next()!=nullptr)
            {
                Nodo<T>* succ = current->get_next();
                if(succ->get_dato()->get_media() < 25.0)
                {
                    cout << "Studente insufficiente rimosso: ";
                    succ->get_dato()->stampa();
                    cout << endl;

                    current->set_next(succ->get_next());
                    delete succ;
                }
                current = current->get_next(); //avanza solo se non ho rimosso 
            }
        }

        void stampa() const
        {
            Nodo<T>* current = top;

            while(current != nullptr)
            {
                current->get_dato()->stampa();
                current = current->get_next();
                cout << endl;
            }
        }

        double get_ammontareBorse()
        {
            Nodo<T>* current = top;
            double totale=0.0;
            while(current != nullptr)
            {
                StudenteBorsista* sb = dynamic_cast<StudenteBorsista*>(current->get_dato());
                if(sb!=nullptr) //cioé se è un borsista e non un semplice studente:
                    totale += sb->get_importo_borsa();

                current = current->get_next();
            }
            return totale;
        }
};

int main()
{

    /*StudenteBorsista s("1001","Mario","Rossi",25.5,800,12);
    s.stampa();*/

    Stack<Studente*> s; //Stack di puntatori a Studente
    const string input = "input.txt";
    if(!s.readFile(input))
        cout << "Errore durante lettura del file." << endl;

    s.rimuoviUnder25();
    cout << endl;
    s.stampa();
    cout << endl;

    cout << "Totale importi borse di studio: " << s.get_ammontareBorse() << " euro.\n" << endl;
    return 0;
}
