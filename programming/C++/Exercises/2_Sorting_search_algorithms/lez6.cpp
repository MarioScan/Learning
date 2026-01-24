/*

    FILES

*/

#include <iostream>
#include <fstream>
#include <string>
//#include <cctype>
using namespace std;

int* readFile(const string&, int&);
void printArray(int*, const int&);
void writeFile(const string&,const int*, const int&);
void printText(const string&);
void ReWriteThisFile(const string&);

int* readFile(const string& nomeFile, int& dim)
{
    ifstream file(nomeFile);
    if(!file)
    {
        cerr << "Errore apertura file input." << endl;
        exit(0);
    }

    int num, contaNum = 0;
    while(file >> num) //vediamo quanti elementi ci sono (file >> num legge cosa c'è nel file)
        contaNum++;
    
    dim = contaNum;
    int* array = new int[dim];

    file.clear(); //ripristino file da eventuali errori scritti durante la lettura
    file.seekg(0,ios::beg); //porto il file a posizione 0, da beginning 

    // specifica la base: ios::beg, ios::cur, ios::end --> beginning, current, end  
    for(int i=0;i<dim;i++)
        file >> array[i];

    file.close();

    //dim modificato precedentemente
    return array;
}

void printArray(int* array, const int& dim)
{
    cout << "Stampa array:" << endl;
    for(int i=0;i<dim;i++)
    {
        cout << "array["<< i << "] = " << array[i] << endl;
    }
}

void writeFile(const string& fileOut, const int* array, const int& dim)
{
    //se vuoi aggiungere e non cancellare tutto prima della scrittura si può aprire in append --> ios::app (ofstream file(fileOut,ios::app);)
    ofstream file(fileOut);
    if(!file)
    {
        cerr << "Errore durante apertura file output" << endl;
        exit(0);
    }

    float media=0;
    file << "Array caricato da un altro file." << endl;
    for(int i=0;i<dim;i++)
    {
        file << array[i] << endl;
        media+=array[i];
    }
    media/=dim;
    file << "Media elementi array: " << media << endl;

    file.close();
}


void printText(const string& fileIn)
{
    ifstream file(fileIn);
    
    string riga;
    cout << "Lettura file di stringhe:" << endl;
    int c=1;
    while(getline(file,riga)) 
    {
        cout << "Riga n."<< c++ << ": " << riga << endl;
    }
}

void ReWriteThisFile(const string& fileInOut)
{
    cout << "Operazione di riscrittura file stringa" << endl;
    fstream file(fileInOut, ios::in | ios::out);
    if(!file)
    {
        cerr << "impossibile aprire file in input/output" << endl;
        exit(0);
    }

    //Preferibile aprire e poi chiudere il file per cambiare tra lettura e scrittura, ma si può anche fare così

    string buffer;
    size_t pos;
    int conta=0;
    while(file >> buffer)
    {
        bool check=false;
        for(int i=0;i<buffer.length();i++)
        {
            char c = tolower(buffer[i]);
            if(c == 'a' || c  == 'e' || c  == 'e' || c  == 'i' || c  == 'u')
            {
                check=true;
            }
        }
        if(check)
            conta++;
    }
    
    file.clear();       // Resetta gli errori (ad esempio eof)
    file.seekg(0);      // Torna all'inizio del file per leggere di nuovo
    file.seekp(0);      // Sposta anche il cursore di scrittura all'inizio

    char c;
    while(file.get(c))
    {
        char lowerC = tolower(c);
            if(lowerC == 'a' || lowerC  == 'e' || lowerC  == 'i' || lowerC  == 'o' || lowerC  == 'u')
            {
                pos = file.tellg(); //posizione dopo aver letto
                file.seekp(pos - 1); //andiamo a carattere con vocale letto
                file.put('X'); //inserisco modifica
                file.seekg(pos); //torno a lettura normale
            }
    }
    
    file.clear();       
    file.seekg(0,ios::end);
    file << "Parole con almeno una vocale: " << conta << endl;

    file.close();
}

int main()
{
    int n;
    string file = "in.txt";

    int* array = readFile(file,n);
    printArray(array,n);
    
    string fileOut = "out.txt";
    writeFile(fileOut,array,n);

    string fileStr = "string.txt";
    printText(fileStr);
    
    ReWriteThisFile(fileStr);

    return 0;
}