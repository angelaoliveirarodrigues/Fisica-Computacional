#include "Functor.h"

class Func1 : public Functor {
    public:
        Func1(string name);
        Func1(string name, int valor);
        ~Func1() =default;
        double operator() (double x);
    private:
    int valor;
};