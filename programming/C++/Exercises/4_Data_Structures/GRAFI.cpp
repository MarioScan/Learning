/*
    -------------------------------------
    |             GRAFI 📊              |
    -------------------------------------

    🧠 DEFINIZIONE GENERALE
    Un grafo è una struttura dati formata da:
      📌 V: insieme dei vertici (o nodi)
      📌 E: insieme degli archi (o collegamenti) tra coppie di vertici

    Un grafo può essere:
    - 🔁 **Non direzionato** (archi senza direzione)
    - 🔀 **Direzionato** (archi con direzione da un nodo all’altro)

    I grafi sono fondamentali in informatica: rappresentano reti, mappe,
    connessioni tra oggetti, e sono al centro di molti problemi computazionali.

    Vedremo qui le basi teoriche e gli algoritmi elementari di visita.

    -------------------------------------
    |       GRAFI DIREZIONATI 🔀        |
    -------------------------------------

    Un grafo direzionato G = (V, E) ha archi **con direzione**.

    Esempio: arco (u, v)
      👉 Parte da u (nodo sorgente)
      👉 Arriva a v (nodo destinazione)
      👉 Si dice:
           - "uscente da u"
           - "entrante in v"

    ⚠️ L’adiacenza NON è simmetrica:
        se (u,v) ∈ E, non implica che (v,u) ∈ E

    Rappresentazione grafica:

                    / \
    A -----------> B <-     C
    ^             /|        ^   
    |           /  |        |
    |         /    |        |
    |       /      |        |
    |     /        |        |
    |   /          |        |
    | ▼            ▼        |
    D <----------> E        F

    -------------------------------------
    |     GRAFI NON DIREZIONATI 🔁      |
    -------------------------------------

    In un grafo non direzionato G = (V, E):
      📌 Gli archi NON hanno direzione
      📌 Le coppie (u,v) sono **non ordinate**
      📌 u e v sono adiacenti **simmetricamente**

      📌  Rappresenta una connessione bidirezionale.

    Un arco (u,v) implica che:
      🔁 u è connesso a v
      🔁 v è connesso a u

    Rappresentazione grafica:

    A ------------- B       C
     \              |       |
       \            |       |
         \          |       |
           \        |       |
             \      |       |
               \    |       |
                 \  |       |
    E               F       G


    -------------------------------------
    |         GRADO DI VERTICE          |
    -------------------------------------

    📍 Grado di un vertice

      - In un grafo NON direzionato:
          ➤ Grado = numero di archi incidenti al nodo

      - In un grafo DIREZIONATO:
          ➤ Grado entrante = # archi in ingresso
          ➤ Grado uscente = # archi in uscita
          ➤ Grado totale = somma dei due

    ---------------------------------------------
    |           CAMMINI E SOTTOCAMMINI          |
    ---------------------------------------------
    
    📍 Cammino (path)
      - Un ** cammino di lunghezza k ** da u a v è una sequenza:
            v₀, v₁, ..., vₖ   con v₀ = u, vₖ = v
      - Ogni coppia consecutiva (vᵢ, vᵢ₊₁) ∈ E

      - Un nodo v è detto **raggiungibile** da u se esiste un cammino da u a v

      - Un cammino è detto **semplice** se tutti i nodi sono distinti

    📍 Sottocammino
    Un **sottocammino** è una porzione (subsequenza) di un cammino più lungo.

    Esempio:
      Dato un cammino:
        v₀ → v₁ → v₂ → v₃ → v₄ → v₅

      Un sottocammino può essere:
        v₂ → v₃ → v₄

    In generale:
      vᵢ, ..., vⱼ   con  0 ≤ i ≤ j ≤ k

    È importante per identificare sotto-percorsi in problemi come:
    - verifica di raggiungibilità parziale
    - sottosequenze valide di un algoritmo

    -------------------------------------
    |               CICLI               |
    -------------------------------------    
        
    📍 Ciclo
    Un **ciclo** è un cammino che inizia e termina nello stesso nodo:
      v₀ → v₁ → ... → vₖ   con v₀ = vₖ

    Il ciclo è:
      🔹 **semplice** se tutti i vertici (tranne il primo/ultimo) sono distinti
      🔹 **non semplice** se ripete vertici oltre al primo/ultimo

    📌 Un grafo **senza cicli** si dice **aciclico**

    - Esempio: gli **alberi** sono grafi aciclici
    - I cicli sono centrali in problemi come: rilevamento di deadlock, dipendenze circolari, ecc.

    ---------------------------------------------
    |     CONNESSIONE grafo NON DIREZIONATO     |
    ---------------------------------------------

    📍 Grafo non direzionato connesso
    - Ogni **coppia di nodi** è collegata da almeno un cammino

    📍 Componenti connesse
    - Suddivisioni del grafo in **sottografi connessi**
    - Due nodi appartengono alla stessa componente se sono **raggiungibili tra loro**

    Esempio di componenti connesse:
      {1, 2, 5}, {3, 6}, {4}

    📌 Un grafo **è connesso** se ha una **sola** componente connessa

    -------------------------------------------
    |     CONNESSIONE grafo DIREZIONATO 🔀    |
    -------------------------------------------

    📍 Componente fortemente connessa (grafo orientato)
    - È un **sottografo massimo** in cui:
        ∀ coppie (u, v), u è raggiungibile da v e v è raggiungibile da u

    📌 Un grafo **direzionato è fortemente connesso** se ha **una sola** componente fortemente connessa
       (cioè tutti i nodi si raggiungono tra loro in entrambe le direzioni)

    Esempio di componenti fortemente connesse:
      {1, 2, 4, 5}, {3}, {6}

    -------------------------------------
    |     SOTTOGRAFI E GRAFI COMPLETI   |
    -------------------------------------

    📍 Sottografo
    Un grafo G' = (V', E') è un **sottografo** di G = (V, E) se:
      - V' ⊆ V (sottoinsieme di nodi)
      - E' ⊆ E (sottoinsieme di archi che collegano solo nodi in V')

    📍 Grafo completo
    Un grafo **non direzionato** è **completo** se:
      - Ogni coppia di nodi è **adiacente**, cioè collegata direttamente da un arco

    ⚠️ In un grafo completo con n nodi, ci sono:
      - ⬤ n(n-1)/2 archi se è **non direzionato**
      - ⬤ n(n-1) archi se è **direzionato**

      (1) Esempio:

      Sia G = (V,E) un grafo non orientato (non direzionato) COMPLETO:

      A ------- B
      | \     / |
      |   \ /   |
      |   / \   |
      | /     \ |
      C ------- D

      In quanto completo ogni nodo è connesso a tutti gli altri, 
      per tanto avrà n(n-1)/2 archi, infatti:
      A,B,C,D = 4 nodi --> 4(4-1)/2 = 12/2 = 6, e contandoli abbiamo 
      effettivamente 6 nodi.

      (2) Esempio:

      Sia G = (V,E) un grafo orientato (direzionato) COMPLETO:

      A <-----> B
      ^ ^     ^ ^
      |   \ /   |
      |   / \   |
      ▼ ▼     ▼ ▼
      C <-----> D      
      
      A,B,C,D = 4 nodi --> 4(4-1) = 4x3 = 12, difatti:
      contandoli abbiamo proprio 12 archi.



    -------------------------------------
    |    RAPPRESENTAZIONE DEI GRAFI 🚀  |
    -------------------------------------

    📌 La cardinalità |V| rappresenta il numero di vertici nel grafo,
    ovvero la dimensione dell'insieme V.

    Esistono due metodi fondamentali per rappresentare un grafo:

    -------------------------------------
    |       MATRICE DI ADIACENZA        |
    -------------------------------------

    Una **matrice di adiacenza** è una matrice quadrata n × n, dove n = |V|.
    Ogni cella matrix[u][v] assume valore:
      ➤ 1 (o true) se esiste un arco da u a v
      ➤ 0 (o false) altrimenti

    ✅ Utile quando il grafo è denso (molti archi).
    ❌ Poco efficiente in memoria per grafi sparsi.

    Esempio di grafo direzionato:

    Sia A = [aᵢⱼ] una matrice tale che:
    aᵢⱼ = 1 se (i, j) ∈ E

    Rappresentazione grafica:

    A -----------> B            C
    |            ^ |          / |
    |           /  |        /   |
    |        /     |      /     |
    |      /       |    /       |
    |    /         |  /         |
    ▼  /           ▼ ▼          ▼
    D <----------- E            F<-
                                \ /

    -------------------------------------
    |        LISTA DI ADIACENZA         |
    |      (GRAFI NON DIREZIONATI)      |
    -------------------------------------

    Una **lista di adiacenza** è un array di |V| liste, una per ciascun vertice.

    ➤ Adj[u] contiene tutti i vertici v tali che (u,v) ∈ E

    ✅ Vantaggiosa nei grafi sparsi: utilizza meno memoria
    ❌ Meno immediata da consultare per sapere se un arco esiste

    ➤ Nei grafi non direzionati, la somma delle lunghezze di tutte le liste è 2|E|

    Esempio:

    Grafo non orientato:              Lista di adiacenza:

    A ------------ B                  A -> B -> D -> NULL
    |             /|  \               B -> A -> D -> C -> E -> NULL
    |            / |    \             C -> B -> E -> NULL
    |          /   |      \           D -> A -> E -> B -> NULL
    |        /     |       C          E -> D -> B -> C -> NULL
    |      /       |     /       
    |    /         |   /         
    |  /           | /          
    D ------------ E       

    -------------------------------------
    |        LISTA DI ADIACENZA         |
    |        (GRAFI DIREZIONATI)        |    
    -------------------------------------

    Anche qui, abbiamo un array di |V| liste, una per ogni vertice u.

    ➤ Adj[u] contiene tutti i vertici v tali che (u,v) ∈ E (uscente da u)

    ➤ Nei grafi direzionati, la somma delle lunghezze di tutte le liste è |E|

    Esempio:

    Grafo orientato:                    Lista di adiacenza:

    A -----------> B            C       A -> B -> D -> NULL        
    |            ^ |          / |       B -> E -> NULL
    |           /  |        /   |       C -> E -> F -> NULL
    |        /     |      /     |       D -> B -> NULL
    |      /       |    /       |       E -> D -> NULL
    |    /         |  /         |       F -> F -> NULL
    ▼  /           ▼ ▼          ▼
    D <----------- E            F<-
                                \ /

    ---------------------------------------------
    |       COSTI DI RAPPRESENTAZIONE E VISITA   |
    ---------------------------------------------

    📦 COSTO SPAZIALE

    ➤ Matrice di adiacenza (n × n):
        • Spazio = O(V²)        ⛔ inefficiente per grafi sparsi
        • Ogni cella rappresenta un possibile arco

    ➤ Lista di adiacenza (array di liste):
        • Spazio = O(V + E)     ✅ più compatta per grafi sparsi

    🧮 COSTO TEMPORALE DI ACCESSO

    ➤ Matrice di adiacenza:
        • Verifica esistenza arco (u,v): O(1)
        • Scorrere tutti i vicini di u: O(V)

    ➤ Lista di adiacenza:
        • Verifica esistenza arco (u,v): O(deg(u))     [grado di u]
        • Scorrere i vicini: O(deg(u))

    💡 Conclusione:
      - Per grafi **densi**: matrice più efficiente
      - Per grafi **sparsi**: lista molto più scalabile


      

    ----------------------------------
    |       FUNZIONI E ALGORITMI     |
    |       APPLICATE AI GRAFI       |
    ----------------------------------

    Vedremo i seguenti algoritmi fondamentali per l’esplorazione dei grafi:

    ----------------------------------------
    |      Ricerca in Ampiezza - BFS       |
    |      Breadth-First Search (BFS)      |
    ----------------------------------------
    🔷 **Ricerca in Ampiezza (Breadth-First Search - BFS)**
      ➤ Visita i nodi per livelli, partendo da un nodo sorgente `s`
      ➤ Utilizza una **coda (FIFO)**

    ▶️ Idee chiave:
      - Tutti i nodi inizialmente sono colorati **bianchi** (non visitati)
      - Quando vengono scoperti, diventano **grigi**
      - Quando sono completamente esplorati, diventano **neri**
      Quindi:
        • I nodi grigi formano la **frontiera attiva**
        • I nodi neri sono quelli **già esplorati completamente**

    🔹 Risultati prodotti
      • `d[v]`  →  distanza minima in archi da `s` nodo sorgente
      • `π[v]`  →  predecessore nel **Breadth‑First Tree** (BFT)

    ⏱️ **Complessità**  (lista di adiacenza)
      • Tempo  **O(|V| + |E|)**
      • Spazio **O(|V|)**  (colori, distanze, predecessori, coda)

    🔹 Output: albero BFS, distanze minime dalla sorgente, predecessori
  |                                                                                |   
  ----------------------------------------------------------------------------------

    🔸 **Print-Path** – cammino minimo da `s` a `v`
      ➤ Stampa il percorso minimo (se esiste) dalla sorgente a un nodo destinazione
      ➤ Utilizza l’array dei predecessori costruito durante la BFS
      -->   • **Complessità** `O(|V|)`   (profondità massima del cammino)
    
  ---------------------------------------------------------------------------------  
    
  -------------------------------------------
  |          Ricerca in Profondità          |
  |        (Depth-First Search - DFS)       |
  -------------------------------------------

    📝 **Ricerca in Profondità (Depth-First Search - DFS)**
      ➤ Esplora ricorsivamente in profondità prima di tornare indietro
      ➤ Utilizza uno **stack implicito** nella ricorsione

    ▶️ Produce una **foresta DFS** (più alberi se il grafo non è connesso)

     🔹 Dati per ogni nodo `v`
    • `d[v]`  →  tempo di scoperta (BIANCO → GRIGIO)
    • `f[v]`  →  tempo di completamento (GRIGIO → NERO)
    • `π[v]`  →  predecessore

    • L’insieme dei predecessori `π` definisce una **foresta** (più alberi se il grafo non è connesso)

    🔹 Ogni nodo ha due timestamp:
      - tempo di scoperta (d)
      - tempo di fine visita (f)

    🔹 Utilizzata in:
      - Rilevamento cicli
      - Ordinamento topologico

      - Classificazione degli archi :
        albero, indietro, avanti, incrociati
       -> (Tree, Back, Forward, Cross)
      
      ---------------------------------------
      | Tipo     | Condizione su d/f        |
      | Tree     | scopro nodo bianco       |
      | Back     | verso antenato (GRIGIO)  |
      | Forward  | verso discendente NERO   |
      | Cross    | resto dei casi           |
      ---------------------------------------

      ⏱️ Complessità:   Tempo O(|V| + |E|)   |   Spazio O(|V|)

*/

