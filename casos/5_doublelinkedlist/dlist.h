/*
 * dlist.h
 *
 *  Created on: 10/08/2015
 *      Author: pperezm
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>
#include "exception.h"

template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
	friend class DListIterator<T>;
};

template <class T>
DLink<T>::DLink(T val) {
	value = val;
	previous = NULL;
	next = NULL;
}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) {
	value = val;
	previous = prev;
	next = nxt;
}

template <class T>
DLink<T>::DLink(const DLink<T> &source) {
	value = source.value;
	previous = source.previous;
	next = source.next;
}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&) throw (OutOfMemory);
	~DList();

	void addFirst(T) throw (OutOfMemory);
	void add(T) throw (OutOfMemory);
	T    getFirst() const throw (NoSuchElement);
	T    removeFirst() throw (NoSuchElement);
	T	 getLast() const throw (NoSuchElement);
	T    removeLast() const throw (NoSuchElement);
	int  length() const;
	T    get(int) const throw (IndexOutOfBounds, NoSuchElement);
	bool contains(T) const;
	bool empty() const;
	void clear();
	std::string toString() const;
	void operator= (const DList&) throw (OutOfMemory);

	void addBefore(DListIterator<T>&, T) throw (IllegalAction, OutOfMemory);
	void addAfter(DListIterator<T>&, T) throw (IllegalAction, OutOfMemory);
	T    removeCurrent(DListIterator<T>&) throw (IllegalAction);

	bool set(int, T) throw (IndexOutOfBounds);
	int  indexOf(T) const;
	int  lastIndexOf(T) const;
	T    remove(int) throw (IndexOutOfBounds);
	bool removeFirstOcurrence(T);
	bool removeLastOcurrence(T);

private:
	DLink<T> *head;
	DLink<T> *tail;
	int 	 size;

	friend class DListIterator<T>;
};

template <class T>
DList<T>::DList() {
	head = NULL;
	tail = NULL;
	size = 0;

}

template <class T>
DList<T>::~DList() {
	clear();
}

template <class T>
bool DList<T>::empty() const {
    
	if(head == NULL){
		return true;
	}
	return false;
}

template <class T>
int DList<T>::length() const {
	return size;
}

template <class T>
bool DList<T>::contains(T val) const {
	DLink<T> *p;

	p = head;
	while (p != 0) {
		if (p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}

template <class T>
T DList<T>::getFirst() const throw (NoSuchElement) {
	if (empty()) {
		throw NoSuchElement();
	}
	return head->value;
}

template <class T>
void DList<T>::addFirst(T val) throw (OutOfMemory) {
	//Crear el nuevo nodo
	DLink<T> *nuevo = new DLink<T>(val);
	//Verificar que hay memoria disponible
	if(nuevo == NULL){
		throw OutOfMemory();
	}
	//1. Si la lista esta vacia
		//Head = nuevo nodo
		//Tail = nuevo nodo
	if(empty()){
		head = nuevo;
		tail = nuevo;
	}else{
	
	//2. Si no esta vacia
		//Apuntar nuevo->next = head
		//head->previo = nuevo
		//head = nuevo
		nuevo->next = head;
    	head->previous = nuevo;
    	head = nuevo;
	}
	//Aumentar el tamaño
	size++;

}

template <class T>
void DList<T>::add(T val) throw (OutOfMemory) {
	//1. Si la lista esta vacia
	//Head = nuevo nodo
	//Tail = nuevo nodo
	if(empty()){
		addFirst(val);
	}
		//Crear el nuevo nodo
	DLink<T> *nuevo = new DLink<T>(val);
	//Verificar que hay memoria disponible
	if(nuevo == NULL){
		throw OutOfMemory();
	}
	
	tail->next = nuevo;
	nuevo->previous = tail;
	tail = nuevo;
	size++;

}

template <class T>
T DList<T>::removeFirst() throw (NoSuchElement) {
	//SOLUCION EN CLASE

	//Checar si la lista esta vacia
	if (empty())
	throw NoSuchElement();


	int NEW_CODE = 1;

	if(NEW_CODE){

		if (head == tail){
		  //Guardar el valor del nodo a borrar
	 	   T victima = head->value;
			delete head;
			delete tail;
			head = 0;
			tail = 0;
			size --;
			return victima;
		}
		//Crear apuntador al nodo a borrar
		DLink<T> * nodo_victima = head;

		//Head es igual a su siguiente
		head = head->next;

		//El siguiente del nodo a borrar es igual a NULL
		nodo_victima->next = NULL;

		//El previo de head es igual a NULL
		head->previous = NULL;

		//Reducir el tamaño
		size--;

		//Guardar el valor del nodo a borrar
	 	T victima = nodo_victima->value;

		//Borrar nodo anterior
		delete nodo_victima;

		//Regresar el valor del nodo borrado
		return victima;

		
	}else{

	/*
	OTRA IMPLEMENTACION
	*/

	if (head == tail){
		//Guardar el valor del nodo a borrar
	 	T victima = head->value;
		delete head;
		delete tail;
		head = 0;
		tail = 0;
		size --;
		return victima;
	}
	//El siguiente de head es igual a head
	head = head->next;

	//El siguiente del anterior de head es igual a NULL
	head->previous->next = NULL;

	//Guardar en una varibale temporal el previod e head
	T victima = head->previous->value;
	//Borrar el anterior de head
	delete head->previous;

	//Apuntar el anterior de head a NULL
	head->previous = NULL;

	//Reducir tamaño
	size--;

	return victima;
	}



}

