#include <iostream>
using namespace std;
int quadrado(int x){
 if (x>2) {
        return quadrado(x-1) +1 +2*(x-1);
    } else {
        return 2*x;
    }
 }
int main (){
    cout<< quadrado;
    return 0;
}