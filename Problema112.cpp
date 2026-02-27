#include <iostream>
#include <cmath>

float seno_quadrado(float int_num) {
   return pow(sin(int_num),2);
}

int main() {

    for (int i=0;i<3;i++) {
        std::cout << i+seno_quadrado(i);
    }
return 0;
}
