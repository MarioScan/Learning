/*
    ------------------------------
    |           Alberi           |
    ------------------------------

   🔸 Si dice "grafo diretto" un insieme di nodi collegati mediante archi direzionati.

    🔸 Un "albero" è un grafo diretto in cui ogni NODO può avere un solo arco entrate
    ed un qualunque numero di archi uscenti 

    🔸 Se un NODO non ha archi uscenti allora si dice FOGLIA;

    🔸 Se un NODO non ha archi entranti allora si dice RADICE;

   🔸 Poiché in un albero non ci sono nodi con due o più archi entranti,
    per ogni albero di vede essere UNA ed UNA SOLA RADICE.


                              Bisnonno  <-- Radice
                            /   |  \
                          /     |    \
                        /       |      \
                     Sorella  Nonno    Sorella <-- Foglia
                                | ^ <- Nodo
                                |
                               / \
                             /     \
                           /         \
              Nodo ->   Figlio      Figlia <-- Foglia
                          |
                          |
                         /| \
                       /  |   \
                     /    |     \
                   /      |       \
                 Nipote  Nipote   Nipote <-- Foglie


   🔸 Quindi in generale possiamo dire che gli alberi sono una Generalizzazione delle liste:
    infatti:
        - Ogni elemento può avere più di un solo successore
        - Sono utili per rappresentare partizioni ricorsive di insieme e strutture gerarchiche


    ----------------------------------------------------------
    |           Alberi e strutture gerarchiche               |
    ----------------------------------------------------------

    - Il NODO da cui parte un ARCO si dice GENITORE;
    - Il NODO a cui arriva un ARCO si dice FIGLIO;
    - Due NODI con lo stesso GENITORE sono detti FRATELLI;
    - Da ogni NODO (NON-FOGLIA) di un ALBERO si dirama un SOTTOALBERO,
    quindi si intuisce la NATURA RICORSIVA di questa STRUTTURA DATI.
    
    ----------------------------------------------------------
    |           Alberi come strutture ricorsive              |
    ----------------------------------------------------------

  🔸  Definizione ricorsiva:
        Un albero è un insieme di nodi che:
        - O è vuoto;
        - Oppure ha un nodo chiamato RADICE da cui discendono:
            ZERO o PIU' SOTTOALBERI, detti anch'essi alberi.

    🔸 Dato un NODO, i NODI che appartengono al suo SOTTOALBERO, si dicono:
    DISCENDENTI.
    
    🔸 Dato un qualunque NODO, i NODI che si trovano nel CAMMINO DALLA RADICE
    ad ESSO, sono detti i suoi ASCENDENTI.


                                    A <-- Radice
                                   /|\
                                 /  |  \
                               /    |    \
                              B     E      F  <- Sottoalbero: F -> (G H I) 
                             / \         / | \                
                            /   \       /  |  \         
                           C     D     G   H   I <- Fratelli


Da C a radice:  B e A sono i nodi ASCENDENTI di C  


    ----------------------------------------------
    |           Profondità di un NODO            |
    ----------------------------------------------

  🔸  La profondità di un nodo si determina dal numero di archi dalla radice al nodo in questione.
    👉 Ricorsivamente:
      - La radice ha profondità 0
      - La profondità di un nodo non radice è 1 + la profondità del genitore

    👉 Calcolo:

      int profondita(Nodo* radice, Nodo* target, int livello = 0) {
          if (radice == nullptr) 
            return -1; // nodo non trovato
          
          if (radice == target) 
            return livello; //fine funzione 

          int left = profondita(radice->left, target, livello + 1); 
          
          if (left != -1) 
            return left;

          return profondita(radice->right, target, livello + 1);
      }


    ----------------------------------------------
    |             Cammini e Livelli              |
    ----------------------------------------------

  🔸  Continuando il discorso della profondità, possiamo dire che il livello di un nodo,
      è la sua distanza dalla radice:
      - La radice ha livello 1
        - I figli della radice livello 2 
          - I nipoti della radice livello 3 
              - e così via...

  🔸  I fratelli hanno lo stesso livello ma non tutti i nodi dello stesso livello sono fratelli, 
    ovvero, possono avere genitori differenti. 

  🔸 L'altezza di un albero è pari alla profondità della foglia di massima profondità,
    cioé, il cammino più lungo dalla radice alla foglia più distante.


       Livello 1 ->                 A <-- Radice
                                   /|\
                                 /  |  \ <- Ramo (o arco) AF
                               /    |    \
       Livello 2 ->           B     E      F  <- Sottoalbero: F -> (G H I) 
                             / \         / | \  <- Ramo (o arco) FI              
                            /   \       /  |  \         
       Livello 3 ->        C     D     G   H   I <- Fratelli

      -------------------------------------------------------------------------------------------------
      | Analisi:                                                                                      |
      |-----------------------------------------------------------------------------------------------|
      | Radice: A                                                                                     |
      | Genitori: A, B, F                                                                             | 
      | Figli: B, E, F, C, D, G, H, I                                                                 |
      | Fratelli: {B, E, F}, {C, D}, {G, H, I}                                                        |
      |                                                                                               |
      | Foglie: E, C, D, G, H, I                                                                      |
      | Nodi interni: B, F (non foglie perché hanno discendenti, ma non sono radice hanno ascendenti) |
      -------------------------------------------------------------------------------------------------

    ----------------------------------------------
    |             Alberi bilanciati              |
    ----------------------------------------------

    🔸 Un albero di profondità h si dice BILANCIATO (o EQUILIBRATO) se:

      1. Tutte le foglie si trovano alla stessa profondità;
      2. Ogni nodo interno, radice inclusa, ha lo stesso numero K di figli.
      
      
    ----------------------------------------------
    |               Albero Binario               |
    ----------------------------------------------    
    
    🔸 Un albero si dice BINARIO se ogni nodo ha al massimo due figli (sottoalberi),
    il sinistro e il destro.
      🔸 Un albero BINARIO non vuoto si dice DEGENERE se ogni nodo diverso da una foglia
         ha un solo figlio. 
         Per convenzione si assume che l'albero VUOTO sia DEGENERE

    - Un albero binario può contenere al massimo 2^k nodi a profondità k;
    - Il numero totale di nodi di un albero (foglie incluse) di profondità k
      è al massimo di 2^(k+1) - 1 nodi --> 2^(k+1) potenza di tutti i livelli es. 4 livelli (3+1) visto il primo livello è 0, e -1 perché livello 0 contiene solo UN elemento (la RADICE);
    👉 La profondità di un albero bilanciato è O(log n) 

    ----------------------------------------------
    |       Implementazione di un albero         |
    ---------------------------------------------- 

    Albero:
                        A
                      /   \
                    B      C
                     \   / \
                      D  E   F
                     /   \
                    G     H
    Struttura:

                          |Sx|A|Dx|
                           /     \
                         /         \
                       /             \
                     /                 \
                |Sx|B|Dx|           |Sx|C|Dx|                     
                       \            /       \
                   |Sx|D|Dx|     Sx|E|Dx| |Sx|F|Dx|
                    /                  \
               |Sx|G|Dx|            |Sx|H|Dx|

    Sx = Sinistra
    Dx = Destra
  


    ---------------------------------------------------------------------
    |       Albero Binario di Ricerca (BST – Binary Search Tree)        |
    ---------------------------------------------------------------------
    
    Un BST ha una proprietà fondamentale:

    🔹 Ogni nodo contiene un valore.
    🔹 Tutti i valori nel sottoalbero sinistro sono minori del nodo.
    🔹 Tutti i valori nel sottoalbero destro sono maggiori del nodo.
      
    Esempio di BST:

                      50
                     /  \
                   30    70
                  /  \  /  \
                 20 40  60 80

    🔍 2. Come funziona la ricerca binaria:
        Dato un valore da cercare (val), e un nodo corrente:

        1. Se il nodo è nullptr, il valore non è presente nell’albero.
        2. Se il valore è uguale al valore del nodo, trovato! (Centro! 🎯)
        3. Se val < nodo->valore, vai a sinistra.
        4. Se val > nodo->valore, vai a destra.

      🧠 Esempio ricerca:

        Cerchiamo 60:
        Nodo attuale: 50 → 60 > 50, vado a destra.
        Nodo attuale: 70 → 60 < 70, vado a sinistra.
        Nodo attuale: 60 → Trovato! ✅

    Vedremo meglio a breve con del codice, adesso passiamo alla creazione di un Albero in C++:

   🔸 1. Inserimento dei dati in un Albero binario di Ricerca (BST):
      I nuovi elementi vengono sempre inseriti come nuove foglie.

   🔸 2. Visita di un albero binario di ricerca (BST):
      Esistono tre strategie di visita notevoli:
        • Visita PREORDER visita prima la radice, quindi il sottoalbero sinistro 
          e per ultimo quello destro;
        • Visita INORDER processa prima il sottoalbero sinistro, quindi la radice
          ed infine il sottoalbero destro;
        • Visita POSTORDER processa prima il sottoalbero sinistro, poi quello
          destro ed infine la radice. 
    
   🔸 3. Costo della visita di un Albero Binario di Ricerca (BST):
      🔹 Complessità: T(n)=Θ(n) 
        • Devono essere fatti almeno n passi, dunque T(n)= Ω(n);
        • Rimane da provare che T(n)=O(n):
          • Se n=0:
            T(0)=c (c>0) (la procedura deve testare se il puntatore è diverso da NULL)
          • Se n>0:
            ...
      🔹 Spiegamolo meglio:
      Costo della visita (es. inorder, preorder, postorder)
      Quando visiti un albero, vuol dire che esplori TUTTI i nodi almeno una volta, giusto?
      Se hai n nodi, devi per forza passare almeno una volta da ciascuno.
      Quindi:
        🔹 Lower bound (Ω(n)): non puoi fare meno di n passi,
            perché devi visitare ogni nodo.
        🔹 Upper bound (O(n)): non fai più di c * n passi per qualche costante c,
            perché ogni nodo lo visiti una volta sola (o un numero limitato di volte 
            costante).

      Da qui si conclude che la complessità è Θ(n), cioè “proporzionale a n”.
      
      🔹 Il ragionamento formale:
        👉 Definisci:
          T(n) = tempo necessario per visitare un albero con n nodi.

        👉 Caso base:
          Se l’albero è vuoto (n=0),
          devi solo controllare se il puntatore è nullo (operazione costante):
          T(0) = c (costante)

        👉 Caso ricorsivo:
          Se l’albero non è vuoto, il tempo è dato dal:

          visitare il nodo corrente (costante)

          più visitare il sottoalbero sinistro (tempo T(n_sinistro))

          più visitare il sottoalbero destro (tempo T(n_destro))
          T(n) = T(n_sinistro) + T(n_destro) + d
          dove d è una costante per visitare il nodo corrente.

        👉 Da qui:
          Per ogni nodo il tempo è sommato una volta sola, quindi sommando su tutto l’albero:
          T(n) = d * n
          che è proprio Θ(n). 
                    ^^^^^^^^^^^

      ---------------------------------------------------------------------------------------------------------------------------------------------------------
      | Tipo di albero                                  |	 Altezza (h)           |  Ricerca / Inserimento / Cancellazione       |  Visita (Traversale)        |
      |-------------------------------------------------|------------------------|----------------------------------------------------------------------------|
      | Albero Binario Generico                         |	 O(n) (peggiore caso)	 |  O(n)	                                      |  Θ(n)                       |
      | Albero Binario di Ricerca (BST) non bilanciato  |  O(n) (peggiore caso)  |  O(n)	                                      |  Θ(n)                       |
      | Albero Binario di Ricerca (BST) Bilanciato      |  O(log n)	             |  O(log n)     	                              |  Θ(n)                       |
      | Albero B (B-Tree)	                              |	 O(log n)	             |  O(log n)                                    |  Θ(n)                       |
      | Albero Heap (Max/Min Heap)                      |	 O(log n)	             |  O(log n) (inserimento, estrazione max/min)  |  Θ(n) (per visita completa) |
      ---------------------------------------------------------------------------------------------------------------------------------------------------------

      📌 1. Albero Binario Generico:
        Altezza può essere grande come n (ad esempio una lista collegata).
        Ricerca e inserimento possono dover scorrere tutta la profondità, quindi O(n).

      📌 2. Albero Binario di Ricerca (BST) non bilanciato:
        Se inserisci nodi in ordine crescente o decrescente, diventa una lista: altezza O(n).
        Peggior caso: ricerche, inserimenti e cancellazioni degradano a O(n).

      📌 3. BST Bilanciato: 
        Mantengono altezza O(log n).
        Operazioni di ricerca, inserimento e cancellazione sono efficienti: O(log n).
        Traversal è comunque Θ(n), perché devi visitare ogni nodo.

      📌 4. Albero B (B-Tree):
        Usato in database e file system.
        Mantiene altezza bassa O(log n).
        Operazioni su blocchi di dati, sempre O(log n).

     📌 5. Heap (Max-Heap, Min-Heap):
        Albero binario completo, altezza O(log n).
        Inserimento ed estrazione del massimo/minimo sono O(log n).
        Visita completa è sempre Θ(n) perché devi toccare ogni nodo.


   🔸 4. Ricerca in un Albero Binario di Ricerca (BST)
      - Ricerca iterativa
      - Ricerca ricorsiva
   🔸 5. Massimo e minimo (di un Albero Binario di Ricerca (BST))

   🔸 6. Successore di x (di un Albero Binario di Ricerca (BST))

   🔸 7. Cancellazione di un nodo (di un Albero Binario di Ricerca (BST))
      - Caso in cui nodo è una foglia
      - Caso in cui nodo ha un solo figlio
      - Caso in cui nodo ha due figli
      - Procedura "Trapianta"

*/