// --- ESEMPIO COMPLETO GRAFI ---
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum Colore { BIANCO, GRIGIO, NERO };

struct Nodo {
    Colore colore;
    int distanza;
    int predecessore;
    int discovery_time;
    int finish_time;
};

class Grafo {
private:
    int V;
    int tempo;
    vector<vector<int>> adj;

public:
    vector<Nodo> nodi;

    Grafo(int vertici) : V(vertici), tempo(0), adj(vertici), nodi(vertici) {}

    void aggiungiArco(int u, int v) {
        adj[u].push_back(v);
    }

    void bfs(int s);
    void printPath(int s, int v);
    void dfs();
    void dfsVisit(int u);
};

// --- BFS ------------------------------------------------------------
void Grafo::bfs(int s) {
    for (auto& n : nodi) {
        n.colore = BIANCO;
        n.distanza = -1;
        n.predecessore = -1;
    }
    nodi[s].colore = GRIGIO;
    nodi[s].distanza = 0;

    queue<int> Q;
    Q.push(s);

    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int v : adj[u]) {
            if (nodi[v].colore == BIANCO) {
                nodi[v].colore = GRIGIO;
                nodi[v].distanza = nodi[u].distanza + 1;
                nodi[v].predecessore = u;
                Q.push(v);
            }
        }
        nodi[u].colore = NERO;
    }
}

