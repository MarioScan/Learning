#ifndef BTS_H
#define BTS_H

/* Nota alberi:
inOrder(simmetrica): sinistro -> root -> destro
PreOrder(anticipata): root -> sinistro -> destro
PostOrder(posticipata): sinsitro -> destro -> root
*/

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Nodo
{
    private:
        T dato;
        Nodo<T>* left;
        Nodo<T>* right;
    public:
        Nodo(const T& data) : dato(data), left(nullptr), right(nullptr) {}
        ~Nodo() {}
        
        const T& get_dato() const { return dato; }
        Nodo<T>* get_left() const { return left; }
        Nodo<T>* get_right() const { return right; }
        
        void set_dato(const T& newDato) { dato = newDato; }
        void set_left(Nodo<T>* newLeft) { left = newLeft; }
        void set_right(Nodo<T>* newRight) { right = newRight; } 
};

template <typename T>
class BTS
{
    private:
        Nodo<T>* root;

        Nodo<T>* searchHelper(Nodo<T>* node, const string& nomePadre) //ricerca preOrder
        {
            if(!node)
                return nullptr;
            
            if(node->get_dato()->get_nome() == nomePadre)
                return node;
            
            Nodo<T>* leftSearch = searchHelper(node->get_left(),nomePadre);
            if(leftSearch) 
                return leftSearch;

            return searchHelper(node->get_right(),nomePadre);
        }

        void insertChildHelper(const string& nomePadre, const T& nuovoDato)
        {
            Nodo<T>* nuovo = new Nodo<T>(nuovoDato);
            if(!nuovo)
            {
                cerr << "Errore, impossibile creare nuovo nodo [insertChildHelper] " << endl;
                return;
            }
            
            Nodo<T>* padre = searchHelper(root,nomePadre);
            if(!padre)
            {
                cerr << "Padre non trovato!" << endl;
                return;
            }

            if(!padre->get_left())
            {
                padre->set_left(nuovo);
                padre->get_dato()->set_figlioSinistro(nuovoDato);
            }

            else if(!padre->get_right())
            {
                padre->set_right(nuovo);
                padre->get_dato()->set_figlioDestro(nuovoDato);
            }

            else 
            {
                cerr << "Errore, hai gia' due figli!" << endl;
                exit(1);
            }
        }
        void printPostOrderHelper(Nodo<T>* node) const
        {
             if(!node)
                return;
            printPostOrderHelper(node->get_left());
            printPostOrderHelper(node->get_right());
            node->get_dato()->print();
            cout << endl;
        }

        void findFatherOf_Helper(Nodo<T>* node, const string& nomeFiglio,string& result) const
        {
            if(!node || result != "")
                return;
            //ricerca in PreOrder -> root -> left -> right
            if((node->get_dato()->get_figlioSinistro() && node->get_dato()->get_figlioSinistro()->get_nome() == nomeFiglio) || (node->get_dato()->get_figlioDestro() && node->get_dato()->get_figlioDestro()->get_nome() == nomeFiglio))
            {
                result = node->get_dato()->get_nome(); //trovato
                return;
            }
            
            findFatherOf_Helper(node->get_left(),nomeFiglio, result);
            findFatherOf_Helper(node->get_right(),nomeFiglio, result);
        }

        //sovraccarico con tipo di ritorno string
        string findFatherOf_Helper(Nodo<T>* node, const string& nomeFiglio) const
        {
            if(!node)
                return "";
            
            if((node->get_dato()->get_figlioSinistro() && node->get_dato()->get_figlioSinistro()->get_nome() == nomeFiglio) || (node->get_dato()->get_figlioDestro() && node->get_dato()->get_figlioDestro()->get_nome() == nomeFiglio))
                return node->get_dato()->get_nome(); //trovato
            
            string leftRes = findFatherOf_Helper(node->get_left(),nomeFiglio);
            if(leftRes != "")
                return leftRes; //trovato!
            
            return findFatherOf_Helper(node->get_right(),nomeFiglio);
        }

        int get_heightHelper(Nodo<T>* node) const
        {
            if(!node) 
                return 0;
            return 1 + max(get_heightHelper(node->get_left()), get_heightHelper(node->get_right()));
            /*
            
                                 Gianni Morandi         <-- node != nullptr -> return 1 + max dei figli per ricorsione
                               /                \ 
                            Giorgio             Marco   <-- entrambi Giorgio e Marco faranno per ricorsione stessa cosa
                           /       \          /       \ 
                        Gnazio     Nino    Pancrazio   Luigitto <-- Gnazio, Nino, Pancrazio e Luigitto faranno per ricorsione stessa cosa
                      /      \                |        /     \ 
                 Francesco   Ciccio         Bilbo    Tobbi   Giuseppe <-- return 1 + 0 --> sono tutte foglie quindi qui termina ricorsione
            
            --> Albero di altezza 4.
            */
        }