#include <iostream>
using namespace std;

template <typename T>
class Nodo
{
    private:
        T valore;
        Nodo<T>* left;
        Nodo<T>* right;
        
    public:
        Nodo(const T& val) : valore(val) {}

        const T& get_valore() const { return valore; }
        Nodo<T>* get_left() const { return left; }
        Nodo<T>* get_right() const { return right; }

        void set_valore(const T& newVal) { valore = newVal; }
        void set_left(Nodo* newLeft) { left = newLeft; }
        void set_right(Nodo* newRight) { right = newRight; } 
};

template <typename T>
class Albero
{
    private: 
        Nodo<T>* root;
    
        Nodo<T>* insertHelper(Nodo<T>* node, const T& val)
        {
            if(node == nullptr) //inserimento della radice (ovvero il primo nodo dell'albero)
                return new Nodo<T>(val);

            else if(val < node->get_valore()) //è più piccolo della radice, allora deve andare a sinistra
                node->set_left( insertHelper(node->get_left(), val) );
            else 
                node->set_right( insertHelper(node->get_right(), val) );

            return node;
        }

        void displayHelper(Nodo<T>* node) const 
        {
            if(node != nullptr)
            {
                displayHelper(node->get_left());
                cout << node->get_valore() << " ";
                displayHelper(node->get_right());
            }
        }

