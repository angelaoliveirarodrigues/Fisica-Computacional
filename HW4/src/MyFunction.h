#include "Functor.h"

class MyFunction : public Functor {
    public:
    MyFunction(string name);
    ~MyFunction() = default;
    double operator()(double x);
};
