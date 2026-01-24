/*

    ------------------------------
    |       Albero di ricerca    |
    |            (BST)           |
    ------------------------------
*/

#include <iostream>
#include <string>
#include <fstream>
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
        ~Studente() { cout << "[DEBUG]: Chiamato distruttore Studente." << endl;}
        Studente() : matricola(-1), nome("-1"), cognome("-1"), media(0.0) {}
        Studente(const Studente& stud) 
        : matricola(stud.matricola), nome(stud.nome), cognome(stud.cognome), media(stud.media) {}

        int get_matricola() const { return matricola; }
        const string& get_nome() const { return nome; }
        const string& get_cognome() const { return cognome; }
        double get_media() const { return media; }

        friend ostream& operator<<(ostream& os, const Studente& s);

        void stampa()
        {
            cout << *this << endl;
        }
};
ostream& operator<<(ostream& os, const Studente& s)
{
    os << s.get_matricola() << ": " << s.get_nome() << " " << s.get_cognome() << " - media: " << s.get_media();
    return os;
}

template <typename T>
class Nodo
{
    private:
        T dato;
        Nodo<T>* left;
        Nodo<T>* right;
    public:
        Nodo(const T& data) : dato(data), left(nullptr), right(nullptr) {}

        const T& get_dato() const { return dato; }
        Nodo<T>* get_left() const { return left; }
        Nodo<T>* get_right() const { return right; }
        
        void set_left(Nodo<T>* newLeft) { left = newLeft; }
        void set_right(Nodo<T>* newRight) { right = newRight; }
};

template <typename T>
class BST
{
    private: 
        Nodo<T>* root;
    
    Nodo<T>* insert_helper(Nodo<T>* radice, const T& nuovoDato)
    {
        if(radice == nullptr)
            return new Nodo<T>(nuovoDato);
        
        if(nuovoDato->get_matricola() > radice->get_dato()->get_matricola())
            radice->set_right( insert_helper(radice->get_right(),nuovoDato) );
        else if(nuovoDato->get_matricola() < radice->get_dato()->get_matricola())
            radice->set_left( insert_helper(radice->get_left(), nuovoDato));
        else 
        {
            cerr << "Errore: non sono ammessi studenti con stessa matricola!" << endl;
            exit(0);
        } 
        return radice;
    }

    T search_helper(Nodo<T>* radice, const int key)
    {
        if(radice==nullptr)
            return T();
        
        if(key == radice->get_dato()->get_matricola())
            return radice->get_dato();
        if(key > radice->get_dato()->get_matricola())
            return search_helper(radice->get_right(),key);
        else
            return search_helper(radice->get_left(),key);
    }

    void inOrderHelper(Nodo<T>* radice)
    {
        //in ordine --> sinistra -> radice -> destra
        if(radice==nullptr)
            return;
        
        inOrderHelper(radice->get_left());
        cout << *(radice->get_dato()) << endl;
        inOrderHelper(radice->get_right()); 
    }

    void destroyHelper(Nodo<T>* radice)
    {
        if(radice == nullptr)
            return;
        
        destroyHelper(radice->get_left());
        destroyHelper(radice->get_right());
        delete radice;
    }

    Nodo<T>* successore(Nodo<T>* radice) //minore del lato maggiore
    {
        radice = radice->get_right(); //mi sposto al sottoalbero destro
        while(radice->get_left() != nullptr) //lo scorro fino al punto più a sinistra possibile
        {
            radice = radice->get_left();
        }
            
        return radice; //ritorno valore
    }

    Nodo<T>* predecessore(Nodo<T>* radice)
    {
        radice = radice->get_left();
        while(radice->get_right() != nullptr)
        {
            radice = radice->get_right();
        }
        return radice;
    }

    Nodo<T>* remove_helper(Nodo<T>* radice, const int key)
    {
        if(radice == nullptr)
            return nullptr;

        //ricerca
        if(key < radice->get_dato()->get_matricola())
        {
            radice->set_left( remove_helper( radice->get_left(),key ) );
        }
        else if(key > radice->get_dato()->get_matricola())
        {
            radice->set_right( remove_helper( radice->get_right(),key ) );
        }
        else //trovato: vediamo se e quanti figli ha (da trapiantare) 
        {
            if(radice->get_left() == nullptr && radice->get_right() == nullptr) //caso 1: il nodo è una foglia
            {
                delete radice->get_dato();
                delete radice; //cancello nodo dalla memoria
                return nullptr; //ritorno nullptr per aggiornare memoria puntatore genitore
            }
            else if(radice->get_left() != nullptr) //esiste figlio a sinistra
            {
                Nodo<T>* temp = radice->get_left();
                delete radice->get_dato();
                delete radice;
                return temp;
            }
            else if(radice->get_right() != nullptr) //a destra 
            {
                Nodo<T>* temp = radice->get_right();
                delete radice->get_dato();
                delete radice;
                return temp;
            }
            else 
            {
                // due figli → usa successore
                Nodo<T>* succ = successore(radice);
                *(radice->get_dato()) = *(succ->get_dato());
                radice->set_right(remove_helper(radice->get_right(), succ->get_dato()->get_matricola()));
            }
        }
        return radice;
    }

    public:
        BST() : root(nullptr) {}

        void insert(const T& nuovoDato)
        {
            root = insert_helper(root, nuovoDato);
        }

        T search(const int key)
        {
            return search_helper(root,key);
        }

        bool readFile(const string& nomeFile)
        {
            ifstream file(nomeFile);
            if(!file)
                return false;

            string buffer;
            while(getline(file,buffer,',')) //delimitatore ',' fino a dove legge ogni stringa
            {
                int matricola = stoi(buffer); //string To int

                getline(file, buffer, ',');
                string nome = buffer;

                getline(file, buffer, ',');
                string cognome = buffer;

                getline(file, buffer);
                double media = stod(buffer);

                Studente* s = new Studente(matricola,nome,cognome,media);
                insert(s);
            }
            return true;
        }

        void inOrder()
        {
            inOrderHelper(root);
        }

        void destroy()
        {
            destroyHelper(root);
        }

        void remove(const int key)
        {
            cout << "Elimino valore: \"" << key << "\" dall'albero di Ricerca." << endl;
            if(search(key)) //se ritorna true, cioé se esiste, allora:
                root = remove_helper(root,key);
            else 
                cout << "Valore: \"" << key << "\" non trovato." << endl;
        }

        ~BST() 
        { 
            cout << "[DEBUG]: Chiamato distruttore Albero Binario di Ricerca (BTS)." << endl; 
            this->destroy();
        }

        
};

int main()
{
    /*Studente s(1,"Mario","Rossi",25.5);
    Studente s1(s);
    cout << s1 << endl;
    cout << endl;
    //s1.stampa();*/

    BST<Studente*> tree;
    const string fileIn = "input.txt";
    if(!tree.readFile(fileIn))
    {
        cerr << "Impossibile aprire file per la lettura. " << endl;
        exit(0);
    }
    cout << *(tree.search(1004)) << "\n" << endl;

    //tree.destroy(); //test
    tree.remove(1006);
    tree.inOrder();
    cout << endl;


    return 0;
}