        void destroy(Nodo<T>* node) //usata nel distruttore
        {
            if(node)
            {
                destroy(node->get_left());
                destroy(node->get_right());
                delete node;
            }
        }
        
        bool searchHelper(Nodo<T>* node, int key)
        {
            if(node == nullptr)
            {
                return false; //non trovato
            }
            else if(key == node->get_valore())
                return true;
            else if(key < node->get_valore())
                return searchHelper(node->get_left(), key);
            else 
                return searchHelper(node->get_right(), key);
        }

        Nodo<T>* removeHelper(Nodo<T>* node, int key)
        {   
            if(node == nullptr)
                return node;
            else if(key < node->get_valore())
            {
                node->set_left( removeHelper(node->get_left(), key) );
            } 
            else if(key > node->get_valore())
            {
                node->set_right( removeHelper(node->get_right(), key) );
            } 
            else //Nodo trovato
            {
                if(node->get_left() == nullptr && node->get_right() == nullptr) //allora il nodo da rimuovere è una FOGLIA
                {
                    delete node; //cancello nodo dalla memoria
                    return nullptr; //ritorno nullptr per aggiornare puntatore del genitore
                }
                else if(node->get_right() != nullptr) //esiste figlio a destra, trova successore per rimpiazzare questo nodo --> Non vogliamo che il figlio si ritrovi orfano!
                {
                    node->set_valore( successor(node) ); //(1)*
                    node->set_right( removeHelper(node->get_right(), node->get_valore()) ); //non vogliamo perdere il figlio
                }
                else //trova precedessore per rimpiazzare questo nodo
                {
                    node->set_valore( predecessor(node) ); //(2)*
                    node->set_left( removeHelper(node->get_left(), node->get_valore()) );
                }
            }
            return node;
        }

