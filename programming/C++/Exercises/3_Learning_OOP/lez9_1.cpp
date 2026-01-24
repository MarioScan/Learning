/*

        -----------------------------
        |   Ereditarietà multipla   |
        -----------------------------

        Una classe può ereditare attributi e comportamento di
        più di una classe base.
        Vediamo un esempio:
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Persona
{
    private:
        string nome;
        string codice_fiscale;
        int eta;
    public:
        Persona(string name, string cf, int age) : nome(name), codice_fiscale(cf), eta(age) {} //costruttore
        Persona(const Persona& p) : nome(p.nome), codice_fiscale(p.codice_fiscale), eta(p.eta) {} //costruttore di copia
        Persona() : nome("Nome sconosciuto"), codice_fiscale("CF sconosciuto"), eta(-1) {} //costruttore di default
        virtual ~Persona() { cout << "Chiamato distruttore di Persona." << endl; } //distruttore

        //getters e setters
        const string& getNome() const { return nome; }
        const string& getCodice_fiscale() const { return codice_fiscale; }
        const int& getEta() const { return eta; } 

        void setNome(const string& newNome) { nome = newNome; } 
        void setCodice_fiscale(const string& newCF) { codice_fiscale = newCF; } 
        void setEta(const int& newEta) { eta = newEta; } 
};

class Lavoratore : public Persona
{
    private:
        int stipendio;
        string matricola;
    public:
        Lavoratore(string name, string cf, int age, int salary, string personalCode) : Persona(name,cf,age), stipendio(salary), matricola(personalCode) {} //costruttore 
        Lavoratore(const Lavoratore& worker) : Persona(worker.getNome(), worker.getCodice_fiscale(), worker.getEta() ), stipendio(worker.stipendio), matricola(worker.matricola) {} //costruttore di copia
        Lavoratore() : Persona("Nome sconosciuto","CF sconosciuto",-1), stipendio(-1), matricola("Matricola sconosciuta") {} //costruttore di default
        ~Lavoratore() override { cout << "Chiamato distruttore di Lavoratore." << endl; } //distruttore --> non necessario in quanto non sto allocando memoria dinamica ma utile a scopo di studio

        const int& getStipendio() const { return stipendio; }
        const string& getMatricola() const { return matricola; } 
        
        void setStipendio(const int& newSalary) { stipendio = newSalary; }
        void setMatricola(const string& newMatricola) { matricola = newMatricola; }

};

class Professore : public Lavoratore
{
    private: 
        vector<string> materie;
        int esamiDaCorreggere; 
    public:
        Professore(string name, string cf, int age, int salary, string personalCode,string subjects, int exams) 
         /*Persona(name,cf,age), No--> va messo tutto in lavoratore*/ 
        : Lavoratore(name,cf,age,salary,personalCode), esamiDaCorreggere(exams) 
        {
            //lavoro per inserire stringa materie in un vettore di stringhe:
            string temp = "";
            for(int i=0; i< subjects.size() ; i++)
            {
                char c = subjects[i];
                
                if(c == ',')
                {
                    while(!temp.empty() && temp.back() == ' ') temp.pop_back(); //se ho uno spazio alla fine della stringa usa pop (cancella ultima cella)
                    while(!temp.empty() && temp.front() == ' ') temp.erase(0,1); //non esiste pop_front quindi faccio erase partendo da cella zero e cancello solo una cella (come se avessi una "pop_front()")

                    if(!temp.empty())
                    {
                        materie.push_back(temp);
                        temp.clear();
                    }
                }
                else temp+=c;
            }
            //gestisco ultima materia 
            while(!temp.empty() && temp.back() == ' ') temp.pop_back();
            while(!temp.empty() && temp.front() == ' ') temp.erase(0,1);
            
            if(!temp.empty())
            {
                materie.push_back(temp);
                temp.clear();
            }
        }
        Professore() : Lavoratore("Nome Sconosciuto","CF sconosciuto",-1,-1,"Matricola sconosciuta"), materie(), esamiDaCorreggere(0) {}
        ~Professore() override { cout << "Chiamato distruttore di Professore." << endl; }

        const vector<string>& getMaterie() const { return materie; } 
        const int& getEsamiDaCorreggere() const { return esamiDaCorreggere; } 

        void setMaterie(const vector<string>& newMaterie) { materie = newMaterie; }
        void setEsamiDaCorreggere(const int& newEsamiDaCorreggere) { esamiDaCorreggere = newEsamiDaCorreggere; }


        friend ostream& operator<<(ostream& out, const Professore& p) 
        {
            out << "Professore: " << p.getNome() 
            << "\nCF: " << p.getCodice_fiscale() 
            << "\nAnni: " << p.getEta() 
            << "\nStipendio: " << p.getStipendio() 
            << "\nMatricola: " << p.getMatricola() 
            << "\nMaterie:" << endl;
            for(int i=0;i<p.materie.size();i++)
                out << p.materie.at(i) << endl;
            out << "\nEsami da correggere: " << p.esamiDaCorreggere << endl; 
            return out;  
        }
};

int main()
{
    Persona p1("Mario", "MRSNC98", 25);
    Lavoratore l1("Luca","DWER948NDUR", 33,5000,"0001");
    Professore prof1("Gianni","NFKND4N4I50",44,7000,"0002","Programmazione 1, Algebra Lineare, Fisica",45);
    //Stampa professore
    cout << prof1 << endl;

    //prova set / get classe Professore
    prof1.setEsamiDaCorreggere(30); 
    cout << "Il professore ha corretto 15 esami, adesso ne rimangono: " << prof1.getEsamiDaCorreggere() << endl;

    //prova set / get classe Lavoratore con oggetto Professore
    prof1.setStipendio(prof1.getStipendio() + 1000);
    cout << "\nIl professore ha avuto un aumento dello stipendio di 1000 euro: " << prof1.getStipendio() << endl;
    
    //prova set / get classe Persona con oggetto Professore
    prof1.setEta(prof1.getEta() + 1);
    cout << "\nIl professore ha fatto il compleanno! Adesso ha " << prof1.getEta() << " anni. Congratulazioni!" << endl;
    
    cout << "\n Vediamo grafico completo della situazione:" << endl;
    cout << prof1 << endl;

    return 0;
}