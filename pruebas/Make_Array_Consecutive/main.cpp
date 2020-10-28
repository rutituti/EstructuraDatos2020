#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

void display(vector<int> a) {
   for(int i = 0; i < a.size(); ++i)
   cout << a[i] << " ";
}

int count_missing_numbers(vector<int> a){
    int diff=0, counter=0;
    for(int i = 0; (i+1) < a.size(); ++i){
        diff = a[i+1] - a[i];
       cout<<"\nDIFF: "<<diff<<endl;
        if(diff > 1){
            counter += (diff-1);
        }
    }
    return counter;
}

int main()
{
      vector<int> a = {6, 2, 3, 8};
    
   cout << "\n The array before sorting is : ";
   display(a);
    //cout<<"\nSIZE OF ARRAY= "<<size;
   sort(a.begin(),a.end());
   cout << "\n\n The array after sorting is : ";
   display(a);
   cout<<"\nMISSING NUMBERS = "<<count_missing_numbers(a);

    return 0;
}