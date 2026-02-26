#include <iostream>
#include <cmath>
using namespace std;

int fact(int k){
    if (k>1){
        return k*fact(k-1);
    }else{
        return 1;
    }
}


int main(){
    int x;
    cout<<"Introduza um número: ";
    cin>>x;
    cout<< "O fatorial corresponde a:"<< fact(x);
    return 0;
}