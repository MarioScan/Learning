/*

    -----------------------
    |       Classi        |
    ----------------------- 

(1) 📘 Cos'è una classe?
Una classe è un modello astratto che rappresenta un "tipo di dato complesso", costruito da te.
Può contenere:

<-> Dati: (variabili membro)

<-> Funzioni: (metodi) che agiscono su quei dati

Vediamo un esempio:
*/

#include <iostream>
using namespace std;

class Persona
{
    private: 
        string nome;
        int eta;

    public:

        //setters
        void setNome(string newName) { nome = newName; }
        void setEta(int newAge) { eta = newAge; } 
      
        //getters
        string getNome() { return nome; }
        int getEta() { return eta; }
};

int main()
{
    /*

        (2) 🧱 Costruzione di oggetti
    
    */
    //Adesso possiamo creare una persona con gli elementi della classe creata:
    Persona p1; //creazione della instanza --> istanzazione 
    p1.setNome("Mario");
    p1.setEta(21);

    cout << "Nome utente: " << p1.getNome() << "\nEta: " << p1.getEta() << endl;

    //Benissimo adesso proviamo da input:

    Persona p2;
    string inNome;
    int inEta;
    cout << "\n-----------------------\nInserisci nome utente: "; cin >> inNome; cout << "Inserisci eta: "; cin >> inEta; 
    p2.setNome(inNome); p2.setEta(inEta);
    cout << "Hai aggiunto il nuovo utente:\nNome: " << p2.getNome() << "\nEta: " << p2.getEta() << endl;
    
    return 0;
}

