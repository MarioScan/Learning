
/*
    ---------------------------------------------------
    |     Tutte le creazioni di oggetti nel main.     |
    ---------------------------------------------------
*/

#include <iostream>
#include <vector>
using namespace std;

class Animale
{
    public:
        virtual void verso() const { cout << "Verso animale" << endl; }
        ~Animale() { cout << "Distruttore animale chiamato." << endl; }
};
class Cane : public Animale
{
    private:
        string nome;
    public:
        Cane() {} //Costruttore default
        Cane(string name) : nome(name) {} //Costruttore con parametri
        Cane(const Cane& obj) //Costruttore di Copia
        { 
            nome = obj.nome; 
        } 

        const string& getNome() const { return nome; } //BEST GETTER
        void setNome(const string& newNome) { nome = newNome; } //BEST SETTER

        void verso() const override { cout << "Wof wof!" << endl; }
    // Cane è un oggetto polimorfo perché ha override su un metodo virtual della base Animale.
};
class Gatto : public Animale{
    public:
        void verso() const override { cout << "Miao!" << endl; } 
};
class Mucca : public Animale{   
    public:
        void verso() const override { cout << "Muuuuu!" << endl; }
};

int main()
{
    //1 -> Creazione statica di un oggetto (creazione su STACK)
    Cane mioCane1; //usa costruttore di default;
    Cane mioCane2("Fufi"); //uso costruttore con parametri
    cout << "Ho un cane e si chiama: " << mioCane2.getNome() << endl;

    string in;
    cout << "Stai adottando un cagnolino, come lo chiami: "; cin >> in;
    mioCane1.setNome(in);
    cout << "Il tuo cane si chiama: " << mioCane1.getNome() << endl;
    
    //2 -> Creazione dinamica di un oggetto (creazione su HEAP)
    Cane* miocane3 = new Cane();
    Cane* miocane4 = new Cane("Fiffi");
    //importante fare delete per evitare memory leak!
    delete miocane3;
    delete miocane4;
    
    //3 -> Creazione con lista di inizializzazione (list-initialization) (C++11+) --> 
    Cane miocane5{"Mimmo"};
    //Questo metodo qui sotto utilizza una copy-list-initialization, cioé crea oggetto temporaneo con quei parametri 
    //e lo assegna alla variabile, tuttavia il compilatore spesso ottimizza il tutto, il che lo rende praticamente identico
    Cane miocane10 = {"Giano"};


    //4 --> Copia o assegnazione
    Cane mioCane6{};
    Cane miocane6 = mioCane1; //tramite costruttore di copia 
    miocane6 = mioCane1; //tramite assegnamento
    Cane copiaDiCane = miocane6; //anche questo tramite costruttore di copia 

    //5 --> Creazione di array(statica o dinamica)
        //Array statico
        Cane mieiCani[3]; //crea 3 oggetti con costruttore di default.
        mieiCani[0].setNome("Ninuzzu");
    
        //array dinamico (poco usato, meglio vector)
        Cane* mieiCagnolini = new Cane[3]; //crea 3 oggetti con costruttore di default.

        //anche qui --> puntatori? allora serve delete
        delete[] mieiCagnolini;

    
    //6 --> Creazione di vectors di oggetti o puntatori a oggetti:
    vector<Cane> v; //vettore di oggetti
    vector<Cane*> vPtr; //vettore di puntatori a oggetti
        //Inizializzazione oggetti:
        v.push_back(Cane("Gino")); //aggiunge oggetto al vettore di oggetti
        vPtr.push_back(new Cane("Ciccio")); //aggiunge puntatore a oggetto dinamico 
    //liberare memoria!
    for(Cane* p : vPtr)
        delete p;
    v.clear();

    //7 --> Creazione usando la parola chiave (C++11+) "auto" (non lo useremo a scopi didattici)
    auto obj = Cane("Nino"); //il tipo viene dedotto automaticamente, nel nostro caso: <classe Cane>


    int n = 4;
    vector<Animale*> animali;
    //inizializzazione vettore animali:
    for(int i=0;i<n; i++) 
    {
        if(i==0)
            animali.push_back(new Cane());
        else if(i==n-1)
            animali.push_back(new Mucca());
        else animali.push_back(new Gatto());
    }

    //stampa verso usando un range-based for:
    cout << "Stampa verso animali:" << endl;
    for(Animale* a : animali)
    {
        a->verso();
    }

    //come so che animale è ognuno di loro: ovvero come so a che classe appartengono ogni animali i-esimo? 
    for(Animale* a : animali)
    {
        if(Cane* thisIsADog = dynamic_cast<Cane*>(a))
        {
            cout << "Io sono un cane!" << endl;
        }
        else if(Gatto* thisIsACat = dynamic_cast<Gatto*>(a))
        {
            cout << "Io sono un gatto!" << endl;
        }
        else if(Mucca* thisIsACow = dynamic_cast<Mucca*>(a))
        {
            cout << "Io sono una mucca! ";
            a->verso();
            cout << endl;
        }
    }



    return 0;
}