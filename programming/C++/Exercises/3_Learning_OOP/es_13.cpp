/* 🧪 Esercizio Overload (20-30 min)

1. Crea la classe Frazione(a, b)

2. Implementa:
    <+> operator+ per somma frazioni
    <+> operator== per confronto
    <+> operator<< per stampa

3. Usa gcd(a,b) ("Greatest Common Divisor", ovvero: "Massimo Comune Divisore") per semplificare automaticamente le frazioni

🔥 Curiosità extra
Se non stai usando C++17 o superiore, la funzione std::gcd non esiste! In quel caso dovresti implementarla tu stesso, ad esempio con l’algoritmo di Euclide:

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

*/

#include <iostream>
using namespace std;

//si suppone che la Frazione possa solamente essere di interi positivi, in quanto non specificato diversamente
class Frazione
{   
    private:
        unsigned int num;
        unsigned int den;
    public:
        Frazione(unsigned int x,unsigned int y) : num(x), den(y) {
            if(y == 0) throw invalid_argument("Denominatore non puo' essere zero.\n");
        }
        Frazione() : num(0), den(1) {}
        ~Frazione() { cout << "Distruttore chiamato!" << endl; }
        Frazione(const Frazione& fraz) : num(fraz.num), den(fraz.den) {} //Costruttore di Copia

        /*
        
            3   2    3 + 4     7                                                3   2   6 + 8    14   7
            - + -  = -----  =  -  --> lo vogliamo grezzo senza semplificazioni: - + - = ----- = --- = -  ma vogliamo risparmiarci la semplificazione 
            4   2      4       4                                                4   2     8      8    4
        
        */
        //2.1
        Frazione operator+(const Frazione& altraFraz) 
        {
            unsigned int newNum = (num * altraFraz.den) + (altraFraz.num * den); 
            unsigned int newDen = den * altraFraz.den;
            return Frazione(newNum,newDen);
        }

        //2.2 
        bool operator==(const Frazione& altraFraz)
        {
            return num == altraFraz.num && den == altraFraz.den;
        }

        //2.3 --> per divertimento la facciamo anche fuori dalla funzione con friend
        /* 
        ostream& operator<<(const ostream& out, const Frazione& fraz)
        {
            out << "(" << num << "/" << den << ")";
            return out;
        }
        */
       friend ostream& operator<<(ostream&, const Frazione&); //dichiarazione interna alla classe
};

ostream& operator<<(ostream& out, const Frazione& fraz) //definizione fuori dalla classe
{
    out << "(" << fraz.num << "/" << fraz.den << ")";
    return out;
}


int main()
{
    Frazione f1(3,4);
    Frazione f2{4,3};
    Frazione copia(f1);
    //2.3
    cout << "Frazione 1: " << f1 << "; Frazione 2: " << f2 << endl;
    //2.1
    Frazione f3 = f1 + f2;
    cout << "Somma delle due frazioni uguale = " << f3 << endl;
    //2.2 
    cout << "Frazione copia di f1 = " << copia << endl; 
    cout << "Sono uguali? " << (copia==f1 ? "Sono uguali!" : "Non sono uguali...") << endl;
    cout << "Fine programma.\n" << endl;

    return 0;
}