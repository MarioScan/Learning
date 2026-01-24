/*

        --------------------------
        |      Ereditarietà      |
        --------------------------

(1) 🧬 Cos’è l’Ereditarietà?
È il meccanismo che consente a una classe di acquisire (ereditare) attributi e metodi da un’altra classe.

🔥 Tre tipi di ereditarietà
Tipo	Accesso ai membri public e protected della base
public	Rimangono public/protected nella derivata
protected	Tutti diventano protected
private	Tutti diventano private

👉 Nella vita reale: usa sempre public, a meno che tu non stia scrivendo una libreria blindata.
*/

#include <iostream>
using namespace std;

class Base {
public:
    void saluta() { cout << "Ciao da Base!" << endl; }
};

class Derivata : public Base {
public:
    void extra() { cout << "Funzione in Derivata!" << endl; }
};

/*

    -------------------------------------------------
    |                                               |
    |   Costruttori e Distruttori in Ereditarietà   |
    |                                               |
    -------------------------------------------------

(2) ⚙️ Ordine di esecuzione:
    Quando viene creata una instanza della classe "Figlia" viene utilizzato un costruttore della classe "Genitore" 
    e poi quella della classe "Figlia" che stiamo andando a creare. 
    Quindi:    
        1. Prima il costruttore della base;
        2. Poi quello della derivata;
        3. Alla distruzione: prima la derivata, poi la base.

*/

class Persona {
public:
    Persona() { cout << "Costruttore Persona" << endl; }
    ~Persona() { cout << "Distruttore Persona" << endl; }
};

class Studente : public Persona {
public:
    Studente() { cout << "Costruttore Studente" << endl; }
    ~Studente() { cout << "Distruttore Studente" << endl; }
};

/*
    ---------------------------------------
    |                                     |
    |   Binding Dinamico & Polimorfismo   |
    |                                     |
    ---------------------------------------

(3) ❓ Che succede se usi un puntatore alla classe base?
    --> Utilizziamo il comando override per modificare una funzione preesistente nella classe Genitore, 
        per personalizzarla alla sotto classe Figlia. 

    👉 Senza virtual (📦 STATIC BINDING 📦), chiamerebbe sempre il metodo della base: early binding (collegamento anticipato):
        --> L'early binding non permette il polimorfismo tra classi padre e figlio, 
        perché il collegamento ai metodi viene fatto a tempo di compilazione e non tiene conto del tipo dinamico dell'oggetto. 
        (❌)

    👉 Con virtual (🔁 DYNAMIC BINDING 🔁), usa quello della classe effettiva: late binding (collegamento ritardato, 
        cioè funzioni virtuali) --> permette invece il polimorfismo 
        (✅)


    ⚠️ Occhio a...
    <-> virtual → Attiva il dynamic binding

    <-> new/delete → Implicano allocazione dinamica

    <-> Funzioni non virtuali sono sempre static bound (early binding)

    🧪 Comando "FINAL":
        Permette di impedire ulteriori OVERRIDE: (*)

*/

class Animale {
public:
    virtual void parla() const { cout << "Verso generico" << endl; }
    // (*Esempio di Final --> per impedire override)
    virtual void finalMethod() const final { cout << "Metodo finale non modificabile." << endl; }

};

class Cane : public Animale {
public:
    void parla() const override { cout << "Bau!" << endl; }
    //cercare di ⚠️ modificare la funzione finalMethod() darebbe ERRORE DI COMPILAZIONE ⚠️
    //                  ^^^                     ^^^                     ^^^^^^
};

/*

    ---------------------------------------
    |                                     |
    |    Composizione vs Ereditarietà     |
    |                                     |
    ---------------------------------------

(4) 👨‍👩‍👦 Composizione:

La composizione si verifica quando una classe contiene un oggetto di un'altra classe come attributo.

Avviene quando "Una classe contiene un’altra classe."

È una relazione "ha un" (has-a).

    --> esempio: Auto ha un Motore.

Qui, l’oggetto m (di tipo Motore) è un membro della classe Auto. 
Significa che ogni volta che crei un oggetto Auto, viene automaticamente creato anche il suo Motore.

🔧 Vantaggi della composizione: 
    ✅ Più flessibile (puoi cambiare comportamento "iniettando" oggetti diversi).
    ✅ Meno dipendenza tra le classi.
    ✅ Facilita il principio di singola responsabilità (SRP).
    ✅ Permette incapsulamento più pulito.

*/

class Motore {
public:
    void accendi() { cout << "Motore acceso!" << endl; }
};

class Auto {
    Motore m;
public:
    void avvia() { m.accendi(); }
};

/*
    ---------------------------------------
    |                                     |
    |    Composizione vs Ereditarietà     |
    |                                     |
    ---------------------------------------

(4.1) 🧠 Quando usare cosa? 
Usa ereditarietà quando c'è una vera relazione gerarchica tra classi.

Usa composizione quando vuoi riutilizzare funzionalità senza creare una relazione gerarchica.

👉 Quando “è un” → ereditarietà   --> (es. Studente è una Persona)
👉 Quando “ha un” → composizione  --> (es. Auto ha un Motore)

*/