        int successor(Nodo<T>* node) //trova valore più piccolo sotto al figlio destro data la nostra radice (1)*
        {
            node = node->get_right(); // passo 1: spostati al sottoalbero destro
            while(node->get_left() != nullptr) // passo 2: vai più a sinistra possibile
            {
                node = node->get_left();
            }
            return node->get_valore(); // passo 3: ritorna il valore di quel nodo
        }

        int predecessor(Nodo<T>* node) //trova valore più grande sotto al figlio sinistro data la nostra radice (2)*
        {
            node = node->get_left(); // passo 1: vai al figlio sinistro
            while(node->get_right() != nullptr) // passo 2: vai il più a destra possibile
            {
                node = node->get_right();
            } 
            return node->get_valore(); // passo 3: ritorna il valore di quel nodo
        }

        void inOrderHelper(Nodo<T>* node) const //Sinistra -> radice -> destra
        {
            if(!node) { return; }
          inOrderHelper(node->get_left());
          cout << node->get_valore() << endl;
          inOrderHelper(node->get_right());
        }
        
        void postOrderHelper(Nodo<T>* node) const //sinistra -> destra -> radice
        {
            if(!node) { return; }
          postOrderHelper(node->get_left());
          postOrderHelper(node->get_right());
          cout << node->get_valore() << endl;
        }

