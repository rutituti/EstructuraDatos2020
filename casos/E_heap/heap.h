/*
 * heap.h
 *
 *  Created on: 20/10/2015
 *      Author: clase
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include "exception.h"
#include <iostream>

template <class T>
class Heap {
private:
	T *data;
	unsigned int size;
	unsigned int count;
	
	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);
	
public:
	Heap(unsigned int) throw (OutOfMemory);
	~Heap();
	bool empty() const;
	bool full() const;
	void add(T) throw (Overflow);
	T remove() throw (NoSuchElement);
	void clear();
	std::string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int sze) throw (OutOfMemory) {
	size = sze;
	count = 0;
	data = new T[size];
	if(data == NULL)
	throw OutOfMemory();
}

template <class T>
Heap<T>::~Heap() {
	delete [] data;
	data = NULL;
	size = 0;
	count = 0;
}

template <class T>
bool Heap<T>::empty() const {
	if(count == 0){
		return true;
	}else
	{
		return false;
	}
	
}

template <class T>
bool Heap<T>::full() const {
	if(count == size){
		return true;
	}else{
		return false;
	}
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos-1)/2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return (2*pos)+1;
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return (2*pos)+2;
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
}

template <class T>
void Heap<T>::add(T val) throw (Overflow) {
	//Revisar si hay espacio disponible
	if(full()){
		throw Overflow();
	}
	//Obtener la siguiente posicion disponible
	int pos = count;
	//Guardar valor
	data[pos] = val;
	//Auementar el count
	count++;
	
	//REHEAP
	//Si el padre es mas grande, hacer swap
	if(pos > 0 && data[parent(pos)] > val){
		swap(data[pos],data[parent(pos)]);
	}

}

template <class T>
T Heap<T>::remove() throw (NoSuchElement) {
	T aux;
	
	return aux;
}

template <class T>
void Heap<T>::clear() {
}
	

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	
	aux << "[";
	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		}
		aux << data[i];
	}
	aux << "]";
	return aux.str();
}
#endif /* HASH_H_ */
	
