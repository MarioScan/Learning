/* 
🧪 ESERCIZIO – Verifica di parentesi bilanciate usando una pila
Obiettivo:
    Scrivere un programma che verifichi se una stringa di parentesi è correttamente bilanciata.
    Le parentesi possono essere:
    ( ) — parentesi tonde
    [ ] — parentesi quadre
    { } — parentesi graffe

✅ Esempi:
Input	    |   Output
{[()()]}    |	✅ Bilanciata
{[(])}	❌  |   NON bilanciata
(((())))    |   ✅ Bilanciata
[({})](	❌  |   NON bilanciata

🔧 REQUISITI:
Implementare una classe Stack con:
    <+> push(char)
    <+> pop()
    <+> lookTop()
    <+> isEmpty()

La verifica avviene scorrendo la stringa carattere per carattere:
1. Se il carattere è una parentesi aperta, va inserita nello stack.
2. Se è una parentesi chiusa, bisogna controllare se corrisponde all’ultima parentesi aperta nello stack.
    --> Se sì: pop()
    --> Se no: errore → stringa non bilanciata.

📜 Consegnare:
   1. Classe Stack completa
   2. Funzione bool parentesiBilanciate(string s)
   3. main() con 3 test

*/

#include <iostream>
#include <string>
using namespace std;

class Nodo
{
    public:
        char valore;
        Nodo* next;

        Nodo(const char& value) : valore(value), next(nullptr) {}
};

class Stack
{
    private:
        Nodo* top;
    public:
        Stack() : top(nullptr) {}
        ~Stack() 
        {
            while(!isEmpty())
                this->pop();
        }

        Stack(Stack& s)
        {
            top = nullptr;

            Nodo* current = s.top;
            Stack temp;

            while(current != nullptr)
            {
                temp.push(current->valore);
                current = current->next;
            }

            while(!temp.isEmpty())
            {
                this->push(temp.lookTop());
                temp.pop();
            }
        }

        bool isEmpty()
        {
            return top == nullptr;
        }

        void push(char c)
        {
            Nodo* nuovo = new Nodo(c);
            nuovo->next = top;
            top = nuovo;
        }

        char pop()
        {
            if(top==nullptr) //o if(isEmpty())
            {
                throw runtime_error("Pila vuota!");
            }
            Nodo* temp = top; //mi serve per liberare la memoria dinamica
            char valoreNodo = top->valore;
            top = top->next;
            delete temp;
            return valoreNodo;
        }

        char lookTop()
        {
            if(isEmpty())
                throw runtime_error("Pila vuota!");

            char valoreTop = top->valore;
            return valoreTop;
        }

        friend bool parentesiBilanciate(Stack*, string);

        const char& getChar() const { return top->valore; }
};

bool parentesiBilanciate(Stack* pila,string s)
{
    /*  La verifica avviene scorrendo la stringa carattere per carattere:
        1. Se il carattere è una parentesi aperta, va inserita nello stack.
        2. Se è una parentesi chiusa, bisogna controllare se corrisponde 
        all’ultima parentesi aperta nello stack.
            --> Se sì: pop()
            --> Se no: errore → stringa non bilanciata.   */

    for(int i=0;i<s.length();i++)
    {
        char c = s[i];
        if(c == '{' || c == '[' || c == '(')
            pila->push(c);
        
        else if(c == '}' || c == ']' || c == ')')
        {
            if(pila->isEmpty()) 
                return false; //allora è necessariamente SBILANCIATA 
            
                char tempTop = pila->lookTop();
                if( (c == '}' && tempTop != '{') || ( c == ']' && tempTop != '[') || ( c == '(' && tempTop != '('))
                    return false; 
            pila->pop(); 
            // 1. {[( --> ) allora '(' è il top quindi ) va bene pop( '(' ) 
            // 2. {[ --> ] OKAY
            // 3. { --> ] NON BILANCIATA
        }
    }
    return pila->isEmpty();
    /* perché una stringa può essere bilanciata
    solo se la pila è vuota alla fine
    (cioè tutte le parentesi aperte hanno avuto la loro chiusura). */
}

int main()
{
    string test[] = {"{[()()]}", "{[(])}", "(((())))", "[({})]("};
    for(string s : test)
    {
        Stack pila;
        cout << s << " ---> ";
        if(parentesiBilanciate(&pila, s))
            cout << "Bilanciata." << endl;
        else cout << "Non bilanciata." << endl;
    }
    return 0;
}