        void preOrderHelper(Nodo<T>* node) const //radice -> sinistra -> destra
        {
            if(!node) { return; }
          cout << node->get_valore() << endl;
          preOrderHelper(node->get_left());
          preOrderHelper(node->get_right());
        }

        T max(T a, T b) const
        {
            return (a > b) ? a : b;
        }

        int get_altezza_helper(Nodo<T>* node) const
        {
            if(!node)
                return -1; //albero vuoto o foglia dell'albero
            
            return 1 + max( get_altezza_helper(node->get_left()), get_altezza_helper(node->get_right()) );
        }

        int get_nodi_helper(Nodo<T>* node) const 
        {
            if(!node)
                return 0; //albero vuoto o foglia dell'albero, in questo caso ci serve contare anche loro!
            
            return 1 + get_nodi_helper(node->get_left()) + get_nodi_helper(node->get_right()); 
        }

        int get_foglie_helper(Nodo<T>* node) const
        {
            if(!node)
                return 0; //albero vuoto
            if(!node->get_left() && !node->get_right()) //se non ha figli allora è FOGLIA
                return 1; 
            return get_foglie_helper(node->get_left()) + get_foglie_helper(node->get_right());  
        }

        int get_interni_helper(Nodo<T>* node) const
        {
            if(!node || (!node->get_left() && !node->get_right()))
                return 0; //albero vuoto

            return 1 + get_interni_helper(node->get_left()) + get_interni_helper(node->get_right());
        }

