/* 🧪 Esercizio Template (15 min)
Crea una funzione template scambia() che scambia due variabili generiche.

Crea una classe template Coppia<T> che contiene due oggetti generici a, b, e ha un metodo stampa().
*/

#include <iostream>
using namespace std;

template <typename T> 
void scambia(T& a, T& b)
{
    T temp = b;
    b = a;
    a = temp;
}

template <typename T>
class Coppia
{
    private:
        T x;
        T y;
    public:
        Coppia(T n1, T n2) : x(n1), y(n2) {}

        const T& get_x() const { return x; }
        const T& get_y() const { return y; }

        void set_x(const T& new_x) { x = new_x; } 
        void set_y(const T& new_y) { y = new_y; }
        
        void stampa()
        {
            cout << "(" << x << "," << y << ")" << endl;  
        }

        void stampaFuori(); //Propotipo funzione che dichiaro fuori dalla funzione

        void swappa() //funzione scambia ma all'interno della classe, per vedere la differenza
        {
            T temp = y;
            y = x;
            x = temp;
        }
};

template <typename T> //si riscrive ogni volta che creo una funzione / classe con template
void Coppia<T>::stampaFuori()
{
    cout << "Questa e' una funzione di classe definita fuori dalla classe!" << "Ecco la coppia:\nx: " << x << "\ny: " << y << endl;
}

template <typename T>
void scambia(Coppia<T>& couple)
{
    T temp = couple.get_y();
    couple.set_y(couple.get_x());
    couple.set_x(temp);
}



int main()
{
    //1 -> Esempi con la funzione template
    int a = 5, b = 7;
    double x = 3.423, y = 4.1634;
    string p1 = "Ciao" , p2 = "Mondo!";

    cout << "Valori prima dello scambio tramite funzione template di scambio:\n" << "a: " << a << "\nb: " << b << endl;
    cout << "\nx: " << x << "\ny: " << y << endl;
    cout << "\nStringa p1: " << p1 << "\nStringa p2: " << p2 << endl; 

    scambia(a,b);
    scambia(x,y);
    scambia(p1,p2);

    cout << "Valori DOPO dello scambio tramite funzione template di scambio:" << endl;
    cout << "a: " << a << "\nb: " << b << endl;
    cout << "\nx: " << x << "\ny: " << y << endl;
    cout << "\nStringa p1: " << p1 << "\nStringa p2: " << p2 << endl; 


    //2 -> Creazione di oggetti di una classe Template
    cout << "Adesso utilizziamo una classe template Coppia per le medesime operazioni:" << endl;
    Coppia<int> coppia1(10, 20);
    Coppia<double> coppia2(3.14, 4.16);
    Coppia<string> coppia3("Buongiorno","Caffe'?");

    //3 -> Sovraccarico funzione di scambio() per usarla per la classe Coppia:
    coppia1.stampa();
    cout << "Uso funzione esterna alla classe per scambiarli: " << endl;
    scambia(coppia1);
    coppia1.stampa();

    cout << "Provo funzione creata adesso all'interno della classe: " << endl;
    coppia1.swappa();
    coppia1.stampa();
    cout << "Ecco riportati i valori al loro stato originale dopo questo doppio scambio!" << endl;
    coppia2.stampaFuori();


    return 0;
}

