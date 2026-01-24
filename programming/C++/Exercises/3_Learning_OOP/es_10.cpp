/*

🧪 Mini esercizio sui vectors:

1. Crea un vector<int>;
2. Inserisci i numeri da 1 a 10
3.Stampa la somma di tutti gli elementi
4.Rimuovi l’ultimo elemento con pop_back()
5.Stampa gli elementi rimasti con un range-based for

*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> a;
    for(int i=1;i<=10;i++)
    {
        a.push_back(i); //Aggiunge valore in fondo al vettore
    }

    cout << "Stampa vettore:" << endl;
    for(int n : a)
    {
        cout << n << " ";
    }
    cout << "\nRimozione ultimo elemento:" << endl;

    a.pop_back(); //rimuove ultimo elemento del vettore

    cout << "Stampa vettore:" << endl;
    for(int n : a)
    {
        cout << n << " ";
    }

    
    cout << "\nStampa elemento nella cella 2 con controllo su accesso: " << a.at(2) << endl; //.at() permette accesso sicuro con controllo se sto puntando fuori dal limite
    //cout << "\nStampa elemento nella cella 2: " << a.at(12) << endl; //Output: terminate called after throwing an instance of 'std::out_of_range'
                                                                        //what():  vector::_M_range_check: __n (which is 12) >= this->size() (which is 9)
    cout << "\nStampa elemento nella cella 5 senza controllo su accesso: " << a[5] << endl;
    cout << "Dimensione del vettore: " << a.size() << endl;
    cout << "Elemento in cima al vettore (primo elemento): " << a.front() << endl;
    cout << "Elemento in fondo al vettore (ultimo elemento): " << a.back() << endl;

    cout << "Ho finito: svuoto il vettore." << endl;
    a.clear();
    cout << "Controllo se il vettore e' stato svuotato correttamente:" << endl;
    if(a.empty()) 
        cout << "Il vettore e' stato svuotato correttamente (a.empty() == true)." << endl;
    else cerr << "Vettore non svuotato correttamente. ERRORE!" << endl;

    return 0;
}

/* Ricordiamo:

 🎯 Metodi fondamentali

    ---------------------------------------------------------------------------------------------------------------
    |      Metodo	       |             Significato                     	          |         Esempio           |
    |                      |                                                          |                           |
    |    push_back(x)	   |         Aggiunge x in fondo al vettore                   |     numeri.push_back(10); |
    |    pop_back()	       |         Rimuove l’ultimo	                              |     numeri.pop_back();    |
    |    size()	           |         Ritorna il numero di elementi	                  |     numeri.size();        |
    |    empty()	       |         Ritorna true se è vuoto	                      |     if (numeri.empty())   |
    |    clear()	       |         Svuota il vettore	                              |     numeri.clear();       |
    |    at(i)	           |         Accesso sicuro (controlla il limite)	          |     cout << numeri.at(2); |
    |    operator[]	       |         Accesso diretto (più veloce, ma senza controllo) |	    numeri[2] = 10;       |
    |    front()	       |         Ritorna il primo elemento	                      |     numeri.front();       |
    |    back()	           |         Ritorna l’ultimo elemento	                      |     numeri.back();        |
    ---------------------------------------------------------------------------------------------------------------
*/