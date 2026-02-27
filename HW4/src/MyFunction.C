#include "MyFunction.h"

#include <cmath>
#include <cstdio>

MyFunction::MyFunction(string name_) : Functor(name_) {}
double MyFunction::operator()(double x) {
    return pow(x, 4.0) * log(x + sqrt(pow(x, 2.0) + 1));
}

