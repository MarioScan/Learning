/* 🧪 ESERCIZIO – Gestione di richieste in una pila prioritaria
🎯 Obiettivo

--> Simula un sistema di gestione richieste dove:

Ogni Richiesta ha:
    <+>  string descrizione
    <+>  int priorità (più alto = più urgente)

<!> Le richieste vengono inserite in ordine arbitrario
<!> La pila deve sempre mantenere ordine decrescente di priorità
<=> Quindi la richiesta con priorità più alta è in cima

Implementa:
  -  push() → inserisce mantenendo ordine
  -  pop() → rimuove la richiesta più urgente
  -  top() → visualizza la richiesta in cima
  -  printAll() → stampa tutte le richieste 
*/

#include <iostream>
#include <string> //mi serve per la funzione to_string() (voglio restituire priorità insieme a descrizione)
using namespace std;

class Nodo
{
    public:
        int priority;
        string descrizione;
        Nodo* next;
        
        Nodo(const int& priorita, const string& desc) : priority(priorita), descrizione(desc), next(nullptr) {}
};

class Stack
{
    private:
        Nodo* top;
    public: 
        Stack() : top(nullptr) {}

        ~Stack() 
        {
            while(!this->isEmpty())
                this->pop(); 
        }

        Stack(Stack& s)
        {
            /* VIOLA IL PRINCIPIO LIFO? (Last In First Out) 
            "L'ultimo che entra è il primo che esce" 
            vale quando usi la pila per eseguire operazioni,
            non quando la stai copiando, duplicando o analizzando dall'esterno. 
            */
            top = nullptr;
            Stack temp;
            Nodo* current = s.top;

            while(current != nullptr) //copia ribaltata pila in pila temporanea
            {
                temp.push(current->priority,current->descrizione);
                current = current->next;
            }

            while(!temp.isEmpty()) //inserimento nella Pila di input
            {
                push(temp.top->priority,temp.top->descrizione);
                temp.pop();
            }
        }

        bool isEmpty()
        {
            return top == nullptr;
        }

        void push(int priorita, string desc)
        {
            Stack temp; //stack temporaneo per ordinamento

            while(!isEmpty() && top->priority > priorita)
            {
                temp.push(top->priority, top->descrizione);
                this->pop(); //pila originale
            }

            // Inserisco il nuovo elemento in cima come dovrebbe 
            Nodo* nuovo = new Nodo(priorita,desc);
            nuovo->next = top; //se è vuoto il next -> nullptr (IMPORTANTE)
            top = nuovo;
            
            //Ri-inserisci gli elementi salvati nella pila temporanea
            while(!temp.isEmpty())
            {
                this->push(temp.top->priority, temp.top->descrizione);
                temp.pop();
            }

            /* Quindi ogni volta che abbiamo un elemento di priorità superiore (indice superiore)
            Salviamo la nostra pila in una temporanea, cancelliamo tutta la pila e inseriamo il valore
            dopodiché "rimettiamo tutto dentro la pila".
            */
        }
        
        string pop()
        {
            if(isEmpty())
                throw runtime_error("Pila vuota!");

            Nodo* temp = top;
            string data = top->descrizione;
            data = "[" + to_string(top->priority) + "] --> " + data; 
            top = top->next;

            delete temp;
            return data;
        }

        void printAll(Stack s)
        {
            //si presume si voglia mantenere la Pila per sicurezza
            //utilizziamo allora un costruttore di copia Pila

            if(isEmpty())
            {
                cout << "Pila vuota!" << endl;
                return;
            }

            while(!s.isEmpty())
            {
                cout << s.pop() << endl;
            }
        }
};

int main()
{
    Stack pila;
    pila.push(10,"Ciao");
    pila.push(1,"Eila'");
    pila.push(20,"Messaggio urgente.");
    pila.push(30,"Collega infortunato.");

    pila.printAll(pila);

    return 0;
}