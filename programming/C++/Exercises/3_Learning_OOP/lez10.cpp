/*
    -----------------
    |    VECTORS    |   --> Libreria <vector>
    -----------------

    🧠 COS’È UN VECTOR
    std::vector<T> è un array dinamico della STL (Standard Template Library), ed è un
    contenitore dinamico che si comporta come un array, ma cresce da solo e ha metodi molto utili.

    È come un array, ma:

    cresce e si riduce automaticamente;
    ti permette operazioni comode con metodi già pronti;
    è molto usato in concorsi, esami, codice reale;
    è template, quindi puoi usare qualsiasi tipo come T: primitivi, oggetti, puntatori, ecc.

    Vantaggi:
    <+> ha dimensione variabile
    <+> può contenere qualsiasi tipo (primitivi o oggetti)
    <+> ti offre sicurezza (con .at()), flessibilità, e integrazione con algoritmi STL

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

    (4) 📌 Iterazione con range-based for:
        La range-based for loop (cioè “for basato su intervallo”) è una forma moderna e semplificata di for
        introdotta in C++11, usata per scorrere tutti gli elementi di un contenitore, come vector, array, set, string, ecc.,
        senza bisogno di usare gli iteratori manualmente.
            🧠 È un modo per dire:
            "Per ogni elemento x dentro la collezione v, fai qualcosa"
        --> esempio:
                for (int n : numeri) 
                {
                    cout << n << endl;
                }
            

    (5) 📌 Iterazione con iteratori:
            for (vector<int>::iterator it = numeri.begin(); it != numeri.end(); ++it) 
            {
                cout << *it << endl;
            }
        🧠 Nota: begin() → puntatore al primo elemento, end() → dopo l’ultimo


    (6) 🧱 Vettori di oggetti:
            📌 Attenzione: gli oggetti sono copiati nel vector, 
            quindi se modifichi uno dopo averlo inserito... nel vector non cambia nulla.
                        
            Vantaggi:
            ✅ È semplice
            ✅ Tutti gli oggetti sono dello stesso tipo (Cane)
            ✅ La memoria è gestita in automatico (niente new o delete)

            Limiti:
            ❌ Non puoi metterci dentro oggetti di classi diverse ma con la stessa base
            ❌ Non hai polimorfismo (perché un vector<Animale> che contiene oggetti di Cane, Gatto... fa slicing!)
                                                                                                        ^^^^^^^^
        🧨 Cos'è il Slicing?
            Quando inserisci un oggetto derivato (Cane) in un vector<Animale>, viene troncata la parte derivata.
            Risultato? Chiami verso()... e ti risponde quello della classe base, non quello override. (Vedi esempio sotto)

    (7) 💥 Cos'è un oggetto polimorfo?
        Un oggetto polimorfo è un oggetto derivato da una classe base con almeno un metodo virtuale.
        In pratica è un oggetto che può "cambiare forma" a seconda del tipo effettivo che rappresenta,
        anche se lo trattiamo come un oggetto di tipo base.
        --> Vediamo meglio con del codice... (sotto)

    (8) ⚙️ Vettori di puntatori a oggetti polimorfi:
        Permette di risolvere il problema precedente (6) della mancanza di Polimorfismo.
        ⚠️ Importantissimo:
            *) Se il distruttore di Animale non fosse virtual, delete a non chiamerebbe correttamente il distruttore di Cane, 
            causando un memory leak.
        💣 Quindi: in classi base polimorfe, il distruttore deve essere sempre virtuale!

        Vantaggi:
            ✅ Supporta il polimorfismo
            ✅ Ogni oggetto mantiene il comportamento corretto (late binding)
            ✅ Puoi iterare e chiamare verso() su oggetti diversi
        ⚠️ Problema: memoria dinamica → devi fare delete
            --> es.
                    for (Animale* a : animali)
                    delete a;       

    (9) 
            -------------
            |    AUTO   |
            -------------

        🟢 Esiste una parola chiave del C++, introdotta seriamente in C++11, 
        che serve a far dedurre automaticamente al compilatore il tipo della variabile in base al contesto.
        📌 In breve:
        auto dice al compilatore:
        “👋 Hey, guarda cosa sto assegnando a questa variabile, e indovina il tipo da solo.”
                auto numero = 42;       // deduce: int
            auto nome = "Mario";    // deduce: const char*
            auto pi = 3.14;         // deduce: double

        💥 Con oggetti STL:
            --> esempio 
                vector<string> nomi = {"Mario", "Ella", "Zaenyah"};

                for (auto nome : nomi) {
                    cout << nome << endl;
                }
            ☝️ In questo caso auto nome diventa automaticamente string, perché sta scorrendo un vector<string>.

        PRO: 
            ✅ 1. Evita scrittura verbosa:

                            vector<int>::iterator it = numeri.begin();  // 💤
                            auto it = numeri.begin();                   // 🔥
            ✅ 2. Più sicuro nei template:
            Quando lavori con template generici, non sai esattamente che tipo avrai — auto ti salva la vita.
        
        CONTRO:
            ⚠️ Attenzione!
            auto non significa "variabile dinamica" come in Python o JavaScript.

            Il tipo è dedotto a tempo di compilazione, non è come var in JavaScript o Object in Java.
            Una volta assegnato, non puoi cambiarlo:


    -----------

    🔥 Da qui in poi…
        Useremo vector ovunque:
      <->  Per raccogliere input da file
      <->  Per salvare oggetti (vector<Studente>)
      <->  Per strutture dati avanzate (pile, liste simulate, alberi)
      <->  Per template (template<class T> vector<T>)

*/