        void collectNodes(Nodo<T>* node, vector<T>& v) const
        {
            if(!node)
                return;
            
            v.push_back(node->get_dato());
            collectNodes(node->get_left(),v);
            collectNodes(node->get_right(),v);
        }

        void printPerYear_helper(Nodo<T>* node) const
        {
            vector<T> sorter;
            collectNodes(node,sorter);
            //mergeSort(sorter,sorter.front(),sorter.back()); //errato --> non prende il posto ma solo il valore
            mergeSort(sorter,0,sorter.size()-1); // size - 1 indica indice ultimo elemento, ricorda: v[0],v[1],v[2] -> size = 3 

            for(T dato : sorter)
            {
                dato->printWithoutChildren();
                cout << endl;
            }
            
        }

        void merge(vector<T>& v, int left, int mid, int right) const
        {
            //divido vector v dei parametri in due: 
            //dimensione
            int leftSize = mid - left + 1; // OoOoOoO - oOoOoO -> left(inizio) mid(length/2) right(fine) -> leftSize = mid - left + 1 
            int rightSize = right - mid; 
            
            //vettori che dividono a metà il precedente
            vector<T> leftVector(leftSize), rightVector(rightSize);
            
            //carico i valori di v nei due nuovi vectors
            for(int i=0; i<leftSize; i++)
                leftVector.at(i) = v[left + i];
            for(int i=0; i<rightSize; i++)
                rightVector.at(i) = v[mid + 1 + i];

            //inizio sorting:
            int leftIndex = 0, rightIndex = 0, finalIndex = left;

            while(leftIndex < leftSize && rightIndex < rightSize)
            {
                if(leftVector.at(leftIndex)->get_annoNascita() <= rightVector.at(rightIndex)->get_annoNascita())
                    v[finalIndex++] = leftVector[leftIndex++];
                else 
                    v[finalIndex++] = rightVector[rightIndex++];
            }

            //eventuali elementi rimanenti
            while(leftIndex < leftSize)
                v[finalIndex++] = leftVector[leftIndex++];
            while(rightIndex < rightSize)
                v[finalIndex++] = rightVector[rightIndex++];
        }

        void mergeSort(vector<T>& v, int left, int right) const //left indica inizio intervallo, right indica fine intervallo
        {
            if(left >= right)
                return;
            int mid = left + (right - left) / 2; //inizio + (fine - inizio = dimensione totale) / 2 = mid = es. 12345 mid 6789 
            
            mergeSort(v,left,mid);
            mergeSort(v, mid+1, right);
            merge(v, left, mid, right);
        }

    public:
        BTS() : root(nullptr) {}
        
        BTS<T>* insertRoot(const T& nuovoDato)
        {
            if(!root)
                root = new Nodo<T>(nuovoDato);
            return this;
        }

        BTS<T>* insertChild(const string& nome_genitore, const T& nuovoDato) //inserimento a cascata
        {
            if(!root)
            {
                cerr << "Errore, devi prima creare la Radice, forse volevi usare [insertRoot(dato)] ?" << endl;
                exit(1);
            }   
            insertChildHelper(nome_genitore,nuovoDato);
            return this;
        }
        
        void printInOrder(Nodo<T>* node) const //sx -> root -> dx
        {
            if(!node)
                return;
            printInOrder(node->get_left());
            node->get_dato()->print();
            cout << endl;
            printInOrder(node->get_right());
        }

        void printPostOrder() const
        {
            printPostOrderHelper(root);
        }

        void printPreOrder(Nodo<T>* node) const 
        {
            if(!node)
                return;
            node->get_dato()->print();
            cout << endl;
            printPreOrder(node->get_left());
            printPreOrder(node->get_right());
        }

        void print() const 
        {
            printPreOrder(root);
            //printPostOrder();
            //posso scegliere se cambiare in: inorder, preorder o postorder, per il momento lo lascio così
        }

        void clearTree(Nodo<T>* node)
        {
            if(!node) 
                return;

            clearTree(node->get_left());
            clearTree(node->get_right());
            delete node->get_dato();
            delete node;
        }

        void findFatherOf(const string& nomeFiglio) const
        {
            //string res = "";
            //findFatherOf_Helper(root,nomeFiglio,res);
            string res = findFatherOf_Helper(root,nomeFiglio);
            if(res != "") 
                cout << "Il padre di " << nomeFiglio << " e': " << res << endl;
            else cout << "Padre di " << nomeFiglio << " non trovato." << endl;
        }

        int get_height() const
        {
            return get_heightHelper(root);
        }

        void printPerYear() const
        {
            printPerYear_helper(root);   
        }

        ~BTS()
        {
            cout << "Chiamato distruttore Albero Binario di Ricerca (BTS)." << endl;
            clearTree(root);
        }
};

#endif