template <class T>
T DList<T>::get(int index) const throw (IndexOutOfBounds, NoSuchElement) {
	int pos;
	DLink<T> *p;

	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	if (index == 0) {
		return getFirst();
	}

	p = head;
	pos = 0;
	while (pos != index) {
		p = p->next;
		pos++;
	}

	return p->value;
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
std::string DList<T>::toString() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
DList<T>::DList(const DList<T> &source) throw (OutOfMemory) {
	DLink<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} else {
		p = source.head;
		head = new DLink<T>(p->value);
		if (head == 0) {
			throw OutOfMemory();
		}
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			if (q->next == 0) {
				throw OutOfMemory();
			}
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
void DList<T>::operator=(const DList<T> &source) throw (OutOfMemory) {
	DLink<T> *p, *q;

	clear();
	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} else {
		p = source.head;
		head = new DLink<T>(p->value);
		if (head == 0) {
			throw OutOfMemory();
		}
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			if (q->next == 0) {
				throw OutOfMemory();
			}
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
void DList<T>::addBefore(DListIterator<T> &itr, T val) throw (IllegalAction, OutOfMemory) {
	
}

template <class T>
void DList<T>::addAfter(DListIterator<T> &itr, T val) throw (IllegalAction, OutOfMemory) {
}

template <class T>
T DList<T>::removeCurrent(DListIterator<T> &itr) throw (IllegalAction) {
	T val;
	
	return val;
}

template <class T>
bool DList<T>::set(int index, T val) throw (IndexOutOfBounds) {
	int pos;
	DLink<T> *p;

	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	p = head;
	pos = 0;
	while (pos != index) {
		p = p->next;
		pos++;
	}

	p->value = val;
	return true;
}

template <class T>
int DList<T>::indexOf(T val) const {
	int index;
	DLink<T> *p;

	index = 0;
	p = head;
	while (p != 0) {
		if (p->value == val) {
			return index;
		}
		index++;
		p = p->next;
	}
	return -1;
}

template <class T>
int DList<T>::lastIndexOf(T val) const {
}

template <class T>
T DList<T>::remove(int index) throw (IndexOutOfBounds) {
	int pos;
	T val;
	DLink<T> *p;

	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	if (index == 0) {
		return removeFirst();
	}

	p = head;
	pos = 0;
	while (pos != index) {
		p = p->next;
		pos++;
	}

	val = p->value;
	p->previous->next = p->next;
	if (p->next != 0) {
		p->next->previous = p->previous;
	}
	size--;

	delete p;

	return val;
}

template <class T>
bool DList<T>::removeFirstOcurrence(T val) {
	return false;
}

template <class T>
bool DList<T>::removeLastOcurrence(T val) {
	return false;
}

template <class T>
class DListIterator {
public:
	DListIterator(DList<T>*);
	DListIterator(const DListIterator<T>&);

	bool begin();
	bool end();
	T&   operator() () throw (NoSuchElement);
	bool operator++ ();
	void operator= (T) throw (NoSuchElement);

private:
	DLink<T> *current;
	DLink<T> *previous;
	DList<T> *theList;

	friend class DList<T>;
};

template <class T>
DListIterator<T>::DListIterator(DList<T> *aList) : theList(aList) {
	begin();
}

template <class T>
DListIterator<T>::DListIterator(const DListIterator<T> &source) : theList(source.theList) {
	begin();
}

template <class T>
bool DListIterator<T>::begin() {
	previous = 0;
	current = theList->head;
	return (current != 0);
}

template <class T>
T& DListIterator<T>::operator() () throw (NoSuchElement) {
	if (current == 0) {
		throw NoSuchElement();
	}
	return current->value;
}

template <class T>
bool DListIterator<T>::end() {
	if (current == 0) {
		if (previous != 0) {
			current = previous->next;
		}
	}
	return (current == 0);
}

template <class T>
bool DListIterator<T>::operator++ () {
	if (current == 0) {
		if (previous == 0) {
			current = theList->head;
		} else {
			current = previous->next;
		}
	} else {
		previous = current;
		current = current->next;
	}
	return (current != 0);
}

template <class T>
void DListIterator<T>::operator= (T val) throw (NoSuchElement) {
	if (current == 0) {
		throw NoSuchElement();
	}
	current->value = val;
}

#endif /* DLIST_H_ */