#include <iostream>
#include <vector>
using namespace std;

//(6-7)
class Animale
{
    public:
        virtual void verso() const { cout << "Verso animale" << endl; }
        ~Animale() { cout << "Distruttore animale chiamato." << endl; }
};
class Cane : public Animale
{
    public:
        void verso() const override { cout << "Wof wof!" << endl; }
    // (7) Qui Cane è un oggetto polimorfo perché ha override su un metodo virtual della base Animale.
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
    //(1) Creazione di vectors
    vector<int> v1; //vettore vuoto 
    vector<int> v2(10); //10 elementi inizializzati tutti a 0
    vector<int> v3(5,6); //5 elementi tutti inizializzati a 6.
    
    vector<string> nomi = {"Mario","Luigi","Yoshi"}; 

    //(2-3) Utilizzo di alcune funzioni sui vectors:

    vector<int> numeri; //anch'esso vettore vuoto 
    numeri.push_back(10); //push_back(x) ---> Aggiunge x in fondo
    numeri.push_back(20);
    numeri.push_back(30);
        
    cout << "Numeri vettore: ";
    for(int i=0;i< numeri.size(); i++)
    {
        cout << numeri[i] << " "; // Output: 10 20 30
    }

    //(4) Iterazione con range-based for:
    cout << "\nAltro modo di stampare il contenuto del vettore:" << endl;
    for (int n : numeri) 
    {
        cout << n << " "; // Anch'esso da Output: 10 20 30
    }


    //(5) Iterazione con iteratori: (non lo useremo...)
    for (vector<int>::iterator it = numeri.begin(); it != numeri.end(); ++it) 
    {
        cout << *it << endl;
    } 


    //(6) Vettore di oggetti:
    vector<Cane> cani;
    cani.push_back(Cane());
    cani[0].verso(); //Output: "Wof wof!"

    //ma...
    vector<Animale> animali;
    animali.push_back(Cane());
    animali[0].verso(); //Output: "verso animale" --> Non c'è polimorifsmo 

    //mentre:
    Animale* arr[3];
    arr[0] = new Cane();
    arr[0]->verso(); //Output: "Wof wof!" --> C'è il polimorfismo 

    //Come risolviamo?

    //(7-8) Vediamo come: Vettori di puntatori a oggetti polimorfi:
    cout << "Vettori di puntatori a oggetti polimorfi:" << endl;
    vector<Animale*> animali2;
    animali2.push_back(new Cane());
    animali2.push_back(new Gatto());
    animali2.push_back(new Mucca());

    animali2[0]->verso();
    animali2[1]->verso();
    animali2[2]->verso();

    cout << "Adesso stampiamo nuovamente con ciclo range-based e cancelliamo memoria allocata." << endl;
    for (Animale* a : animali2)
    {
        a->verso();
        delete a; //utilizziamo scorrimento visto nel punto 4
    }
    /* Output ottenuto nel punto (7-8):
        Vettori di puntatori a oggetti polimorfi:
        Wof wof!
        Miao!
        Muuuuu!
        Adesso stampiamo nuovamente con ciclo range-based e cancelliamo memoria allocata.
        Wof wof!
        Distruttore animale chiamato.
        Miao!
        Distruttore animale chiamato.
        Muuuuu!
        Distruttore animale chiamato.
    */

    //(9) Parola chiave "auto": 
    cout << "\nUso della parola chiave \"auto\" (n.b: extra non per esame): " << endl;
    auto numero = 10;
    auto stringa = "Ciao mondo";
    auto pi = 3.14;
    
    cout << "Stampa numero:" << numero << "Stringa:" << stringa << "Pi greco: " << pi;

    cout << "Fine del programma.\n\n";

    return 0;
}

/*  Perché usare i vectors è preferibile rispetto agli array statici:

---------------------------------------------------------------------------------------------------------
| 📌 Motivo	                      | 🔧Array (int arr[10])	         |  💡 std::vector<int>            |  
---------------------------------------------------------------------------------------------------------
| ✅ Dimensione dinamica	         |  ❌ No	                       |  ✅ Sì (puoi fare push_back)    | 
| ✅ Metodi utili (size(), ecc.)	 |  ❌ Nessuno	                   |  ✅ Tantissimi                  |
| ✅ Più sicuro	                 |  ❌ No bound check	           |  ✅ .at(i) dà errore se i fuori |
| ✅ Compatibile con STL	         |  ❌ No	                       |  ✅ Sì                          |
| ✅ Più leggibile e moderno	     |  ❌ Vecchio stile	               |  ✅ Best practice               |
| ✅ Facile da passare a funzioni |	❌ Serve passare anche la size  |  ✅ .size() incluso             |
---------------------------------------------------------------------------------------------------------
*/