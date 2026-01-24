/*

    Esercizio sulle classi ed ereditarietà:


📌 Obiettivo:
Crea una gerarchia di classi per rappresentare animali.
Classe base: Animale
   - attributo nome
   - metodo virtuale verso()

Classi derivate: Cane, Gatto, Mucca
   -> ognuna override verso() con un suono specifico

Nel main():

1. Crea un vettore di puntatori a Animale
2. Inserisci 1 oggetto per tipo
3. Itera e chiama verso() per ogni oggetto

-----------
Output atteso:
Bau!
Miao!
Muuu!
-----------
*/

#include <iostream>
using namespace std;

class Animali
{
    private:
        string nome;
    public:
        Animali(string name) : nome(name) {}
        Animali() : nome("Sconosciuto") {}
        virtual ~Animali() {}

        void setName(const string& name) { nome = name; }
        string getName() { return nome; }

        virtual void verso() const = 0; //buona norma per un metodo virtuale puro che deve essere modificato
};

class Cane : public Animali
{
    private:
        string razza;
    public:
        Cane(string name, string race) : Animali(name), razza(race) {}
        Cane() : Animali("Sconosciuto"), razza("Sconosciuta") {}

        void setRazza(const string& race) { razza = race; }
        string getRazza() { return razza; }

        void verso() const override {
            cout << "Wof wof!" << endl;
        }
};

class Gatto : public Animali
{
    private:
        int eta;
    public:
        Gatto(string name,int age) : Animali(name), eta(age) {}
        Gatto() : Animali("Sconosciuto"), eta(-1) {}

        void setEta(const int& age) { eta = age; }
        int getEta() { return eta; }

        void verso() const override {
            cout << "Mao! " << endl;
        }
};

class Mucca : public Animali{
    private:
        string colore;
    public:
        Mucca(string name, string color) : Animali(name), colore(color) {} 
        Mucca() : Animali("Unknown"), colore("Unknown") {}

        void setColore(const string& color) { colore = color; }
        string getColore() { return colore; }

        void verso() const override {
            cout << "Muuuu!" << endl;
        }
};


int main()
{
    //1 e 2 
    Animali* animale[3]; 
    animale[0] = new Cane("Pluto","Pastore tedesco");
    animale[1] = new Gatto("Garfield",5);
    animale[2] = new Mucca("Carlotta","Bianca e nera");

    //3 
    for(int i=0;i<3;i++)
    {
        cout << "Nome: " << animale[i]->getName() << endl;
        if(Cane* c = dynamic_cast<Cane*>(animale[i]))
        {
            cout << "Razza: " << c->getRazza() << endl;
        }
        else if(Gatto* g = dynamic_cast<Gatto*>(animale[i]))
        {
            cout << "Eta': " << g->getEta() << endl;
        }
        else if(Mucca* m = dynamic_cast<Mucca*>(animale[i]))
        {
            cout << "Colore: " << m->getColore() << endl;
        }
        cout << "Verso: "; animale[i]->verso(); cout << endl;
    }

}
