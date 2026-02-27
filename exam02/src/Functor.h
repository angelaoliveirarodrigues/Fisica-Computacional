#ifndef __FUNCTOR__
#define __FUNCTOR__

#include <string>
using namespace std;

#include "TCanvas.h"

class Functor{
    public:
        Functor(string name="");
        virtual ~Functor();

        virtual double operator () (double x);
        virtual void Draw(array<double,2> range, int npoints, array<string,2> titles);
    
    protected:
        string name;
        static TCanvas *c ;
};

#endif