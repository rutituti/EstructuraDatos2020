/*
 * linkedlist.h
 *
 *  Created on: 07/09/2020
 *      Author: Ruth Solis Velasco
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>
#include <sstream>
#include "exception.h"
using namespace std;

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) {
	value = val;
	next = NULL;
}

template <class T>
Link<T>::Link(T val, Link* nxt) {
	value = val;
	next = nxt;
}

template <class T>
Link<T>::Link(const Link<T> &source){
	value = source.value;
	next = source.next;
}

template <class T>
class List {
public:
	List();
	List(const List<T>&) throw (OutOfMemory);
	~List();

	void addFirst(T) throw (OutOfMemory);
	void add(T) throw (OutOfMemory);
	T    getFirst() const throw (NoSuchElement);
	T    removeFirst() throw (NoSuchElement);
	int  length() const;
	T    get(int) const throw (IndexOutOfBounds, NoSuchElement);
	bool contains(T) const;
	bool empty() const;
	void clear();
	std::string toString() const;
	void operator= (const List&) throw (OutOfMemory);

	void addBefore(ListIterator<T>&, T) throw (IllegalAction, OutOfMemory);
	void addAfter(ListIterator<T>&, T) throw (IllegalAction, OutOfMemory);
	T    removeCurrent(ListIterator<T>&) throw (IllegalAction);

	bool set(int, T) throw (IndexOutOfBounds);
	int  indexOf(T) const;
	int  lastIndexOf(T) const;
	T    remove(int) throw (IndexOutOfBounds);
	bool removeFirstOcurrence(T);
	bool removeLastOcurrence(T);

private:
	Link<T> *head;
	int 	size;

	friend class ListIterator<T>;
};

template <class T>
List<T>::List(){
	head = NULL;
	size = 0;
}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
bool List<T>::empty() const {
	
	if(head == NULL){
		return true;
	}else{
		return false;
	}
}

template <class T>
int List<T>::length() const {
	
	return size;

	//SOLUCION EN CLASE
	/*
	int i = 0;
	if(head == NULL){
		return i;
	}

	//Solucion en clase
	Link<T> * ptr = head;
	i++;
	while(ptr -> next != NULL){
		ptr = ptr->next;
		i++;
	}
	cout<<"size = "<<i<<endl;
	return i;*/
}

template <class T>
bool List<T>::contains(T val) const {
	//Crear apuntador a head
	Link<T> *ptr = head;

	//Recorrer lista hasta encontrar el valor val
	while (ptr->next != NULL){

		if(ptr->value == val)
		//Devolver verdadero si lo encontró
		return true;
		ptr = ptr->next;
	}

	//Devolver falso si no se encontró el valor
	return false;
	
}

template <class T>
T List<T>::getFirst() const throw (NoSuchElement) {
	if(head == NULL)
		throw NoSuchElement();
	return head->value;
}

template <class T>
void List<T>::addFirst(T val) throw (OutOfMemory) {
	//SOLUCION EN CLASE

	//Crear nuevo nodo con el valor val

	Link<T> *nuevo = new Link<T>(val);

	if (nuevo ==NULL){
		throw OutOfMemory();
	}
	//Apuntar al siguiente del nuevo nodo a head
	nuevo->next = head;
	//Head apuntarlo al nuevo nodo
	head = nuevo;
	//Incrementar tamaño
	size++;
}

template <class T>
void List<T>::add(T val) throw (OutOfMemory) {
	//SOLUCION EN CLASE

	//Verificar si la lista esta vacia, agregar al pricipio
	if (empty()){
		addFirst(val);
		return;
	}

	//Crear un nuevo nodo
	Link<T> *nuevo = new Link<T>(val);

	if (nuevo ==NULL){
		throw OutOfMemory();
	}

	//Crear un apuntador actual
	Link<T> *actual = head;

	//Recorrer la lista hasta llegar al final
	while(actual->next != NULL){
		actual = actual->next;
	}

	//Apuntar actual al nuevo nodo
	actual->next = nuevo;

	//Aumentar el tamaño
	size++;
}

template <class T>
T List<T>::removeFirst() throw (NoSuchElement) {
	//Verificar si la lista esta vacia
	if(head == NULL){
		throw NoSuchElement();
	}

	//Crear apuntadores, uno que apunte al head y otro temporal
	Link<T> *actual = head, *temp;

	//Crear una variable temporal que guarde el valor del primer nodo a borrar
	int first_value=head->value;

	//Guardar el nodo siguiente del head en temp
	temp = actual->next;

	//Borrar actual
	delete actual;

	//Igualar el head al temp
	head = temp;

	//Decrementar el tamaño
	size--;

	//Regresar el valor del nodo borrado
	return first_value;
}

