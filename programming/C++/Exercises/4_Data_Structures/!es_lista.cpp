/*
  🧪 ESERCIZIO (30 MIN)
Obiettivo:
Implementa una lista ordinata di studenti con:
  -  nome (string)
  -  voto (int)

Operazioni richieste:
  -  Inserimento mantenendo l’ordine decrescente per voto
  -  Stampa
  -  Ricerca per nome
  -  Cancellazione per nome
*/

#include <iostream>
using namespace std;

class Studente
{
    private:
        string nome;
        int voto;
    public:
        Studente(string name, int score) : nome(name), voto(score) {}
        Studente() : nome("Sconosciuto"), voto(0) {}
        Studente(const Studente& stud) : nome(stud.nome), voto(stud.voto) {}
        ~Studente() { cout << "Distruttore Studente chiamato." << endl; } 

        const string& getNome() const { return nome; }
        const int& getVoto() const { return voto; }

        void setNome(const string& newName) { nome = newName; }
        void setVoto(const int& newScore) { voto = newScore; } 

        friend ostream& operator<<(ostream& out, const Studente& stud);

};

ostream& operator<<(ostream& out, const Studente& stud)
{
    out << "Dati studente:\nNome: " << stud.getNome() << "\nVoto: " << stud.getVoto() << endl;
    return out;
}

class Nodo 
{
    public:
        Studente stud;
        Nodo* next;
        
        Nodo(const string& nome, const int& voto) : stud(nome,voto), next(nullptr) {}

        void print(const Nodo& nodoStud)
        {
            cout << "\nDati studente:\nNome: " << nodoStud.stud.getNome() << "\nVoto: " << nodoStud.stud.getVoto() << endl;
        }
};

class Lista
{
    private:
        Nodo* head;
    public:
        Lista() : head(nullptr) {}

        ~Lista() {
            cout << "Distruttore Lista chiamato." << endl;
            while(head!=nullptr)
            {
                Nodo* temp = head;
                head = head->next;
                delete temp;
            }
        }

        Nodo* getMiddle(Nodo* head)
        {
            if(head==nullptr || head->next==nullptr)
                return head; 
            
            Nodo* slow = head; //si muove di 1 --> 1 , 2 , 3 , 4 , 5 
            Nodo* fast = head->next; //si muove di 2 --> 2 , 4 , 6 , 8 , 10
            //slow diventa quindi la metà di fast 
            while(fast != nullptr && fast->next != nullptr)
            {
                slow = slow->next;
                fast = fast->next->next;
            }

            return slow; //ritorna la metà
        }

        Nodo* merge(Nodo* leftSide, Nodo* rightSide)
        {
            if(leftSide == nullptr) //abbiamo finito tutti gli elementi della lista a sinitra --> allora ritorna quella a destra (a sinistra non c'è più nulla da fare)
                return rightSide; 
            if(rightSide == nullptr) //viceversa come visto 
                return leftSide;

            Nodo* result = nullptr;
            if(leftSide->stud.getVoto() >= rightSide->stud.getVoto())
            {
                result = leftSide;
                result->next = merge(leftSide->next, rightSide);
            }
            else 
            {
                result = rightSide;
                result->next = merge(leftSide,rightSide->next);
            }
            return result;
        }

        Nodo* mergeSort(Nodo* head)
        {
            if(head==nullptr || head->next==nullptr)
                return head; //caso base: 0 o 1 elementi
            
            Nodo* leftSide = getMiddle(head);
            Nodo* rightSide = leftSide->next; 
            leftSide->next = nullptr; //spezzo i due lati

            leftSide = mergeSort(head); //lato sinistro viene successivamente divisa da inizio (head) fino a leftSide (middle)
            rightSide = mergeSort(rightSide); //da successivo di leftSide (middle) fino alla fine (nullptr)

            return merge(leftSide,rightSide); //riunisco i due lati
        }

        //Inserimento mantenendo l’ordine decrescente per voto
        void push(const string& nome, const int& voto)
        {
            Nodo* nuovo = new Nodo(nome,voto);
            if(head==nullptr)
            {
                nuovo->next = head; //head->nullptr
                head = nuovo; //nuovo->nullptr
                return;
            }

            //altrimenti, ci sono già elementi nella lista: 
            
            //Inserimento:
            nuovo->next = head;
            head = nuovo;

            //Ordinamento --> uso algoritmo di Ordinamento MergeSort
            head = mergeSort(head);
        }

        void stampa()
        {
            Nodo* current = head;
            bool check = false;
            while(current != nullptr)
            {
                if(current->stud.getVoto() < 18 && check == false)
                {
                    cout << "\n--- Studenti con voto insufficiente: ---" << endl;
                    check = true;
                }
                cout << current->stud << endl;
                current = current->next;
            }   
        }
        
        int cerca(const string& key)
        {
            int result = 0;
            Nodo* current = head;
            while(current) // equivale a scrivere: current != nullptr
            {
                if(current->stud.getNome() == key)
                {
                    cout << current->stud << endl;
                    result++;
                }
                current = current->next;
            }
            cout << "Studenti trovati: ";  
            return result;
        } 

        int cancella(const string& key)
        {
            int result = 0;

            //caso testa
            while(head != nullptr && head->stud.getNome() == key)
            {
                Nodo* temp = head;
                head = head->next;
                delete temp;
                result++;
            } 
            //altra parte della lista
            Nodo* current = head; //scorre dalla cima fino alla fine
            Nodo* prev = nullptr; //scorre sempre dietro current --> serve a riconnetere il nodo prima a quello successivo in caso di cancellazione: prev -> current -> current->next

            while(current)
            {
                if(current->stud.getNome() == key)
                {
                    Nodo* temp = current;
                    current = current->next;
                    prev->next = current;
                    delete temp;
                    result++;
                }
                else //vado al nodo successivo
                {
                    prev = current;
                    current = current->next;
                }
            }
            cout << "Studenti eliminati: ";  
            return result;
        }
   
};

/* Lista funzioni classe Lista:

void stampa(); --> stampa lista
void push(string,voto); --> inserisci elemento e ordinalo nella lista
int cerca(string key); --> ritorna numero persone trovate
int cancella(string key); --> elimina tutti i nodi con quel nome, ritorna numero elementi cancellati

*/

int main()
{
    //1 --> creazione e inserimento ordinato valori Lista
    cout << "Inserimento dei voti nella tabella e ordinamento degli studenti per ordine.\n" << endl;
    Lista l;
    l.push("Gino",22);
    l.push("Topogiggio",30);
    l.push("Gianni",18);
    l.push("Capibara",20);
    l.push("Ella",30);
    l.push("Ella",31); //Conta come 30 e lode!
    l.push("Mario",19);
    l.push("Nino",25);
    l.push("U Nannu",29);
    l.push("A Nanna", 27);
    l.push("U ziu",10);
    l.push("Suggitta",17);

    cout << "Stampa tabella:" << endl;
    //2 --> stampa 
    l.stampa();

    //3 --> ricerca
    string key = "Ella";
    cout << "------------------------------\n\nRicerca studente di nome: " << key << "\n" << l.cerca(key) << endl;
    
    //4 --> cancella
    key = "Suggitta";
    cout << "------------------------------\n\nElimina studenti con nome: " << key << "\n" << l.cancella(key) << endl;
    //Controllo:
    l.stampa();
    return 0;
}


