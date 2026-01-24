/*
    -----------------------------
    |      Pile Stack/queue     |
    -----------------------------

Vedremo:

    - Concetto di LIFO (Last-In, First-Out) e FIFO (First-In, First-Out)

    - Implementazioni classiche via array e via liste

    - Operazioni fondamentali:
        push(), pop() (per stack)
        enqueue(), dequeue() (per queue)

    - Vantaggi/svantaggi di ogni struttura

    - Come usare queste strutture per simulare chiamate ricorsive (conversione ricorsione → iterazione)

--------------------------------------------------------------------------------

    (1) 🧠 Cosa è una Pila (Stack)? 
        Una pila è una struttura dati LIFO, ovvero:
        Last In, First Out – L'ultimo elemento inserito è il primo a uscire.

        🔥 Diversa dalla Lista semplice: questa infatti non ha regole, mentre la Pila si --> LIFO 

    ->            Lista:
                head->next->next->next ---->> nullptr
                Rosso->Giallo->Verde->Blu->...>nullptr

    ->            Pila:
                -inizio-
                Rosso (ultimo inserito)
                Giallo
                Verde
                Blu
    ->            -fine- (nullptr)

    📦 Immaginala come una pila di scatole:
        <+>  Metti una scatola (push)
        <+>  Togli l’ultima messa (pop)
        <!>  Non puoi togliere una scatola dal mezzo: solo l’ultima.

    🔁 Operazioni fondamentali:

    -------------------------------------------------------------------
    |  Operazione	|    Descrizione                                  |
    -------------------------------------------------------------------
    |  push(x)	    |    Inserisce x in cima alla pila                |
    |  pop()	    |    Rimuove l’elemento in cima                   |
    |  peek()	    |    Ritorna l’elemento in cima (senza toglierlo) |
    |  isEmpty()	|    Verifica se la pila è vuota                  |
    -------------------------------------------------------------------

    🧪 Dove si usa una Pila?
    <+> Chiamate di funzione → Stack di attivazione (call stack)
    <+> Parentesi bilanciate, espressioni infisse/postfisse
    <+> Backtracking (es. labirinti, DFS)
    <+> Browser (torna indietro)
    <+> Undo/Redo in editor di testo

    ⚙️ Implementazione: Pila con Lista Concatenata
    Perché con lista? Perché è dinamica, non ha bisogno di dimensione fissa come un array.

    ✅ Vantaggi:
    <+> Cresce dinamicamente
    <+> Operazioni in O(1)

    */



#include <iostream>
using namespace std;

//📦 Struttura del Nodo
class Nodo
{
    public:
        int valore;
        Nodo* next;

        Nodo(int value) : valore(value), next(nullptr) {}
};

class Stack
{
    private: 
        Nodo* top;
    
    public:
        Stack() : top(nullptr) {}
        ~Stack() 
        {
            while(!isEmpty()) //<-- funzione isEmpty() scritta sotto
                pop(); 
        }

        Stack(const Stack& s) //costruttore di copia
        {
            top = nullptr;

            //pila temporanea per preservare ordine
            Nodo* current = s.top;
            Stack temp;

            //1. copia
            while(current != nullptr)
            {
                temp.push(current->valore);
                current = current->next;
            }

            //2. rimetto tutto nel nuovo stack 
            while(!temp.isEmpty())
            {
                this->push(temp.lookTop());
                temp.pop();
            }
        }

        //Funzioni utili:
 
        bool isEmpty() const  //non essenziale ma semplifica scrittura
        {
            return top == nullptr;
        }

        void push(int value)
        {
            Nodo* nuovo = new Nodo(value);
            nuovo->next = top;
            top = nuovo;
        }

        int pop()
        {
            if(isEmpty())
            {
                throw runtime_error("Pila vuota!");
            }
            Nodo* temp = top;
            int valoreNodo = temp->valore;
            top = top->next;
            delete temp;
            return valoreNodo;
        }

        int lookTop() const 
        {
            if(isEmpty())
            {
                throw runtime_error("Pila vuota!");
            }

            return top->valore;
        }

        void stampaStack(Stack copia)
        {
            while(!copia.isEmpty())
            {
                cout << "[" << copia.lookTop() << "] ";
                copia.pop();
            }
            cout << endl;
        }

        //Funzione di ordinamento
        void ordinaStack()
        {
            Stack tempStack;

            while(!this->isEmpty())
            {
                int current = this->lookTop();
                this->pop();
                
                //sposta gli elementi più grandi di current indietro sullo Stack originale
                while(!tempStack.isEmpty() && tempStack.lookTop() > current) //> current --> ordine crescente
                {
                    this->push(tempStack.lookTop());
                    tempStack.pop();
                } 

                //Inserimento di current al punto giusto
                tempStack.push(current);
            }

            //Riporta elementi ordinati sullo Stack originale
            while(!tempStack.isEmpty())
            {
                this->push(tempStack.lookTop());
                tempStack.pop();
            }
        }
};



int main()
{
    //Caso particolare: ordinamento di una pila con un'altra pila di supporto!
    Stack pila;

    pila.push(4);
    pila.push(2);
    pila.push(7);
    pila.push(1);
    pila.push(5);
    pila.push(8);

    cout << "Stack iniziale: "; pila.stampaStack(pila);

    pila.ordinaStack();

    cout << "Stack ordinato: "; pila.stampaStack(pila);

    return 0;
}