        int isBalancedHelper(Nodo<T>* node) const
        {
            if(!node)
                return 0;
            
            int leftSide = isBalancedHelper(node->get_left());
            if(leftSide == -1)
                return -1;

            int rightSide = isBalancedHelper(node->get_right());
            if(rightSide == -1)
                return -1;
            
            if ( (leftSide - rightSide) != 0) return -1;

            return 1 + max(leftSide, rightSide);
        }

        int maxPathHelper(Nodo<T>* node) const
        {
            if(!node)
                return 0;
            return 1 + (maxPathHelper(node->get_left()), maxPathHelper(node->get_right()));
        }

    public:
        Albero() : root(nullptr) {}
        ~Albero() 
        { 
            cout << "\n[DEBUG] Distruttore Albero chiamato." << endl;
            destroy(root); 
        }

        void insert(const T& valore)
        {
            root = insertHelper(root, valore);
        }

        void display()
        {
            displayHelper(root); 
            cout << endl;
        }

        bool search(int key)
        {
            return searchHelper(root,key);
        }

        void remove(int key)
        {
            cout << "Elimino valore: \"" << key << "\" dall'albero di Ricerca." << endl;
            if(search(key)) //se ritorna true, cioé se esiste, allora:
                root = removeHelper(root,key);
            else 
                cout << "Valore: \"" << key << "\" non trovato." << endl;
        }

        void preOrder() const //radice -> sinistra -> destra
        {
            cout << "Stampa in Pre-Order:" << endl;
            preOrderHelper(root);
            cout << endl;
        }

        void inOrder() const //Sinistra -> radice -> destra
        {
            cout << "Stampa in In-Order:" << endl;
            inOrderHelper(root);
            cout << endl;
        }

        void postOrder() const //sinistra -> destra -> radice
        {
            cout << "Stampa in Post-Order:" << endl;
            postOrderHelper(root);
            cout << endl;
        }

        bool minValue(T& val) const
        {
            if(!root)
                return false; //nodo vuoto
            
            Nodo<T>* current = root;
            while(current->get_left())
            {
                current = current->get_left();
            }
            val = current->get_valore();
            return true;
        }

        bool maxValue(T& val) const
        {
            if(!root)
                return false;

            Nodo<T>* current = root;

            while(current->get_right())
            {
                current = current->get_right();
            }
            val = current->get_valore();
            return true;
        }

        int get_altezza() const
        {
            return get_altezza_helper(root);
        }

        int get_nodi() const 
        {
            return get_nodi_helper(root);
        }

        int get_foglie() const
        {
            return get_foglie_helper(root);
        }

        int get_interni() const
        {
            return get_interni_helper(root);
        }

        bool isBalanced() const
        {
            //un albero è bilanciato se ogni nodo ha stesso numero di figli e stessa profondità
            return isBalancedHelper(root) != -1; // se è uguale a -1 allora ritorna false
        }

        int maxPath() const 
        {
            return maxPathHelper(root);
        }
};


int main()
{
    Albero<int> tree;
    tree.insert(50); //radice 
    tree.insert(30);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);
    tree.insert(40);
    tree.insert(20);
    tree.insert(5);

    tree.display();

/*
        50
       /  \
     30    70
    /  \  /  \
   20 40  60 80
*/

    tree.remove(5);
    cout << "\nAlbero aggiornato:" << endl;
    tree.display();

    cout << "Ricerca valore 2 nell'albero: " << (tree.search(2) ? "Trovato." : "Non trovato.") << endl;

    tree.remove(0);

    cout << endl;
    tree.preOrder();
    tree.inOrder();
    tree.postOrder();

    cout << endl; 
    cout << "Altezza albero: " << tree.get_altezza() << endl;
    cout << "Numero nodi: " << tree.get_nodi() << endl;
    cout << "Numero foglie: " << tree.get_foglie() << endl;
    cout << "Numero interni: " << tree.get_interni() << endl; //3 --> Anche la radice è un nodo interno!
    cout << "E' bilanciato: " << (tree.isBalanced() ? "Si." : "No!") << endl; 
    cout << "Cammino massimo: " << tree.maxPath() << endl;
    
    return 0;
}





