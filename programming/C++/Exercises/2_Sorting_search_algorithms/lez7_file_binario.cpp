/*

Continuazione lezione sui files --> file binario

*/

#include <iostream>
#include <fstream>
using namespace std;

int** createMatrix(const int&, const int&);
void printMatrix(int**, const int&, const int&);
void freeMatrix(int**,const int&, const int&);
void fillMatrix(int**, const int&, const int&);

void writeMatrixBinary(const string&, int**, const int&, const int&);
void readMatrixBinary(const string&);

int** createMatrix(const int& rows, const int& cols)
{
    int** matrix = new int*[rows];
    for(int i=0;i<rows;i++)
    {
        *(matrix+i) = new int[cols];
    }
    return matrix;
}

void fillMatrix(int** matrix, const int& rows, const int& cols)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            matrix[i][j] = i * cols + j + 1; //numeri da 1 a rows x cols 
        }
    }   
}


void printMatrix(int** matrix, const int& rows, const int& cols)
{
    cout << "\nStampa Matrice:" << endl;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cout << "[" << *(*(matrix + i) + j) << "]"; 
        }
        cout << endl;
    }
}

void freeMatrix(int** matrix,const int& rows, const int& cols)
{
    cout << "\nLiberazione memoria allocata alla matrice dinamica..." << endl;
    for(int i=0;i<rows;i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    cout << "...Memoria liberata con successo." << endl;
}


void writeMatrixBinary(const string& nomeFile, int** matrix, const int& rows, const int& cols)
{
    cout << "Scrittura matrice nel file binario..." << endl;
    ofstream file(nomeFile,ios::binary);
    if(!file)
    {
        cerr << "Errore durante apertura file scrittura binaria." << endl;
        exit(0);
    }

    //scrivo numero i righe e colonne, per sapere dimensioni a lettura.
    file.write(reinterpret_cast<const char*>(&rows), sizeof(int));
    file.write(reinterpret_cast<const char*>(&cols), sizeof(int));

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            file.write(reinterpret_cast<const char*>(&matrix[i][j]),sizeof(int));
        }
    }
    file.close();
    cout << "Scrittura effettuata con SUCCESSO." << endl;
}


void readMatrixBinary(const string& fileName)
{
    cout << "Procediamo a lettura file binario..." << endl;
    ifstream file(fileName);
    if(!file)
    {
        cerr << "Impossibile aprire file binario per la lettura." << endl;
        exit(0);
    }

    int rows, cols;

    file.read(reinterpret_cast<char*>(&rows), sizeof(int));
    file.read(reinterpret_cast<char*>(&cols), sizeof(int));

    //adesso sappiamo dimensioni matrice
    int** matrix = createMatrix(rows,cols);

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            file.read(reinterpret_cast<char*>(&matrix[i][j]),sizeof(int));
        }
    }

    printMatrix(matrix,rows,cols);

    file.close();
    cout << "Lettura file binario effettuata con successo!" << endl;
}



int main()
{
    int rows = 3, cols = 4;
    int **matrix = createMatrix(rows,cols);
    fillMatrix(matrix,rows,cols);
    printMatrix(matrix,rows,cols);

    string filename = "matrix.bin";
    writeMatrixBinary(filename,matrix,rows,cols);
    readMatrixBinary(filename);

    freeMatrix(matrix,rows,cols);
    return 0;
}