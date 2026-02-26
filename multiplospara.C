#include <iostream>
#include <string>

using namespace std;

void myFunc( string pnome, int idade){
    cout<< pnome <<" Refsnes. "<< idade << " anos.\n";
}

int main(){
    myFunc("Liam", 3);
    myFunc("Jenny", 18);
    myFunc("Anja", 26);
    return 0;
}