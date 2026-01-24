/*

    ------------------------
    | LE LISTE CONCATENATE |
    ------------------------

    🔍 Cos’è una lista concatenata?
        Una lista concatenata è una struttura dati dinamica composta da nodi, 
        dove ogni nodo punta al nodo successivo (e a volte anche al precedente, nelle liste doppie).

    ✅ Vantaggi:
        <+> Cresce dinamicamente
        <+> Inserimenti/cancellazioni veloci in posizione nota (O(1))

    ❌ Svantaggi:
        <-> Accesso sequenziale (O(n))
        <-> Gestione dei puntatori più complessa

    ✅ Tipi principali:
        1. Lista Singola: 
            Ogni nodo punta al successivo.

        2. Lista Doppia:
            Ogni nodo ha prev e next.

        3. Lista Circolare:
            L’ultimo nodo punta al primo.

    📦 Struttura base:
                struct Nodo {
                    int val;
                    Nodo* next;
                };

    🔧 Operazioni sui nodi:
        <+>  Inserimento (push_front, push_back)
        <+>  Cancellazione (delete_val)
        <+>  Ricerca (find)
        <+>  Stampa (print)

    🔄 Implementazione con sentinelle:
    Usiamo un nodo fittizio per semplificare inserimenti e rimozioni.

*/