/*
 * sorts.h
 *
 *  Created on: 05/08/2015
 *      Author: pperezm
 */

#ifndef SORTS_H_
#define SORTS_H_

#include "exception.h"
#include <vector>
#include <list>

using namespace std;
template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
public:
	std::vector<T> bubbleSort(const std::vector<T>&);
	std::vector<T> selectionSort(const std::vector<T>&);
	std::vector<T> insertionSort(const std::vector<T>&);
	std::vector<T> shellSort(const std::vector<T>&);
	std::vector<T> mergeSort(const std::vector<T>&);

	std::vector<T> bucketSort(const std::vector<T>&);
	std::list<T>   mergeList(const std::list<T>&, const std::list<T>&);
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
std::vector<T> Sorts<T>::bubbleSort(const std::vector<T> &source) {
	std::vector<T> v(source);
		//cout <<"SIZE= "<<v.size()<<endl;
		for(unsigned int i = 0; i < v.size(); i++){
		
			for(unsigned int j = 0; (j+1) < v.size(); j++){
				
				if(v[j]> v[j+1]){
					swap(v,j,j+1);
					//cout <<"J= "<<j<<"| J+1= "<<j+1<<endl;
				}
			}
	}

	return v;
}

template <class T>
std::vector<T> Sorts<T>::selectionSort(const std::vector<T> &source) {
	std::vector<T> v(source);

	//Selecciona el menor y lo pone al inicio del arreglo
	for(unsigned int i = 0; i < v.size(); i++){
		int menor = i;
		for(unsigned int j = i+1; j < v.size(); j++){
			
			if(v[j]< v[menor]){
				menor = j;
			}
		}
		if(menor != i){
			swap(v,i,menor);
		}
	}

	return v;
}

template <class T>
std::vector<T> Sorts<T>::insertionSort(const std::vector<T> &source) {
	std::vector<T> v(source);
	int key, i, j;
	for(j=1; j < v.size(); j++){
		key = v[j];
		i = j-1;

		while(i >=0 && v[i] > key){
			v[i+1] = v[i];
			i--;
		}
		v[i+1] = key;
	}
	return v;
}

template <class T>
std::vector<T> Sorts<T>::shellSort(const std::vector<T> &source) {
	std::vector<T> v(source);
//GEEKS FOR GEEKS SOLUTION
// Start with a big gap, then reduce the gap 
    for (int gap = v.size() / 2; gap > 0; gap /= 2) { 
        // Do a gapped insertion sort for this gap size. 
        // The first gap elements arr[0..gap-1] are already in gapped order 
        // keep adding one more element until the entire array is 
        // gap sorted 
        for (int i = gap; i < v.size(); i += 1) { 
            // add arr[i] to the elements that have been gap sorted 
            // save arr[i] in temp and make a hole at position i 
            int temp = v[i]; 
  
            // shift earlier gap-sorted elements up until the correct 
            // location for arr[i] is found 
            int j; 
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap) 
                v[j] = v[j - gap]; 
  
            // put temp (the original arr[i]) in its correct location 
            v[j] = temp; 
        } 
    } 

	return v;
}

template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	//SOLUCION SOLUCIONARIO
	int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid &&j <= high) {//359   267 
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	//B[] 23567     9
	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
	//B[] 235679
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	//SOLUCION SOLUCIONARIO
	int mid;

	if ( (high - low) < 1 ) {
		return;
	}
	mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}

template <class T>
std::vector<T> Sorts<T>::mergeSort(const std::vector<T> &source) {
	//SOLUCION SOLUCIONARIO
	//SOLUCION PERSONAL EN CARPETA merge
	std::vector<T> v(source);
	std::vector<T> tmp(v.size());

	mergeSplit(v, tmp, 0, v.size() - 1);
	return v;
}

template <class T>
std::vector<T> Sorts<T>::bucketSort(const std::vector<T> &source) {
	typename  std::list<T>::iterator itr;
	std::vector<T> v;

	return v;
}

template <class T>
std::list<T> Sorts<T>::mergeList(const std::list<T> &lst1, const std::list<T> &lst2) {
	typename std::list<T>::const_iterator itr1, itr2;
	std::list<T> result;

	return result;
}

#endif /* SORTS_H_ */
