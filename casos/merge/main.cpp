#include <iostream>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

void print_arr (int arr[], int size){
        printf("[");
    for (int i=0; i<size; i++){
        printf("%i,",arr[i]);
    }
    printf("]");
}

int* split(int *arr,int size)
{
    print_arr(arr, sizeof(arr)/sizeof(int));
    int mid2 = size/2; // 2
    int mid1 = size-mid2;// 3

    if(mid2!=0)
    {
        int *a;
        int *b;
        // copias temporales
        memcpy(a,arr,mid1*sizeof(int)); //primeros
        memcpy(b,arr+mid1,mid2*sizeof(int));

        print_arr(a, sizeof(a)/sizeof(int));
        print_arr(b, sizeof(b)/sizeof(int));
        //system("pause");

        a = split(a,mid1); // Has esto con papel amigo
        b = split(b,mid2); // Igual para esto

        //ALTO!! 
        //Aqui solo vamos a llegar cuando 
        // la ranita tenga dos hojitas para brincar
        // como minimo.
        int *arr_nuevo = (int*) malloc((mid1+mid2)*sizeof(int)); //regresar arr_nuevo
        int i=0, j=0, k=0; 
        for(;i<sizeof(a)/sizeof(int)  && j <sizeof(b)/sizeof(int); k++){
            if(a[i]< b[j]){
                arr_nuevo[k] = a[i];
               
                i++;
            }else{
                arr_nuevo[k] = b[j];

                j++;
            }
        }
        for(;k < mid1 + mid2;k++){
            if(i <sizeof(a)/sizeof(int)){
                arr_nuevo[k] = a[i];
                i++;
            }else{
                arr_nuevo[k] = b[j];
                j++;
            }
        }
        printf("\nMERGE DE ARREGLOS\n ");
        print_arr(arr, sizeof(arr)/sizeof(int));
     
        return arr_nuevo;
        /*
        int* rana   = &a[0];
        int* brinca = &b[0];
        int* nueva_base;
        int  cnt    = 0;

        while(cnt < size-1)
        {
            if((*rana) > (*brinca))
            {
                arr[cnt] = *brinca; // la rana no quiso brinca a este bloque y se cae
                brinca++;           // la rana brinca para al siguiente bloque
            }
            else
            {
                arr[cnt] =  *rana; // se cae donde estaba la rana
                nueva_base = brinca; //la ranita brinco tenemos nueva base 
                brinca = rana+1; // nueva posición donde la rana brincara
                rana   = nueva_base; // la rana brinca a un lugar seguro!!
            }
            cnt++; // se lleno el bloque que se cayo, vamos al siguiente bloque!!!
        }
        arr[cnt] = *rana; // la rana se fue a mimir
        */

    }
    else
    {
        return arr;
    }
}

int main(int argc, char const *argv[])
{
    int *arr = (int*) malloc((11)*sizeof(int));
    arr [0]= 35;
    arr [1]= 12;
    arr [2]= 5;
    arr [3]= 6;
    arr [4]= 9;
    arr [5]= 11;
    arr [6]= 0;
    arr [7]= 1;
    arr [8]= 2;
    arr [9]= 13;
    arr [10]= 34;
    
    arr = split(arr,sizeof(arr)/sizeof(int));

    print_arr(arr, sizeof(arr)/sizeof(int));

    return 0;
}