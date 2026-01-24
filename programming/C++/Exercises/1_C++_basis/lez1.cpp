/*
C++ Basic Types
int ---> 2 - 4 bytes
float ---> 4 bytes
double ---> 8 bytes
char ---> 1 byte
wchar_t ---> 2 bytes
bool ---> 1 byte
void ---> unspecified
pointers ---> 4 - 8 bytes

C++ Non-Basic Types
class --> di per se') non occupa memoria ma i oggetti al suo interno si, questi piu' il PADDING
padding --> (generalmente 4-8 bytes), esistono modi per ridurre il padding, per esempio 2 di padding invece che 3 o 4...
object --> dipende dal tipo (int, char, float, o un'altra classe ancora...)
string --> 32 bytes: ((8 char*) + (8 size) + (16 buffer))

C++ Type Modifiers
Per int, double , char
- signed --> valori sia positivi che negativi
- unsigned --> solo valori positivi
- short (per int) --> versione corta di int (solitamente 2 byte)
- long (per int e double) --> versione lunga di int (solitamente 8 byte)
- long long (per int) --> versione ancora più lunga, esplicitamente 8 byte (64 bit)
<-> Modificatori costanti/volatili
- const (o const cv-qualified)--> valore costante, cioe' non modificabile
- volatile (o volatile cv-qualified) --> la variabile puo' cambiare "da sola" (es. da hardware)
- mutable --> permette la modifica in una const class (vale solo per membri di classi) (RARAMENTE USATO)
- unqualified (o non cv-qualified) --> tipi senza modificatori di tipo constanti o volatili

int x = 3; --> non cv-qualified
const char y = 'a'; --> const cv-qualified, o genericamente solo cv-qualified


C++ Type Casting 
- Implict --> Il compilatore converte automaticamente un tipo in un altro se è sicuro farlo 
    es. 
        int i = 42; 
        float f = i;  // Implicit cast: int → float

<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->

- Explcit  --> Forzi una conversione usando (tipo) davanti al valore. 
    es. 
        double d = 3.14; 
        int i = (int)d; // taglia la parte decimale → i = 3

<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->

- static_cast ( static_cast<T>() ) --> CAST SICURO e STATICO: 
    Serve per:
        (1) Conversioni tra tipi compatibili, 
        (2) Downcast tra classi con ereditarietà nota , 
        (3) Conversioni di tipo base → derivato (se sei sicuro!)
    
        es. 
            float f = 3.14;
            int i = static_cast<int>(f);  // Sicuro, taglia la parte decimale
      
<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->
        
- const_cast ( const_cast<T>() ) --> RIMUOVE const o volatile: 
    Serve per :
    Rimuovere la qualifica const o volatile da un puntatore o riferimento.
    es.
        void print(int* x) { *x = 10; }
        void wrapper(const int* p) {
            print(const_cast<int*>(p));  // rimuove const
        }

<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->

- dynamic_cast ( dynamic_cast<T>() ) --> CAST DINAMICO CON RTTI
    Serve per: 
        (1) Downcasting sicuro a runtime;
        (2) Funziona solo con puntatori/riferimenti a classi polimorfiche (cioè con almeno un virtual).

        es. 
            class Base { public: virtual ~Base() {} };
            class Derived : public Base {};
            class Other {};

            Base* b = new Derived;
            Derived* d = dynamic_cast<Derived*>(b);  // OK: ritorna puntatore valido

<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->

- reinterpret_cast ( reinterpret_cast<T>() ) --> TRADUZIONE BIT A BIT
    Serve per:
        (1) Cast brutale tra tipi totalmente diversi;
        (2) Usato per low-level o system programming
        
        es.
            int a = 65;
            char* p = reinterpret_cast<char*>(&a);
            std::cout << *p << std::endl;  // Stampa 'A' (ASCII 65)
    
        ⚠️ Altamente pericoloso. Non converte, reinterpreta i bit. Se usato male, causa crash o dati corrotti.

<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->

*/
#include <iostream>
using namespace std;

//PROTOTIPI DI FUNZIONE
void stampaArray(const char (&)[], const int &);

template <size_t R, size_t C> 
void DimMatrix(const int (&)[R][C], int&, int&);

//DEFINIZIONE DI FUNZIONE
void stampaArray(const char (&arr)[], const int &dim)
{
    for(int i=0;i< dim;i++)
    {
        cout << arr[i] << " ";
    }
}

template <size_t R, size_t C> 
void DimMatrix(const int (&arr)[R][C], int& rows, int& cols)
{
    rows = R;
    cols = C;
}

int main()
{
    //Array in C++ 

    int arr1[5] = {1,2,3,4,5};
    int arr2[] = {6,7,8,9,10};
    char arr3[] = {'+','-','*','/'};
    char arr4[20] = {"Ciao mondo"};

    cout << "Array 1: " << endl;

    for(int i=0;i<5;i++)
    {
        cout << arr1[i] << " " ;
    }

    //dimensione di un array:
    size_t dim = sizeof(arr2) / sizeof(arr2[0]);
    cout << "\nArray 2: " << endl;

    for(int i=0;i<dim;i++)
    {
        cout << arr2[i] << " ";
    }

    cout << "\nArray 3: " << endl;
    
    dim = sizeof(arr3) / sizeof(arr3[0]);
    stampaArray(arr3,dim);

    cout << "\nArray 4: " << endl;

    cout << arr4 << endl;

    //calcola dimensione matrice interi 
    
    int righe = 0, colonne = 0; //NOTA: Variabili normali non vanno bene per dimensioni di array passati a template così. (Devono essere necessariamente di tipo const o constexpr)
     
    int arr5[3][3] = 
    {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    DimMatrix(arr5, righe, colonne);
    cout << "Ho dimenticato dimensione righe e colonne di questa matrice, uso funzione:\nRighe: " << righe << "\nColonne: " << colonne << endl; 

    /* ------------------------------------  
    OUTPUT DATO: 

    Array 1: 
    1 2 3 4 5 
    Array 2: 
    6 7 8 9 10 
    Array 3: 
    + - * / 
    Array 4: 
    Ciao mondo
    Ho dimenticato dimensione righe e colonne di questa matrice, uso funzione:
    Righe: 3
    Colonne: 3
    
    ------------------------------------ */
    return 0;
}