template <class T>
T List<T>::get(int index) const throw (IndexOutOfBounds, NoSuchElement) {
	//Verificar que el indice sea correcto
	if(index < 0 || index >= size){
		throw IndexOutOfBounds();
	}
	

	//Crear apuntador al head
	Link<T> *ptr = head;

	//Recorrer la lista hasta el indice indicado
	for (int i=0;i<index;i++){
		ptr = ptr->next;
		//cout<<"\nVALUE= "<<ptr->value<<endl;
	}
	
	//Regresar el valor requerido de la lista
	return ptr->value;
}

template <class T>
void List<T>::clear() {
	//Verificar si esta vacia la lista
	if (empty())
		return;
	
	//Crear apuntadores, uno que apunte a head y otro al siguiente de head
	Link<T> *actual = head, *temp;
	while (actual != NULL){
		temp=actual->next;
	//Borrar el apuntador acutal
		delete actual;
	//Guardar el valor de temp en actual
		actual=temp;
	}
	//Apuntar head a NULL y cambiar el tamaño a 0
	head = NULL;
	size = 0;
	

}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

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
List<T>::List(const List<T> &source) throw (OutOfMemory) {
		
	//SOLUCION EN CLASE

	//Validar si la lista esta vacia
	head = NULL;
	size = 0;
	if(source.empty()){
		return;
	}

	//Crear apuntador
	Link<T>*actual = source.head;
	//Recorrer la lista source
	while (actual !=NULL){
		//Por cada nodo que se visita, crear un nuevo nodo
		add(actual->value);
		actual = actual->next;
		
	}
}

template <class T>
void List<T>::operator=(const List<T> &source) throw (OutOfMemory) {
	//Borrar los datos de la lista a igualar
	clear();
	//Validar si la lista esta vacia
	if(source.empty()){
		return;
	}

	//Crear apuntador a head
	Link<T>*actual = source.head;

	//Recorrer la lista source
	while (actual !=NULL){

		//cout<<"VALORES =  "<<actual->value<<endl;
		
		//Por cada nodo que se visita, crear un nuevo nodo
		add(actual->value);
		actual = actual->next;
		
	}
}

template <class T>
void List<T>::addBefore(ListIterator<T> &itr, T val) throw (IllegalAction, OutOfMemory) {

}

template <class T>
void List<T>::addAfter(ListIterator<T> &itr, T val) throw (IllegalAction, OutOfMemory) {
	//Validar que el iterador es de la lista acutal
	if(this != itr.theList){
		throw IllegalAction();
	}

	//Al prinicipio
	if(itr.current == head){
		addFirst(val);
		itr.current = head;
		itr.previous = NULL;
		return;
	}	

	//Crear nuevo nodo
	Link<T> *nuevo = new Link<T> (val);

	//Validar que se pudo crear
	if(nuevo == 0){
		throw OutOfMemory();
	}

	//Al final
	if(itr.current == NULL){
		
		itr.previous->next = nuevo;
		itr.current = nuevo;
		size++;
		
	}else{
	//En medio
		nuevo->next = itr.current->next;
		itr.current->next =nuevo;
		size++;
	}
	

}

template <class T>
T List<T>::removeCurrent(ListIterator<T> &itr) throw (IllegalAction) {
	return 0;
}

template <class T>
bool List<T>::set(int index, T val) throw (IndexOutOfBounds) {
	return false;
}

template <class T>
int List<T>::indexOf(T val) const {
	return -1;
}

template <class T>
int List<T>::lastIndexOf(T val) const {
	return -1;
}

template <class T>
T List<T>::remove(int index) throw (IndexOutOfBounds) {
	return 0;
}

template <class T>
bool List<T>::removeFirstOcurrence(T val) {
	return false;
}

template <class T>
bool List<T>::removeLastOcurrence(T val) {
	return false;
}

template <class T>
class ListIterator {
public:
	ListIterator(List<T>*);
	ListIterator(const ListIterator<T>&);

	bool begin();
	bool end();
	T&   operator() () throw (NoSuchElement);
	bool operator++ ();
	void operator= (T) throw (NoSuchElement);

private:
	Link<T> *current;
	Link<T> *previous;
	List<T> *theList;

	friend class List<T>;
};

template <class T>
ListIterator<T>::ListIterator(List<T> *aList) : theList(aList) {
	begin();
}

template <class T>
ListIterator<T>::ListIterator(const ListIterator<T> &source) : theList(source.theList) {
	begin();
}

template <class T>
bool ListIterator<T>::begin() {
	previous = 0;
	current = theList->head;
	return (current != 0);
}

template <class T>
T& ListIterator<T>::operator() () throw (NoSuchElement) {
	if (current == 0) {
		throw NoSuchElement();
	}
	return current->value;
}

template <class T>
bool ListIterator<T>::end() {
	if (current == 0) {
		if (previous != 0) {
			current = previous->next;
		}
	}
	return (current == 0);
}

template <class T>
bool ListIterator<T>::operator++ () {
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
void ListIterator<T>::operator= (T val) throw (NoSuchElement) {
	if (current == 0) {
		throw NoSuchElement();
	}
	current->value = val;
}

#endif /* LINKEDLIST_H_ */