/*

    ---------------------------------------
    |                                     |
    |      Cast da Genitore a Figlio      |
    |                                     |
    ---------------------------------------

(5) ❓ Quando farlo e perché è pericoloso? 
    Quando hai un puntatore o riferimento a una classe base (Base*) che in realtà punta a un oggetto di una classe derivata (Derived), 
    a volte vuoi accedere a funzioni o membri specifici della classe derivata.

    🧠 Ma il problema è:
    <-> Non puoi fare questo direttamente senza cast ⚠️:
    perché il compilatore considera solo la base (cioè non conosce la struttura specifica della derivata).

    <-> ⚠️ Devi però fare il cast solo se sei certo che l’oggetto puntato sia effettivamente di tipo derivato!
        --> Altrimenti stai aprendo la porta a bug o crash. 

    -----------------
    |  static_cast  | 
    -----------------
    
    static_cast è un cast a compile time, quindi non controlla a runtime se il cast è effettivamente valido.
    Se basePtr NON punta a un oggetto Derived, questo cast è pericoloso: potresti chiamare metodi inesistenti, 
    causare comportamenti indefiniti e crash.
    Usalo solo se sei certo al 100% del tipo reale dell'oggetto.

    -------------------
    |   dynamic_cast  |
    -------------------
    
    dynamic_cast fa un controllo a runtime usando il sistema RTTI (Run-Time Type Information).
    Se il cast è valido (cioè l’oggetto puntato è effettivamente della classe derivata o sua sottoclasse), 
    restituisce il puntatore convertito.
    Se non è valido, restituisce nullptr (per puntatori) o lancia un'eccezione (per riferimenti).
    Quindi è il modo sicuro per fare downcast da base a derivata.


    -------------------
    |     delete      | (e distruttore virtuale)
    -------------------

    Quando fai delete su un puntatore a base che punta a un oggetto derivato, se il distruttore della base NON è virtuale:
        <-> Viene chiamato solo il distruttore della base (non quello della derivata).

        <-> Questo può causare memory leak perché le risorse allocate nella derivata non vengono liberate.

    Se invece il distruttore della base è virtuale, allora la chiamata a delete ptr esegue:
        1. Distruttore della derivata (pulizia risorse specifiche)
        2. Distruttore della base

    È obbligatorio definire distruttori virtuali nelle classi base se prevedi di usare il polimorfismo
    e la cancellazione tramite puntatori a base.



    👉 Tipi di Ereditarietà:

    ------------------------------------------------------------------------------------------
    |  Tipi di Ereditarietà       |    Accesso a membro             |    Accesso a membro    |
    |                             |    classe base                  |    classe derivata     |
    ------------------------------------------------------------------------------------------
    |                             |    Public                       |    Public              |
    |   Public                    |    Protected                    |    Protected           |
    |                             |    Private                      |    Inaccessibile       |
    ------------------------------------------------------------------------------------------
    |                             |    Public                       |    Protected           |
    |   Protected                 |    Protected                    |    Protected           |
    |                             |    Private                      |    Inaccessibile       |
    ------------------------------------------------------------------------------------------
    |                             |    Public                       |    Private             |
    |   Private                   |    Protected                    |    Private             |
    |                             |    Private                      |    Inaccessibile       |
    ------------------------------------------------------------------------------------------


    👉 public è il tipo di ereditarietà più utilizzato;
    
    👉 private è  il tipo di ereditarietà per default:
            L'ereditarietà di tipo private occulta la classe base all'utente perché sia possibile
            cambiare l'implementazione della classe base o eliminarla del tutto senza richiedere
            alcuna modifica all’utente dell'interfaccia. 

        🧠: quindi se si dimentica di specificare il tipo di ereditarietà, gli
            elementi pubblici della classe base saranno privati in quella derivata
            l'ereditarietà privata è quella di default; essa occulta la classe base 
        
    👉protected mantiene accessibili i membri pubblici e protetti nella 
        classe derivata occultandoli all’esterno.


*/
class Genitore
{
    public:
        virtual ~Genitore() {}
};

class Figlio : public Genitore //eredità 
{
    public:
        void funzioneSpecifica() 
        {
            cout << "Questa e' una funzione specifica della classe Figlio!" << endl;
        }
};

int main()
{
    //1
    cout << "Esempio 1" << endl;
    Base b;
    b.saluta();
    
    Derivata d;
    d.saluta();
    d.extra();


    //2
    cout << "\nEsempio 2" << endl;
    Persona p;
    Studente stud; //alla sua creazione viene usato un costruttore di persona e poi di studente ! 
    //la distruzione viene effettuata dal compilatore a fine esecuzione del programma!
    
    
    //3 
    cout << "\nEsempio 3" << endl;
    Animale* ptr = new Cane();
    ptr->parla();  // 🔥 Output: "Bau!", non "Verso generico"
    delete ptr;

    //4 
    cout << "\nEsempio 4" << endl;
    Auto a;
    a.avvia();

    //5 --> è meglio non usarlo 
    Genitore* genitorePtr = new Figlio();
    Figlio* figlioPtr = dynamic_cast<Figlio*>(genitorePtr); //si può usare static_cast, ma dynamic permette una sicurezza migliore.
    if(figlioPtr)
    {
        figlioPtr->funzioneSpecifica();
    }
    else
    {
        cout << "Cast fallito: genitorePtr non è un Figlio!" << endl;
    }

    delete genitorePtr;
    //delete figlioPtr; //il distruttore del genitore si occupa della cancellazione, provare a fare la delete del puntatore figlio da Segmentation Fault!

    cout << "\n\nVedi distruttori della classe Persona e figli:" << endl;
    return 0;
}