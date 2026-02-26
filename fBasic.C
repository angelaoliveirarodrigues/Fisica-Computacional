#include <iostream>

using namespace std;

void Dead(){ //doesn't have a return value
    cout<<"Eu caí de um penhasco!";
}

void Cabeça(){
    cout<<"Bati com a cabeça";
}

int main(){
    Dead();
    Cabeça();
    Dead();
    return 0;
}