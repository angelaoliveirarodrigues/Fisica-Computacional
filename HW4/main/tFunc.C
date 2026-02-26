#include "MyFunction.h"
#include "IntegDeriv.h"

#include <iostream>
using namespace std;

int main(){
    MyFunction F1("function");
    cout<<F1(1.5)<<endl;
    F1.Draw(0.5, 10., 100, "x","y");

    IntegDeriv integ(F1);
    double xi=0.5;
    double xf=10.;
    double integral= 0.0;
    double error=0.0;

    integ.TrapezoidalRule(xi,xf, integral, error);
    cout<<"Método do Trapézio:" << endl;
    cout<<"Integral: "<<integral<<endl;
    cout<<"Erro: "<<error<<endl;

    integ.simpsonRule(xi,xf,integral,error);
    cout<<"Método de Simpson:" << endl;
    cout<<"Integral: "<<integral<<endl;
    cout<<"Erro: "<<error<<endl;
    
}