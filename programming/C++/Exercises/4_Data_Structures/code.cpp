/*

    --------------------------
    |       CODE (LIFO)      |
    --------------------------
    
    📌 COSA SONO LE CODE?
    Una coda è una struttura dati lineare FIFO:

    First-In, First-Out: il primo elemento inserito è il primo ad essere rimosso.

    📦 USO COMUNE
    ->Le code sono usate quando è importante rispettare l’ordine di arrivo:
    Esempi:
        <+>  Code di stampa 🖨️
        <+>  Task scheduler / gestione processi
        <+>  Algoritmo di BFS (Breadth-First Search) su grafi
        <+>  Simulazioni di eventi (es. cassa supermercato)
        <+>  Buffer di rete
        <+>  Sistemi di messaggistica 📬
        <+>  Pianificazione di processi in un OS 🧠
        <+>  Simulazioni di code reali (clienti, veicoli, ecc.)

    🧠 STRUTTURA INTERNA

    Una coda ha due estremi:

    ----------------------------------------------------------------------------
    | Estremo                        |  Funzione                               |
    |--------------------------------|-----------------------------------------|
    | front (testa)	                 |  da dove si rimuove (pop() / dequeue()) |
    | rear (coda)	                 |  dove si inserisce (push() / enqueue()) |
    ----------------------------------------------------------------------------

    🛠️ OPERAZIONI FONDAMENTALI:

        --------------------------------------------------------------------------------------------------         
        |  Operazione   	     |   Significato                           |  Complessità operazioni     |
        |------------------------|-----------------------------------------|-----------------------------|                                                  
        |  push(x) o enqueue(x)	 |   Inserisce x in fondo alla coda        |             O(1)            |
        |  pop() o dequeue()	 |   Rimuove l’elemento in testa           |             O(1)            |
        |  front()	             |   Legge il primo elemento               |             O(1)            |
        |  back()	             |   Legge l’ultimo elemento               |             O(1)            |
        |  isEmpty()               |	 Verifica se la coda è vuota       |             O(1)            |
        |  size()                | 	 Restituisce il numero di elementi     |             O(1)            |
        --------------------------------------------------------------------------------------------------

    🔄 DIFFERENZA TRA CODA E PILA:
    
        ----------------------------------------------------------------------
        |                  |       Pila (Stack)	    |   Coda (Queue)         |
        |------------------|------------------------|------------------------|
        | Tipo accesso	   |       LIFO	            |   FIFO                 |
        | Inserimento	   |       push() (top)	    |   push() (rear)        |
        | Rimozione	       |       pop() (top)	    |   pop() (front)        |
        | Accesso interno  |	   limitato	        |   limitato             |
        | Uso tipico	   |       Undo, Backtrack	|   Code reali, eventi   |
        ----------------------------------------------------------------------

    💡 CONCETTI COLLEGATI CHE POTREBBERO USCIRE:
        --> queue ≠ priority_queue
        --> Non c'è iterator perché non puoi scorrere la queue (non è pensata per essere attraversata!)
        --> Puoi simulare una coda con due stack (esercizio molto gettonato)

    🔥 VARIANTI DELLA CODA:
        -------------------------------------------------------------------------------------------
        | Tipo di coda	                       |  Descrizione                                     |
        |--------------------------------------|--------------------------------------------------|
        | Coda circolare	                   |  Usa array come buffer circolare                 |
        | Coda doppiamente terminata (deque)   |  Inserimento e rimozione da entrambi i lati      |
        | Coda di priorità	                   |  L'elemento con priorità più alta esce per primo |
        | Coda concorrente	                   |  Supporta accesso da più thread                  |
        -------------------------------------------------------------------------------------------

    🎓 PER L’ESAME
        <+>  Saper implementare una coda con liste collegate (manuale)
        <+>  Conoscere operazioni base (push/pop/front)
        <+>  Capire quando usare una coda invece di una pila
        <+>  Saper spiegare la differenza tra:
        <+>  queue, deque, priority_queue

        Esempio di coda:

            coda.enqueue(10);
            coda.enqueue(20);
            coda.enqueue(30);
            Significa: 

                FRONT → [10] → [20] → [30] → NULL ← REAR
        
            coda.dequeue();  // rimuove 10

                FRONT → [20] → [30] → NULL ← REAR       
*/

#include <iostream>
using namespace std;

class Nodo
{
    public:
        int valore;
        Nodo* next;

        Nodo(int v) : valore(v), next(nullptr) {}
};

class Queue //Ricorda che è di tipo FIFO First In First Out (le Pile sono invece LIFO Last In First Out)
{
    private:
        Nodo* front;
        Nodo* rear;

    public:
        Queue() : front(nullptr), rear(nullptr) {}

        ~Queue()
        {
            cout << "Evocato distruttore Queue" << endl;
            while(!isEmpty())
                dequeue(); //funzione di liberazione nodi della coda (queue)
        }

        bool isEmpty()
        {
            return front==nullptr;
        }


        void enqueue(int v)
        {
            cout << "<+> Inserisco [" << v << "] nella Coda." << endl;  
            Nodo* nuovo = new Nodo(v);
            if(isEmpty())
                front = rear = nuovo;
            else
            {
                rear->next = nuovo;
                rear = rear->next;
            } //FIFO --> First In First Out --> inserimento sempre in rear
        }

        int dequeue()
        {
            cout << "<-> Elimino elemento [" << front->valore << "] dalla coda" << endl;
            if(isEmpty())
                throw runtime_error("<!> Tentativo di svuotamento coda vuota!");

            Nodo* temp = front;
            int value = temp->valore;
            front = front->next;

            if(front == nullptr)
                rear == nullptr; //Coda terminata 
            
            delete temp;
            return value;
        }

        int peek()
        {
            if(isEmpty())
                throw runtime_error("<!> Tentativo di peek() a coda vuota");

            return front->valore;
        }

        void stampa()
        {
            Nodo* current = front;
            cout << "<?> Stato della coda: ";
            if(current == nullptr) 
                cout << "-- coda vuota --" << endl;
            while(current != nullptr)
            {
                cout << "[" << current->valore << "] ";
                current = current->next;  
            }
            cout << endl;
        }

        void popCoda()
        {
            cout << "</> Elimino tutta la coda." << endl;
            while(!isEmpty())
            {
                dequeue();
            }
        }
};


int main()
{
    Queue coda;
    coda.enqueue(10);
    coda.enqueue(15);
    coda.enqueue(20);
    coda.enqueue(30);

    coda.stampa();
    cout << "Primo elemento ad uscire (FIFO): " << coda.peek() << endl;

    coda.dequeue();

    coda.stampa();

    coda.enqueue(5);

    coda.stampa();

    coda.dequeue();

    coda.stampa();

    coda.popCoda();

    coda.stampa();

    coda.enqueue(11);

    coda.stampa();


    return 0;
}
