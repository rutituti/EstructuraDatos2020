/*
 * recursion.h
 *
 *  Created on: 10/09/2015
 *      Author: pperezm
 */

#ifndef RECURSION_H_
#define RECURSION_H_

#include "exception.h"
#include <iostream>
using namespace std;

long sum_seq(int n) {
  long resultado = 0;
  long i = 1;

  while (i <= n) {
    resultado = resultado + i;
    i++;
  }
  
	return resultado;

}

long sum_rec(int n) {
	if (n ==1){
		return 1;
	}

	return n + sum_rec(n-1);
	/*
	2 + sum_rec(1) => 1
	3 + sum_rec(2)
	      ^
	3 + 2 + sum_rec(1) => 1
	*/

}

long fact_seq(int n) {
	long resultado = 1;

	for(int i = 1; i <=n; i++){
		resultado = resultado *i;
	}
	return resultado;

}

long fact_rec(int n) {
	if (n == 0){
		return 1;
	}

	return n * fact_rec(n-1);
}

long fib_seq(int n) {
	long resultado = 1;
	long anterior1 = resultado;
	long anterior2 = resultado;

	for(int i = 3; i<= n; i++){
		resultado = anterior1 + anterior2;
		anterior2 = anterior1;
		anterior1 = resultado;
		//cout<<"Resultado ="<<resultado<<endl;
	}
	return resultado;
}

long fib_rec(int n) {
	if (n == 1 || n == 2){
		return 1;
	}
	return fib_rec(n-1) + fib_rec(n-2);
	 // fib_rec(5)
     // fib_rec(4) + fib_rec(3)
     // fib_rec(3) + fib_rec(2) + fib_rec(2) + fib_rec (1)
     // fib_rec(2) + fib_rec(1) + 1 + 1 + 1
    //     1       +     1      + 1 + 1 + 1 = 5   
}

//Greatest common divisor
long gcd_seq(long a, long b) {
	int aux;

	while (b != 0) {
		aux = b;
		b = a % b;
		a = aux;
	}
	return a;
}

long gcd_rec(long a, long b) {
	int aux = b;
	b = a % b;
	a = aux;
	if (b == 0){
		return a;
	}else{
		return gcd_rec(a,b);
	}
	
}

//Buscar
bool find_seq(int arr[], int size, int val) {
	for(int i=0; i<size ;i++){
		if(arr[i] == val){
			return true;
		}
	}
	return false;
}

bool find_rec(int arr[], int low, int high, int val) {
	if(low == high)
		return false;
	if(arr[high] == val){
		return true;
	}else{
		return find_rec(arr,low,high-1, val);
	}
}
//Otener el numero mayor
int max_seq(int arr[], int size) {
	int max = 0;
	for(int i=0; i<size; i++){
		if(arr[i] > max){
			max = arr[i];
		}
	}
	return max;
}

int max_rec(int arr[], int low, int high) {
	return 0;
}

//Rregresar el valor de la localidad de un arreglo de mayor valor
int unimodal_seq(int arr[], int size) {
	return 0;
}
//Funcion auxiliar para recursion de unimodal_rec
int unimodal_rec(int arr[], int low, int high) {
	return 0;
}

int unimodal_rec(int arr[], int size) {
	return 0;
}

//Busqueda binaria
int bs_seq(int arr[], int size, int val) {
	int low = 0;
	int high = size - 1;
	int mid = (high + low) / 2;
	
	while (low < high){
		mid = (high + low) / 2;
		if (val == arr[mid]){
			return mid;
		}
		
		if(val < arr[mid]){
			high = mid -1;
		}else{
			low = mid + 1;
		}
	}

	return low;
}

//Fucnion auxiliar para hacer una busqueda binaria
//Esta funcion es necesaria para realizar lar ecursion
int bs_aux(int arr[], int low, int high, int val) {
	if(low > high){
		return low;
	}
	int mid = (high + low) / 2;

	if(val == arr[mid]){
		return mid;
	}

	if(val < arr[mid]){
		return bs_aux(arr,low,mid-1,val);
	}else{
		return bs_aux(arr,mid+1,high,val);
	}
}

int bs_rec(int arr[], int size, int val) {
	return bs_aux(arr,0,size-1,val);
}
#endif /* RECURSION_H_ */
