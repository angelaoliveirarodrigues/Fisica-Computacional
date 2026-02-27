#include <iostream>
using namespace std;

void trocanums(int &x, int &y){
    int z=x;
    x=y;
    y=z;
}

int main(){
    int prim = 10;
    int sec=45;
    cout<< "Antes da troca: "<< "\n";
    cout<< prim <<sec<< "\n";

    trocanums(prim, sec);

    cout<<"Depois da troca: "<< "\n";
    cout<<prim<<sec<< "\n";
    return 0;
}