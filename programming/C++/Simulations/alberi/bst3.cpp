
/* classico esercizio Studenti con borsa con albero di ricerca bts per matricola... */

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Studente
{
    private:
        string name;
        string surname;
        int matricola;
        float media;
    public:
        Studente(int mat, const string& n, const string& cog, float avg) : matricola(mat), name(n), surname(cog),  media(avg) {}
        ~Studente() {}

        const string& get_name() const { return name; }
        const string& get_surname() const { return surname; }
        int get_matricola() const { return matricola; }
        float get_media() const { return media; }
        
        friend ostream& operator<<(ostream&, const Studente&);
        friend istream& operator>>(istream&, Studente&);

        virtual void stampa() const
        {
            cout << *this;
        } 
};

ostream& operator<<(ostream& os, const Studente& s)
{
    os << s.matricola << " - " << s.name << " " << s.surname << " - " << s.media;
    return os;
}

istream& operator>>(istream& is, Studente& s)
{
    is >> s.matricola >> s.name >> s.surname >> s.media;
    return is;
}

class BorsaDiStudio
{
    private:
        int importo;
        int durata;
    public:
        BorsaDiStudio(int imp, int d) : importo(imp), durata(d) {}
        ~BorsaDiStudio() {}

        int get_importo() const { return importo; }
        int get_durata() const { return durata; }

        void stampa() const 
        {
            cout << importo << " euro - " << durata << " mesi";
        }
};

class StudenteBorsista : public Studente
{
    private:
        BorsaDiStudio* borsa; 
    public:
        StudenteBorsista(int matricola, const string& nome, const string& cognome, float media, BorsaDiStudio* b) : Studente(matricola, nome, cognome, media), borsa(b) {}
        ~StudenteBorsista() { if(borsa) delete borsa; }

        int get_importo_borsa() const { if(borsa) return borsa->get_importo(); else return 0; }
        int get_durata_borsa() const { if(borsa) return borsa->get_durata(); else return 0; }

        void stampa() const override
        {
            Studente::stampa();
            cout << " - ";
            borsa->stampa();
            cout << endl;
        }
};

//================================================================================================================================================

template <class T> 
class Nodo
{
    private:
        T dato;
        Nodo<T>* left;
        Nodo<T>* right;
    public:
        Nodo(const T& data) : dato(data), left(nullptr), right(nullptr) {}
        ~Nodo() {}

        const T& get_dato() const { return dato; }
        Nodo<T>* get_left() const { return left; }
        Nodo<T>* get_right() const { return right; }

        void set_dato(const T& newData) { dato = newData; }
        void set_left(Nodo<T>* newLeft) { left = newLeft; }
        void set_right(Nodo<T>* newRight) { right = newRight; }
};

template <class T>
class BST //Binary Search Tree - in questo caso ordinato per matricole.
{
    private:
        Nodo<T>* root;

        Nodo<T>* insertHelper(Nodo<T>* nodo, const T& nuovoDato)
        {
            if(!nodo)
                return new Nodo<T>(nuovoDato);

            if(nuovoDato->get_matricola() < nodo->get_dato()->get_matricola())
                nodo->set_left(insertHelper(nodo->get_left(), nuovoDato));
            else if(nuovoDato->get_matricola() > nodo->get_dato()->get_matricola()) 
                nodo->set_right(insertHelper(nodo->get_right(), nuovoDato));
            else //if(nuovoDato->get_matricola() == nodo->get_dato()->get_matricola())
            {
                cout << "Non puoi inserire due matricole uguali!";
                exit(1); 
            }
            return nodo;
        }

        Nodo<T>* removeMatricolaHelper(Nodo<T>* nodo, int key)
        {
            if(!nodo)
                return nodo; //nullptr
            
            if(key < nodo->get_dato()->get_matricola())
                nodo->set_left(removeMatricolaHelper(nodo->get_left(), key));
            else if(key > nodo->get_dato()->get_matricola())
                nodo->set_right(removeMatricolaHelper(nodo->get_right(), key));
            
            else //trovato 
            {
                //caso 1: no figli
                if(!nodo->get_left() && !nodo->get_right())
                {
                    delete nodo->get_dato();
                    delete nodo;
                    return nullptr;
                }

                //caso 2: un figlio
                else if(!nodo->get_right())
                {
                    Nodo<T>* temp = nodo->get_left();
                    delete nodo->get_dato();
                    delete nodo;
                    return temp; 
                } 

                else if(!nodo->get_left())
                {
                    Nodo<T>* temp = nodo->get_right();
                    delete nodo->get_dato();
                    delete nodo;
                    return temp;
                }

                //caso 3: due figli --> trapianto 
                else 
                {
                    //copio dati del più piccolo successore di nodo
                    Nodo<T>* minNode = findMin(nodo->get_right());
                    //modifico nodo con i nuovi dati
                    nodo->set_dato(minNode->get_dato());
                    //elimino doppione
                    nodo->set_right(nodo->get_right(),nodo->get_dato()->get_matricola());
                }
            }
            return nodo;

        }

