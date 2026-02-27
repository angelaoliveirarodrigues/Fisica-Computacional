#include "Functor.h"

class FuncT : public Functor {
    public:
        FuncT(string name);
        FuncT(string name, int valor);
        ~FuncT() =default;
        double operator() (double x);
    private:
    int valor;
};