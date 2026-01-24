/*

Liste Doppiamente Concatenate 🏰⚔️
PROVA D’ESAME – Programmazione 2
Si consideri una classe Mercante che rappresenta un commerciante medievale.
La classe ha i seguenti attributi privati:

id (intero)

nome (stringa)

città (stringa)

profitto (double): guadagni totali in monete d’oro

La classe ha i seguenti metodi pubblici:

costruttore

get degli attributi

stampa(): stampa nel formato:
id: nome da città - profitto monete

Si consideri una classe Carico che rappresenta la merce venduta dal mercante.
Attributi privati e relativi get/set:

quantità (int): numero di unità di merce

tipo (stringa): descrizione del prodotto (es. "spezie", "velluto")

Si consideri una classe MercanteConCarico derivata da Mercante che aggiunge:

carico: puntatore a Carico

Metodi pubblici:

get_quantità_carico(): restituisce la quantità di merce

stampa():

con carico: id: nome da città - profitto monete [carico: X unità di tipo Y]

senza carico: id: nome da città - profitto monete

Si implementi la Lista Doppiamente Concatenata per gestire i mercanti (oggetti di tipo Mercante o MercanteConCarico).
Il programma deve:

Leggere i dati dal file mercanti.txt nel formato:

id nome città profitto quantità tipo
Se quantità = 0, il mercante non ha carico.

Inserire in lista in ordine decrescente di profitto.

Eliminare i mercanti con profitto inferiore a 100 monete e stampare:
Mercante rimosso: Nome da Città - ID: ...

Stampare il contenuto della lista.

Calcolare il totale delle unità di carico possedute dai mercanti rimanenti.

*/