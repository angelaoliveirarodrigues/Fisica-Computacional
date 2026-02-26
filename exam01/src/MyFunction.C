#include "MyFunction.h"

#include <cmath>
#include <cstdio>

MyFunction::MyFunction(string name_) : Functor(name_) {}
double MyFunction::operator()(double t) {
    return 0.5*exp(-t/100);
}

