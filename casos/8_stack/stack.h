#ifndef STACK_H_
#define STACK_H_

#include <string>
#include <sstream>
#include <list>
#include "exception.h"

using namespace std;
template <class T>
class Stack {
public:
	virtual void push(T) = 0;
	virtual T top() const throw (NoSuchElement) = 0;
	virtual void pop() throw (NoSuchElement) = 0;
	virtual bool empty() const = 0;
	virtual void clear() = 0;
	virtual std::string toString() const = 0;
};

template <class T>
class StackVector : public Stack<T> {
private:
	unsigned int next;
	unsigned int size;
	T 			 *data;

public:
	StackVector(unsigned int) throw (OutOfMemory);
	~StackVector();
	void push(T) throw (Overflow);
	T top() const throw (NoSuchElement);
	void pop() throw (NoSuchElement);
	bool empty() const;
	void clear();
	std::string toString() const;
};

template <class T>
StackVector<T>::StackVector(unsigned int sze) throw (OutOfMemory) {
	size = sze;
	data = new T[sze];
	if(data == 0){
		throw OutOfMemory();
	}
	next = 0;
}

template <class T>
StackVector<T>::~StackVector() {
	size = 0;
	next = 0;
	delete data;
	data = NULL;
}

template <class T>
void StackVector<T>::push(T val) throw (Overflow) {
	if(next == size){
		throw Overflow();
	}
	data[next++] = val;
}

template <class T>
T StackVector<T>::top() const throw (NoSuchElement) {
	if(empty()){
		throw NoSuchElement();
	}
	return data[next-1];
}

template <class T>
void StackVector<T>::pop() throw (NoSuchElement) {
	//cout<<"NEXT "<<next<<endl;
	if(empty()){
		throw NoSuchElement();
	}
	next--;
	//size--;
	
}

template <class T>
bool StackVector<T>::empty() const {
	if(next == 0){
		return true;
	}else{
		return false;
	}
}

template <class T>
void StackVector<T>::clear() {
	next = 0;
}

template <class T>
std::string StackVector<T>::toString() const {
	std::stringstream aux;

	aux << "[";
	if (next > 0) {
		aux << data[0];
		for (int i = 1; i < next; i++) {
			aux << ", " << data[i];
		}
	}
	aux << "]";
	return aux.str();
}

template <class T>
class StackList : public Stack<T> {
private:
	std::list<T> data;

public:
	void push(T);
	T top() const throw (NoSuchElement);
	void pop() throw (NoSuchElement);
	bool empty() const;
	void clear();
	std::string toString() const;
};

template <class T>
void StackList<T>::push(T val) {
	data.push_front(val);
}

template <class T>
T StackList<T>::top() const throw (NoSuchElement) {
	if(empty()){
		throw NoSuchElement();
	}
	return data.front();
}

template <class T>
void StackList<T>::pop() throw (NoSuchElement) {
	if(empty()){
		throw NoSuchElement();
	}
	data.pop_front();
}

template <class T>
bool StackList<T>::empty() const {
	if(data.empty()){
		return true;
	}else{
		return false;
	}
}

template <class T>
void StackList<T>::clear() {
	data.clear();
}

template <class T>
std::string StackList<T>::toString() const {
	std::stringstream aux;
	typename std::list<T>::const_iterator itr = data.begin();

	aux << "[";
	if (!data.empty()) {
		aux << (*itr);
		itr++;
		while (itr != data.end()) {
			aux << ", " << (*itr);
			itr++;
		}
	}
	aux << "]";
	return aux.str();
}
#endif /* STACK_H_ */
