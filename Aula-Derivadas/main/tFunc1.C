#include "Func1.h"

#include <iostream>
using namespace std;

int main(){
    Func1 F1("cos");
    cout<<F1(1.5)<<endl;
    F1.Draw({0.5, 10.}, 100, {"x","y"});
}