/*
    -----------------------
    |   Liste circolari   | --> EXTRA: NO FINI ESAME PROG 2 
    -----------------------

    ⚙️ COSA SONO LE LISTE CIRCOLARI?
        Una lista circolare è una variante della lista concatenata (linked list), ma con una differenza chiave:
        In una lista normale, l'ultimo nodo punta a nullptr.
        In una lista circolare, l'ultimo nodo punta al primo nodo, formando un cerchio.

    🔁 Due tipi:    
        <+>  Lista semplicemente circolare: ogni nodo ha solo next, e l’ultimo punta al primo.
        <+>  Lista doppiamente circolare: ogni nodo ha next e prev, l’ultimo punta al primo, il primo ha prev che punta all’ultimo.

    📌 A COSA SERVONO?
        Le liste circolari sono usate in contesti dove vuoi un traversal continuo, ad esempio:

        <+>  Giochi (tipo “il prossimo giocatore” → current = current->next)
        <+>  Task scheduling (round robin)
        <+>  Buffer circolari
        <+>  Simulazioni cicliche

    Una lista semplicemente circolare potrebbe essere così:
*/

#include <iostream>
using namespace std;


struct Node {
    int value;
    Node* next;
};

class ListaCircolare {
private:
    Node* tail; // tail->next è il primo nodo
public:
    ListaCircolare() : tail(nullptr) {}

    void inserisciInTesta(int val) {
        Node* nuovo = new Node{val, nullptr};
        if (!tail) {
            nuovo->next = nuovo;
            tail = nuovo;
        } else {
            nuovo->next = tail->next;
            tail->next = nuovo;
        }
    }

    void stampa() {
        if (!tail) return;
        Node* curr = tail->next;
        do {
            cout << curr->value << " ";
            curr = curr->next;
        } while (curr != tail->next);
        cout << endl;
    }

    ~ListaCircolare() {
        if (!tail) return;
        Node* curr = tail->next;
        Node* temp;
        do {
            temp = curr;
            curr = curr->next;
            delete temp;
        } while (curr != tail->next);
    }
};


int main()
{

    return 0;
}