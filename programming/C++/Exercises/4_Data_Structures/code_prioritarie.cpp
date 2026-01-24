/*  

    -----------------------------
    |     CODA PRIORITARIA      | 
    -----------------------------


🎯 OBIETTIVO:
Simulare un sistema in cui gli elementi vengono serviti in base alla **priorità** (valore intero più alto = più urgente), 
e non semplicemente nell’ordine di arrivo.

📌 FUNZIONAMENTO:
- Ogni elemento ha:
    <+> un valore (es. stringa: "Email urgente")
    <+> una priorità (es. intero: 4)

- Gli elementi vengono inseriti in **ordine decrescente di priorità**.
    ⏫ L'elemento con **priorità più alta va in testa**
    ⏬ Gli altri vengono inseriti dietro a quelli più urgenti

📚 STRUTTURA:
La coda è implementata come una **lista collegata ordinata**, dove:
    <+> la testa (head) contiene l’elemento più urgente
    <+> l’operazione `enqueue()` inserisce al posto giusto
    <+> `dequeue()` rimuove l’elemento in testa
    <+> `peek()` stampa il più urgente senza rimuoverlo
    <+> `print()` stampa l’intera coda ordinata

🛠️ METODI RICHIESTI:

    ✅ enqueue(valore, priorita) → inserisce ordinato
    ✅ dequeue()                 → rimuove elemento più urgente
    ✅ peek()                    → visualizza il primo
    ✅ print()                   → stampa tutta la coda

🔁 ESEMPIO DI COMPORTAMENTO:
    Enqueue:
        ("Stampare documento", 2)
        ("Aggiornamento sistema", 5)
        ("Email urgente", 4)
        ("Backup", 1)

    Output:
        [5] Aggiornamento sistema → [4] Email urgente → [2] Stampare documento → [1] Backup → NULL

    Dopo dequeue():
        [4] Email urgente → [2] Stampare documento → [1] Backup → NULL

💡 COMPLESSITÀ:
    - Inserimento ordinato (enqueue): O(n)
    - Rimozione in testa (dequeue): O(1)
    - Peek in testa: O(1)
    - Stampa: O(n)

🎓 RICHIESTO ALL’ESAME:
    <+> Saper costruire e ordinare la lista dinamicamente
    <+> Saper gestire puntatori e inserimenti ordinati
    <+> Saper spiegare come funziona la priorità decrescente
    <+> Conoscere differenze con le code normali e le priority_queue STL
*/

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Nodo
{   
    private:
        T valore;
        int priorita;
        Nodo<T>* next;
    public:
        Nodo(const T& val, int prio) : valore(val), priorita(prio) {}

        const T& get_valore() const { return valore; }
        const int& get_priorita() const { return priorita; }
        Nodo* get_next() const { return next; } 
        
        void set_next(Nodo* n) { next = n; }

        friend ostream& operator<<(ostream& os, const Nodo<T>& nodo)
        {
            os << "[" << nodo.get_priorita() << "] " << nodo.get_valore();
            return os;
        }
};

template <typename T>
class CodaPrioritaria
{
    private:
        Nodo<T>* front;
        //Nodo* rear; //non lo usiamo --> gli oggetti vengono inseriti per priorità!
    public:
        CodaPrioritaria() : front(nullptr) {}

        bool isEmpty() const
        {
            return front == nullptr;
        }

        CodaPrioritaria* enqueue(const T& valore, const int& priorita)
        {
            Nodo<T>* nuovo = new Nodo<T>(valore,priorita);

            //inserimento in testa (primo elemento coda) o con priorità più bassa
            if(front == nullptr || front->get_priorita() < nuovo->get_priorita())
            {
                nuovo->set_next(front);
                front = nuovo;
                return this;
            }

            //altrimenti cerchiamo punto giusto: scorrimento coda fino al punto corretto
            Nodo<T>* current = front;
            while(current->get_next() != nullptr && current->get_next()->get_priorita() > nuovo->get_priorita() )
            {
                current = current->get_next();
            }

            //quando il while finisce abbiamo trovato il posto adatto: piazziamo il nuovo nodo
            nuovo->set_next(current->get_next());
            current->set_next(nuovo);

            return this;
        }

        CodaPrioritaria* dequeue()
        {
            if(isEmpty())
            {
                cout << "Coda vuota!" << endl;
                return this;
            }

            Nodo<T>* temp = front;
            front = front->get_next();
            delete temp;

            return this;
        }

        ~CodaPrioritaria()
        {
            cout << "Chiamato distruttore CodaPrioritaria." << endl;
            while(!this->isEmpty())
            {
                this->dequeue();
            }
        }

        Nodo<T>* peek() const
        {
            if(front==nullptr)
            {
                cout << "Coda vuota!" << endl;
                return front;
            }
            return front;
        }

        friend ostream& operator<<(ostream& os, CodaPrioritaria<T>& coda)
        {
            Nodo<T>* current = coda.peek(); 
            
            while(current != nullptr)
            {
                os << *current << " -> "; //uso l'altro operatore per stampa nodo 
                current = current->get_next();
            }
            os << "fine"; //utile solo per visualizzare fine della coda 
            return os;
        }

};
/*
friend ostream& operator<<(ostream& os, Nodo<T>& nodo)
{
    os << "[" << nodo.get_priorita() << "] " << nodo.get_valore();
    return os;
}

friend ostream& operator<<(ostream& os, CodaPrioritaria<T>& coda)
{
    Nodo<T>* current = coda.peek(); 
    
    while(current != nullptr)
    {
        os << *current << " "; //uso l'altro operatore per stampa nodo 
        current = current->get_next();
    }
    return os;
}*/

int main()
{
    CodaPrioritaria<string>* coda = new CodaPrioritaria<string>();

    coda->enqueue("Stampare documento",2)->
    enqueue("Aggiornamento del sistema",5)->
    enqueue("Email urgente",4)->
    enqueue("Backup",1)->
    enqueue("Comunicazione dirigenti",5);

    cout << "Contenuto iniziale Coda Prioritaria:\n" << *coda << endl;

    coda->dequeue();

    cout << "\nContenuto Coda dopo un dequeue:\n" << *coda << endl;

    cout << "\nElemento adesso in testa: " << *(coda->peek()) << endl;

    delete coda;

    cout << "Fine programma." << endl;
    return 0;
}
