#ifndef __FUNC1__
#define __FUNC1__

#include "Functor.h"


class Func1 : public Functor {

public:
    Func1(string name); 
    ~Func1() = default;


    double operator() (double x);

};


#endif