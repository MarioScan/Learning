/*

    -----------------------
    |       Classi        |
    ----------------------- 

♻️ Overloading di metodi

--> Due o più funzioni con lo stesso nome, ma parametri diversi

*/

#include <iostream>
using namespace std;

class Sommatore
{
    public:
        int somma(const int& a,const int& b){ return a + b;}
        double somma(const double& a,const double& b) { return a + b; }
        string somma(const string& a,const string& b) { return a + b; }  
        //nelle stringhe equivale ad una concatenazione di stringhe! 
        //es. --> "Ciao" + "Mondo!" = "CiaoMondo!"

};

/* 
Nella classe Sommatore:
📋 Cosa NON hai qui?
Nella classe Sommatore non ci sono attributi (dati).

Un attributo è una variabile interna alla classe, ad esempio:

class Sommatore {
    private:
        int conteggioOperazioni; // Questo è un attributo
    ...
};
Nel tuo caso, la classe è "stateless", cioè NON ha memoria interna: ogni volta fa solo un'operazione e basta.
                            ^^^^^^^         ^^^^^^^^^^^^^^^^^^^^^^                ^^^^^^^^^^^^^^^^^^
Quindi abbiamo: 

✅ Metodi pubblici: accessibili ovunque
❌ Nessun attributo in questo esempio
✅ Overloading: stesso nome, diversi parametri
*/

int main()
{
    Sommatore sum;
    int calcolo1 = sum.somma(3,4); //somma di interi
    double calcolo2 = sum.somma(4.345,33.244); //somma di double
    string calcolo3 = sum.somma("Ciao", "Mondo!"); //somma di stringhe

    cout << "Somma di int: " << calcolo1 << endl;
    cout << "Somma di double: " << calcolo2 << endl;
    cout << "Somma di string: " << calcolo3 << endl;

    return 0;
}

