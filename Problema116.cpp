#include <iostream>


int quadrado(int num){
    if (num==2){
        return 2*2;
    }
    else{
         return quadrado (num-1)+1+2*(num-1);

    }

}

int main(){
    std::cout << quadrado(5);
}