/*
 * vector.h
 *
 *  Created on: 01/09/2020
 *      Author: Ruth Solis Velasco - A01703207
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "exception.h"
#include <sstream>

using namespace std;

template <class T>
class Vector {
private:
	unsigned int size;
	T	*data;

public:
	Vector(unsigned int) throw (RangeError,OutOfMemory);
	Vector(unsigned int, T&) throw (RangeError, OutOfMemory);
	Vector(const Vector<T>&) throw (OutOfMemory);
	~Vector();

	unsigned int length() const;
	unsigned int resize(unsigned int) throw (RangeError, OutOfMemory);
	unsigned int resize(unsigned int, T&) throw (RangeError, OutOfMemory);
	std::string toString() const;

	T& operator[](unsigned int) const throw (IndexOutOfBounds);
	void operator=(const Vector<T>&);
};

template <class T>
Vector<T>::Vector(unsigned int numberOfElements) throw (RangeError, OutOfMemory) {
	if(numberOfElements == 0)
		throw RangeError();
	size = numberOfElements;
	data = new T[size];
	if(data == 0)
		throw OutOfMemory();
}

template <class T>
Vector<T>::Vector(unsigned int numberOfElements, T &initialValue) throw (RangeError, OutOfMemory) {
	if(numberOfElements == 0)
		throw RangeError();
	size = numberOfElements;
	data = new T[size];

	if(data == 0)
		throw OutOfMemory();
   
	for(unsigned int i =0; i < size; i++){
		data[i] = initialValue;
	}
}

template <class T>
Vector<T>::Vector(const Vector<T> &source) throw (OutOfMemory) {
	size = source.size;
	data = new T[size];
	if(data == 0)
		throw OutOfMemory();
	for(unsigned int i=0; i<size; i++){
		data[i] = source.data[i];
	}
}

template <class T>
Vector<T>::~Vector() {
	delete [] data;
	data = 0;
	size = 0;
}

template <class T>
unsigned int Vector<T>::length() const {
	return size;
}

template <class T>
unsigned int Vector<T>::resize(unsigned int newSize) throw (RangeError, OutOfMemory) {
	if(newSize == 0)
		throw RangeError();
  /*
  * Solucion en clase
  */
//1. Crear un vector temporal del tamaño nuevo
  T *newData = new T[newSize];
	if (newData == 0) 
		throw OutOfMemory();
	

  //2. Copiar los valores del vector actual en el  vector temporal
  unsigned int limit = size;
  if (newSize <= size) {
    limit = newSize;
  } 
	
  for (unsigned int i = 0; i < limit; i++) {
			newData[i] = data[i];
	}

  //3. Borrar los datos del vector actual
  delete [] data;

  //4. Hacer que el vector actual apunte hacia el vector temporal
  data = newData;
  size = newSize;
	return size;


}

template <class T>
unsigned int Vector<T>::resize(unsigned int newSize, T &initValue) throw (RangeError, OutOfMemory) {
	if(newSize == 0){
		throw RangeError();}
  /*
  * Solucion en clase
  */
//1. Crear un vector temporal del tamaño nuevo
  T *newData = new T[newSize];
	if (newData == 0) {
		throw OutOfMemory();}
	

  //2. Copiar los valores del vector actual en el  vector temporal
  unsigned int limit = size;
  if (newSize >= size) {
    limit = newSize;
  } 
 unsigned int i=0;
  for (; i < 10; i++) {
	  if(i<size){
		  newData[i] = data[i];
	  }else{
		  newData[i] = initValue;
	  }
		//cout<<"INIT VALUE = "<<initValue<<endl;	
	}
 

  //3. Borrar los datos del vector actual
  delete [] data;

  //4. Hacer que el vector actual apunte hacia el vector temporal
  data = newData;
  size = newSize;
	return size;

}

template <class T>
std::string Vector<T>::toString() const {
	std::stringstream aux;

	aux << "[" << data[0];
	for (unsigned int i = 1; i < size; i++) {
		aux << ", " << data[i];
	}
	aux << "]";
	return aux.str();
}

template <class T>
T& Vector<T>::operator[] (unsigned int index) const throw (IndexOutOfBounds) {
	/*
	* Solucion obtenida de la carpeta de soluciones
	*/
	if(index < 0 || index >= size){
		throw 	IndexOutOfBounds();
	}
	return data[index];
}

template <class T>
void Vector<T>::operator=(const Vector<T> &right) {
	//cout<<"rightsize = "<<right.size<<endl;
	//cout<<"size = "<<size<<endl;
	if(right.size != size){
		resize(right.size);
	}
	
	for(int i =0; i<size; i++){
		data[i] = right.data[i];
	}

}

#endif /* VECTOR_H_ */