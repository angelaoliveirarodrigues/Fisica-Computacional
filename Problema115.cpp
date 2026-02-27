#include <iostream>
#include <limits>

int main(){
    std::cout << "Limites máximo e mínimo do int:" << std::numeric_limits<int>::max()
    << ";" << std::numeric_limits<int>::min();
}