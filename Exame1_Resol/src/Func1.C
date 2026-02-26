#include "Func1.h"

#include <cmath>
#include <cstdio>

Func1::Func1(string name_) : Functor(name_) {;}
Func1::Func1(string name, int someValue) : Functor(name),  valor(someValue) {;}

double Func1::operator() (double x){
    return 0.5*exp(-x/100);
}