// --- Print Path -----------------------------------------------------
void Grafo::printPath(int s, int v) {
    if (s == v) {
        cout << s;
    } else if (nodi[v].predecessore == -1) {
        cout << "Nessun cammino da " << s << " a " << v << endl;
    } else {
        printPath(s, nodi[v].predecessore);
        cout << " -> " << v;
    }
}

// --- DFS ------------------------------------------------------------
void Grafo::dfs() {
    for (auto& n : nodi) {
        n.colore = BIANCO;
        n.predecessore = -1;
    }
    tempo = 0;
    for (int u = 0; u < V; ++u)
        if (nodi[u].colore == BIANCO)
            dfsVisit(u);
}

void Grafo::dfsVisit(int u) {
    tempo++;
    nodi[u].discovery_time = tempo;
    nodi[u].colore = GRIGIO;

    for (int v : adj[u]) {
        if (nodi[v].colore == BIANCO) {
            nodi[v].predecessore = u;
            dfsVisit(v);
        }
    }

    nodi[u].colore = NERO;
    tempo++;
    nodi[u].finish_time = tempo;
}

// --- MAIN -----------------------------------------------------------
int main() {
    Grafo g(6);
    g.aggiungiArco(0, 1);
    g.aggiungiArco(0, 3);
    g.aggiungiArco(1, 4);
    g.aggiungiArco(2, 4);
    g.aggiungiArco(2, 5);
    g.aggiungiArco(3, 1);
    g.aggiungiArco(4, 3);
    g.aggiungiArco(5, 5); // ciclo su sé stesso

    cout << "\n--- BFS da sorgente 0 ---\n";
    g.bfs(0);
    for (int i = 0; i < 6; i++)
        cout << "Nodo " << i << ": distanza = " << g.nodi[i].distanza << ", predecessore = " << g.nodi[i].predecessore << endl;

    cout << "\nCammino da 0 a 4: ";
    g.printPath(0, 4);

    cout << "\n\n--- DFS su tutto il grafo ---\n";
    g.dfs();
    for (int i = 0; i < 6; i++) {
        cout << "Nodo " << i << ": discovery = " << g.nodi[i].discovery_time
             << ", finish = " << g.nodi[i].finish_time << ", predecessore = " << g.nodi[i].predecessore << endl;
    }

    return 0;
}
