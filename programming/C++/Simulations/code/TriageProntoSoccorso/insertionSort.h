#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <iostream>

template <typename T>
void sort(T* arr, int size)
{
    if(!arr)
    {
        std::cerr << "Puntatore ad array nullo." << std::endl;
        exit(1); 
    }

    //scorrimento
    for(int i=1; i < size; i++)
    {
        T key = arr[i];
        int j = i-1;
        //ordinamento 
        while(j >= 0 && arr[j] > key) //se key è più piccolo
        {
            arr[j+1] = arr[j]; //faccio spazio per nuovo elemento --> [5][2][1][3] -> [2,5][1][3] -> [1,2,5][3] -> [1,2,3,5]
            j--;
        }
        arr[j+1] = key; //posiziono nuovo elemento nella posizione corretta
    }
}


#endif