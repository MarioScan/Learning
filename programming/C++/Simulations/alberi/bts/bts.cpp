#include "bts.h"
#include <iostream>
using namespace std;

//Nodo

template <class T> Nodo<T>::Nodo() : dato(), left(nullptr), right(nullptr) {}
template <class T> Nodo<T>::Nodo(const T& data) : dato(data), left(nullptr), right(nullptr) {}
template <class T> Nodo<T>::~Nodo() {}

template <class T> const T& Nodo<T>::get_dato() const {return dato;}
template <class T> Nodo<T>* Nodo<T>::get_left() const {return left;}
template <class T> Nodo<T>* Nodo<T>::get_right() const {return right;}

template <class T> void Nodo<T>::set_left(Nodo<T>* newLeft) {left = newLeft;}
template <class T> void Nodo<T>::set_right(Nodo<T>* newRight) {right = newRight;}

//BTS

template <class T> BTS<T>::BTS() : root(nullptr) {}
template <class T> bool BTS<T>::isEmpty() { 
    return root==nullptr;
}
template <class T> void BTS<T>::insert(const T& nuovoDato){
    root = insertHelper(root, nuovoDato);
}
