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
	//posicion mas pequeña = posicion
	unsigned int posicion_min = pos;
	//Si el valor de la posicion es mayor que la del hijo izquierdo
		
	if(data[pos] > data[left(pos)] && left (pos) <= count){
		//La posicion mas pequeñas será la izquierda
		posicion_min = left(pos);
	}
	//Comparar el valor de la posicion con valor del hijo izq
		//La posicion mas pequeña es la derecha
	if(data[posicion_min] > data[right(pos)] && right (pos) <= count){
		//La posicion mas pequeñas será la izquierda
		posicion_min = right(pos);
	}
	//Si la posicion mas pequeña es diferente de la posicion
	if(posicion_min != pos){
		//Intercambio entre la posicion y la posicion mas pequeña
		//heapdown (posicion mas pequeña)
		swap(pos,posicion_min);
		heapify(posicion_min);
	}

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
	while(pos > 0 && data[parent(pos)] > val){
		swap(pos,parent(pos));
		pos = parent(pos);
	}

}

template <class T>
T Heap<T>::remove() throw (NoSuchElement) {
	//Verificar que no esté vacio el heap
	if(empty()){
		throw NoSuchElement();
	}
	T aux  = data[0];

	//Pasar el ultimo elemento a la raiz
	count--;
	data[0] = data[count];
	
	//Rehep down
	heapify(0);
	
	return aux;
}

template <class T>
void Heap<T>::clear() {
	count = 0;
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
	
