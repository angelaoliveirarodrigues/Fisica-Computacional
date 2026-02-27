#include "funcT.h"

#include <cmath>
#include <cstdio>

FuncT::FuncT(string name_) : Functor(name_) {;}
FuncT::FuncT(string name, int someValue) : Functor(name),  valor(someValue) {;}

double FuncT::operator() (double x){ 
    x=x * M_PI / 180.0;//converter degrees em rad; a função sen só aceita rads
    return 1/(sqrt(1-(sin(x/2))*(sin(x/2))*sin(x)));
}