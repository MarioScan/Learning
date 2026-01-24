/*
Esercizio: Prodotti e Venditori

Si vuole realizzare un programma in C++ per la gestione di prodotti e venditori.

Classe Prodotto:
-   La classe deve rappresentare un generico prodotto e deve contenere:
-    un intero codice (identificativo del prodotto),
-    un double prezzo (in euro).

Metodi richiesti:
-    costruttore di default (imposta i dati a zero),
-    costruttore con parametri (codice, prezzo),
-    metodi get e set per codice e prezzo,
-    overloading dell’operatore << per stampare le informazioni del prodotto,
-    un metodo void leggi() per leggere i dati da input.

--- Sottoclassi di Prodotto: ---

1)  ProdottoAlimentare
        Attributo aggiuntivo: data di scadenza.
        Metodo bool verifica() → restituisce true se il prodotto non è scaduto, false altrimenti.

2)  ProdottoPerBambini
        Attributo aggiuntivo: fascia d’età (valori possibili: 0-3, 3-6, 6-9, 9-12).

------------------------------------
Classe Venditore
-    La classe deve contenere:
-    un intero codiceVenditore,
-    un array dinamico di Prodotto (l’elenco dei prodotti venduti),
-    un intero numProdotti (numero effettivo di prodotti).

Metodi richiesti:
-    costruttore di default (dati inizializzati a zero),
-    costruttore con parametro (solo il codice del venditore),
-    (opzionale) costruttore di copia,
-    overloading dell’operatore << per stampare codice venditore ed elenco prodotti,
-    double calcolaPrezzoTotale() → somma dei prezzi di tutti i prodotti,
-    double calcolaValoreMagazzino() → somma dei prezzi dei prodotti non scaduti,
-    void aggiungiProdotto(const Prodotto&) → aggiunge un prodotto all’elenco (se c’è spazio),
-    void leggi() per leggere i dati del venditore da input.

⚠️ Nota: la classe Venditore utilizza la composizione, 
quindi all’interno dei suoi metodi deve sfruttare i metodi già definiti nella classe Prodotto.

Programma principale (main)
-    Creare almeno 3 venditori, ciascuno con almeno 5 prodotti.
-    Implementare un menu che permetta all’utente di:
-    stampare l’elenco dei venditori,
-    visualizzare i prezzi totali,
-    ordinare i venditori per prezzo totale (crescente o decrescente).

Suggerimenti:
-    La scadenza dei prodotti può essere gestita in modo semplice (anche come stringa o data fittizia).
-    È possibile organizzare venditori e prodotti in file di testo da leggere con il metodo leggi().
-    Per garantire codici univoci (sia per venditori che prodotti) è consigliato l’uso di variabili statiche.
*/

#include <iostream>
#include "Prodotto.h"
#include "Venditore.h"
using namespace std;

int main() {
    // array di 3 venditori (costruttore di default chiamato per ciascuno)
    Venditore venditori[3];

    // --- Popolo venditore 0 (5 prodotti) ---
    venditori[0].aggiungiProdotto(new Prodotto(10.0));
    venditori[0].aggiungiProdotto(new ProdottoAlimentare(2.5, 20251231)); // non scaduto
    venditori[0].aggiungiProdotto(new ProdottoPerBambini(12.99, FasciaEta::TRE_SEI));
    venditori[0].aggiungiProdotto(new Prodotto(5.50));
    venditori[0].aggiungiProdotto(new ProdottoAlimentare(1.20, 20200101)); // scaduto

    // --- Popolo venditore 1 (5 prodotti) ---
    venditori[1].aggiungiProdotto(new ProdottoPerBambini(8.00, FasciaEta::ZERO_TRE));
    venditori[1].aggiungiProdotto(new ProdottoAlimentare(3.75, 20261130));
    venditori[1].aggiungiProdotto(new Prodotto(14.00));
    venditori[1].aggiungiProdotto(new ProdottoPerBambini(6.50, FasciaEta::SEI_NOVE));
    venditori[1].aggiungiProdotto(new ProdottoAlimentare(0.99, 20270101));

    // --- Popolo venditore 2 (5 prodotti) ---
    venditori[2].aggiungiProdotto(new Prodotto(99.90));
    venditori[2].aggiungiProdotto(new ProdottoAlimentare(4.20, 20200101)); // scaduto
    venditori[2].aggiungiProdotto(new ProdottoPerBambini(20.00, FasciaEta::NOVE_DODICI));
    venditori[2].aggiungiProdotto(new Prodotto(1.50));
    venditori[2].aggiungiProdotto(new ProdottoAlimentare(2.20, 20250801));

    // --- Stampa e riassunti ---
    for (int i = 0; i < 3; ++i) {
        cout << "\n--- Venditore n. " << i << " ---\n";
        cout << venditori[i] << "\n";
        cout << "Prezzo totale: €" << venditori[i].calcolaPrezzoTotale() << "\n";
        cout << "Valore magazzino (non scaduti): €" << venditori[i].calcolaValoreMagazzino() << "\n";
    }

    // Nota: i distruttori dei venditori verranno chiamati automaticamente alla fine di main,
    // liberando la memoria dei prodotti (dato che il Venditore è owner dei Prodotto*).
    return 0;
}
