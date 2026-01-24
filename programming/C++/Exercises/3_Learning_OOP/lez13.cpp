/*

    -------------------------------------
    |    Overloading degli operatori    |
    -------------------------------------

    🧠 Cos’è?

    In C++ puoi ridefinire il comportamento degli operatori, questo meccanismo prende il nome di 
    Overloading degli Operatori, come: +, ==, [], etc., affinché possano essere adattati ai tipi di dati interessati (classi).
    
    -->   In pratica: puoi far sì che l’operatore + funzioni anche con oggetti tuoi, non solo con numeri.

    ⚠️ Regole:
        <+> Non puoi creare operatori nuovi (**, &&&, ecc.)
        <+> Uno dei due operandi deve essere una classe
        <+> Spesso serve usare friend per accedere ai dati privati

    ✍️ Puoi sovraccaricare questi operatori (ecco i più utili):

    (1) Operatori aritmetici (+ - * /):
        Li puoi ridefinire per sommare oggetti tra loro.

    (2) Operatori di confronto (== != < >): 
        Li puoi usare per confrontare oggetti.

    (3) Accesso tipo array ( [] ): 
        Ti serve quando vuoi accedere a un oggetto come se fosse un array.

    (4) Operatore funzione (functor) ( '()' ) 
        Ti permette di trattare un oggetto come una funzione chiamabile.

    (5) Stream di input/output ( << e >> ) 
        Per stampare un oggetto con cout o leggerlo con cin.

    (6) Gestione memoria personalizzata (new e delete): 
        Puoi ridefinire come viene allocato/deallocato un oggetto.


    🛑 Operatori che NON puoi sovraccaricare:

    -------------------------------------------------------------------------------------
    | Operatore	            |  Motivazione                                              |
    -------------------------------------------------------------------------------------
    | . (accesso ai membri) |  Il compilatore ha bisogno di sapere esattamente cosa c’è |
    | :: (scope resolution) |  Gestione del namespace, non sovrascrivibile              |
    | sizeof	            |  Valutato a compile-time                                  |
    | typeid                |  Fornisce tipo a runtime, non modificabile                |
    | ?: (ternario)	        |  È parte della sintassi del linguaggio                    |
    -------------------------------------------------------------------------------------

    📌 Quando ha senso utilizzare l'Overloading degli Operatori?
        Sovraccarica operatori solo se il significato è chiaro e migliora la leggibilità.
        Esempio: 
                ✔️ + per un Punto, Tempo, Data → Ha senso.
                ❌ + per una Persona → 🤨 strano.


    🔑 Parola chiave friend in C++
    La parola chiave friend serve per dichiarare una funzione o classe "amica" di un'altra classe. 
    Significa che la funzione friend può accedere ai membri privati o protetti della classe come se fosse un membro 
    della classe stessa, senza esserlo.
    Viene usata spesso per:
        <+>  operatori esterni come operator<< o operator+ (quando non si vogliono scrivere come metodi membri)
        <+>  funzioni helper esterne che hanno bisogno di accedere ai dettagli interni di una classe

    💥 Perché friend può stare dentro la classe?
    Anche se una friend è una funzione esterna (cioè non è membro della classe), può comunque essere definita 
    direttamente dentro il corpo della classe se vuoi.

    Questo è sintassi valida e C++ ti permette di:
        <1>  Dichiararla nella classe → friend ostream& operator<<(...)
        <2>  Definirla anche lì dentro → scrivi direttamente il corpo { ... } come nel tuo esempio
    
    È una scelta stilistica e di comodità, ma è utile quando:
    <+>  la funzione è corta
    <+>  strettamente legata alla classe
    <+>  vuoi tenerla tutta lì per chiarezza o per esercitazioni/compattezza

    🧠 Ricorda:
    Una funzione friend non è un membro della classe, ma può essere definita nel corpo della classe come eccezione.

    nella parte (5) si potrebbe anche fare:

                                class Auto {
                            private:
                                string targa;
                                string modello;
                            public:
                                Auto(string shield, string model) : targa(shield), modello(model) {}

                                friend ostream& operator<<(ostream&, const Auto&); // solo dichiarazione
                            };

                            // Definizione fuori
                            ostream& operator<<(ostream& outStream, const Auto& car) {
                                outStream << "Targa: " << car.targa << "\nModello auto: " << car.modello;
                                return outStream;
                            }
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// (1) 📌 Operatore +
class Punto
{
    private:
        int x,y;
    public:
        Punto(int a, int b) : x(a), y(b) {}

        Punto operator+(const Punto& p) const { return Punto(x +p.x, y + p.y ); }
        //(2)
        bool operator==(const Punto& p) const { return x == p.x && y == p.y; }
        
        void stampa() const { cout << "(" << x << "," << y << ")" << endl; }
};

//(2) 📌 Operatore ==
class Persona
{
    private:
        string nome;
        int eta;
    public:
        Persona(string n, int age) : nome(n), eta(age) {}

        bool operator==(const Persona& p) const { return nome == p.nome && eta == p.eta; } //se entrambi gli argomenti sono true allora ritorna true 

        void stampa() const { cout << "{nome: \"" << nome << "\", eta': " << eta << "} "; }
};

//(3) 📌 Operatore []
class Vet
{
    private:
        vector<int> v;
    public:
        Vet(int dim) : v(dim)
        {
            for(int i=0;i<dim;i++)
            {
                v[i] = i+1;
            }
            cout << "Vettore di dimensione " << dim << " creato." << endl;
        }
        //posso anche scrivere qualcosa volendo
        //int& operator[] (int i) { cout << "Valore cella di indice [" << i << "] = "; return v[i]; }
        int& operator[] (int i) { return v[i]; }
};

//(4) 📌 Operatore ()
class Moltiplicatore
{
    private: 
        int fattore;
    public:
        Moltiplicatore(int f) : fattore(f) {}
        int operator() (int value) { return value * fattore; } 
};

//(5) 📌 Operatore <<
class Auto
{
    private:
        string targa; 
        string modello;
    public:
        Auto(string shield, string model) : targa(shield), modello(model) {}
        friend ostream& operator<< (ostream& outStream, const Auto& car) 
        { 
            outStream << "Targa: " << car.targa << "\nModello auto: " << car.modello;
            return outStream; 
        }
};

//(6) 📌 new/delete personalizzati 
class ProvaMemoria
{
    public:
        void* operator new(size_t size) 
        {
            cout << "[Allocazione personalizzata!] Dimensione di " << size << " byte" << endl;
            return malloc(size);
        }

        void operator delete(void* ptr) 
        {
            cout << "[Deallocazione personalizzata!]" << endl;
            free(ptr);
        }
}

int main()
{
    //1
    cout << "1) -- Operatore + --\n" << endl; 
    Punto p1{2,3};
    Punto p2{2,3};
    Punto somma = p1 + p2; //possiamo fare la somma dei due con operatore + grazie alla nostra modifica!
    somma.stampa();


    //2 == 
    cout << "2) -- Operatore == --\n" << endl;

    Persona pers1{"Gianni", 22}, pers2{"Mauro",23}, pers3{"Gianni", 22};
    
    cout << "Vediamo se sono la stessa persona:" << endl;
    pers1.stampa();
    pers2.stampa();
    
    if(pers1==pers2)
        cout << "Sono la stessa persona." << endl;
    else cout << "Sono due persone diverse." << endl;

    cout << "Vediamo se invece loro due sono la stessa persona:" << endl;
    pers1.stampa();
    pers3.stampa();

    if(pers1==pers3)
        cout << "Sono la stessa persona." << endl;
    else cout << "Sono due persone diverse." << endl;

    //Vediamo con la classe punto di prima:
    cout << "\nVediamo con la classe punto di prima:\nConfronto se i due punti sono uguali:" << endl; p1.stampa(); p2.stampa(); cout << (p1==p2 ? "Sono uguali!" : "Sono diversi...") << endl;
    

    //3 []
    cout << "3) -- Operatore [] --\n" << endl;
    Vet v(3); //dimensione tra parentesi
    v[0] = 99;
    cout << "Valore cella v[0]: " << v[0] << endl;

    
    //4 ()
    cout << "4) -- Operatore () --\n" << endl;
    Moltiplicatore molt3(3);
    cout << "Moltiplicazione di 3 per input 4: " << molt3(4) << endl;

    //5 Operatore di stream << 
    cout << "5) -- Operatore di stream << --\n" << endl;
    Auto a1{"NR504EL","Porche"};
    
    //stampa con << 
    cout << a1 << endl; 
    return 0;
}