        void clearAllHelper(Nodo<T>* nodo) //post order
        {
            if(!nodo)
                return;
            clearAllHelper(nodo->get_left());
            clearAllHelper(nodo->get_right());
            delete nodo->get_dato();
            delete nodo;
        }

        void printAllHelper(Nodo<T>* nodo) const //in order
        {
            if(!nodo)
                return;
            printAllHelper(nodo->get_left());
            nodo->get_dato()->stampa();
            printAllHelper(nodo->get_right());
        }

        void stampaStudentiHelper(Nodo<T>* nodo) const
        {
            if(!nodo)
                return;

            stampaStudentiHelper(nodo->get_left());
            Studente* s = dynamic_cast<StudenteBorsista*>(nodo->get_dato());
            if(!s) //if(s) solo borsisti, if(!s) solo studenti senza borsa
            {
                nodo->get_dato()->stampa();
                cout << endl;
            }
            stampaStudentiHelper(nodo->get_right());
        }

        void stampaStudentiBorsistiHelper(Nodo<T>* nodo) const
        {
            if(!nodo)
                return;

            stampaStudentiBorsistiHelper(nodo->get_left());
            StudenteBorsista* s = dynamic_cast<StudenteBorsista*>(nodo->get_dato());
            if(s)
            {
                s->stampa();
            }
            stampaStudentiBorsistiHelper(nodo->get_right());
        }        

    public:
        BST() : root(nullptr) {}

        bool isEmpty() const { return root==nullptr; }

        void insert(const T& nuovoDato)
        {
            root = insertHelper(root, nuovoDato);
        }

        Nodo<T>* findMin(Nodo<T>* nodo) const 
        {
            while(nodo->get_left())
                nodo = nodo->get_left();
            return nodo;
        }

        void removeMatricola(int key)
        {
            root = removeMatricolaHelper(root, key);
        }

        void printAll()
        {
            cout << "Stampa BST inOrder:" << endl;
            printAllHelper(root);
            cout << endl;
        }

        void clearAll()
        {
            cout << "Eliminazione di tutti i nodi del bst." << endl;
            clearAllHelper(root);
        }

        ~BST() { if(isEmpty()) return; else clearAll(); }


        BST<T>* insertFromFile(const string& nomeFile)
        {
            ifstream file(nomeFile);
            if(!file)
            {
                cerr << "Errore durante apertura file per lettura." << endl;
                exit(1);
            }

            //abbiamo due tipi di dato, separati solo da spazi. 
            string buffer;
            while(getline(file, buffer))
            {
                stringstream ss(buffer);
                string nome, cognome;
                int matricola;
                float media;
                ss >> matricola >> nome >> cognome >> media;

                int importo, durata; //per studenti borsisti
                if(ss >> importo >> durata)
                    insert(new StudenteBorsista(matricola, nome, cognome, media, new BorsaDiStudio(importo, durata)));
                else 
                    insert(new Studente(matricola, nome, cognome, media));
            }
            file.close();
            return this;
        }

        void stampaStudenti() const 
        {
            cout << "Stampa tutti gli studenti senza borsa:" << endl;
            stampaStudentiHelper(root);
        }

        void stampaStudentiBorsisti() const 
        {
            cout << "Stampa tutti gli studenti borsisti:" << endl;
            stampaStudentiBorsistiHelper(root);
        }
};

//================================================================================================================================================

int main()
{
    string nomeFile = "bst3_input.txt";

    BST<Studente*>* bst = new BST<Studente*>();
    //bst->insert(new StudenteBorsista(1001,"Mario","Rossi", 24.5, new BorsaDiStudio(2500, 4)));
    //bst->insert(new StudenteBorsista(1234,"Luigi","Verdi", 23.4, new BorsaDiStudio(1200, 12)));

    bst->insertFromFile(nomeFile);

    bst->printAll();

    cout << "\n---------------------------------------" << endl;
    bst->stampaStudenti();
    cout << "\n\n---------------------------------------" << endl;
    bst->stampaStudentiBorsisti();
    cout << endl;

    return 0;
}