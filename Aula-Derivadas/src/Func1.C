#include "Func1.h"

#include <cmath>
#include <cstdio>

Func1::Func1(string name_) : Functor(name_) {;}

double Func1::operator() (double x){
    return 1/x*cos(x);
}