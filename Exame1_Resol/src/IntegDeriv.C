#include "IntegDeriv.h"
#include <cmath>
#include <iostream>
using namespace std;

IntegDeriv::IntegDeriv(Functor& func): F(func){;}


void IntegDeriv::TrapezoidalRule(double xi, double xf, double& Integral, int step, double& Error){
    //para vários intervalos

    double h=(xf-xi)/step; //calcular a largura de cada intervalo
    double sum;
    for(int i=1; i<step; i++){
       double x= xi +i*h;
       sum+= F(x); 
    }

    double yi= F(xi);
    double yf= F(xf);
    Integral= (h/2)*(yi+2*sum+yf);
    double derivative =0;
    double secondDerivative = fivepoint(xi, xf, derivative);
    Error=-(h*h*h)/12*secondDerivative;

}

void IntegDeriv::simpsonRule(double xi, double xf, double& Integral, double& Error){
    //para vários intervalos
    
    int step=100;
    double h=(xf-xi)/step;
    double yi= F(xi);
    double yf=F(xf);
    double sum1;
    double sum2;
    for(int i=1; i<step-1; i++){
        double x= (xi+i*h);
        if((i%2)==0){
            sum2+= F(x);
        }else{
            sum1+= F(x);
        }
    }
    Integral=h/3*(yi+sum1*4 +sum2*2+yf);
    double fourthDerivative=fivePointDiff(xi,xf, 4);
    Error=-((h * h * h * h) / 180) * fourthDerivative; 

}

void IntegDeriv::MidPoint(double xi, double xf, double& Integral, int step, double& Error){
    double h=(xf-xi)/step; //calcular a largura de cada intervalo
    double sum;
    for(int i=1; i<step; i++){
       double x= (xi+i*h)/2;
       sum+= h*F(x); 
    } 
    Integral=sum; 
    double secondDerivative=fivePointDiff(xi,xf,2);
    Error=((xf-xi)*(xf-xi)*(xf-xi)*secondDerivative)/(24*step*step);

}

double IntegDeriv::backwarddiff(double xi, double xf, double& Derivative){
    double h=xf-xi;
    Derivative=(F(xi)-F(xf))/h;
    return Derivative;
}

double IntegDeriv::forwarddiff(double xi, double xf, double& Derivative){
    double h=xf-xi;
    Derivative=(F(xf)-F(xi))/h;
    return Derivative;
}
double IntegDeriv::centraldiff(double xi, double xf, double& Derivative){
    double h=xf-xi;
    Derivative=(F(xf)-F(xi-h))/h;
    return Derivative;
}

//Apenas para ordem 2
double IntegDeriv::fivepoint(double xi, double xf, double& Derivative){
    double h=xf-xi;
    Derivative=(-F(xi-2*h)+16*F(xi-h)-30*F(xi)+16*F(xf)-F(xi+2*h))/(12*h*h);
    return Derivative;
}

//Apenas para ordem 2
double IntegDeriv::threepoint(double xi, double xf, double& Derivative){
    double h=xf-xi;
    Derivative= (F(xf)-2*F(xi)+F(xi-h))/(h*h);
    return Derivative;
}

double IntegDeriv::threePointDiff(double xi, double xf, int order) {
    double h= xf-xi;
    if (order == 1) {
        return (F(xf) - F(xi-h))/(2*h); // central diff
    } else if (order == 2) {
        return (F(xf)-2*F(xi) + F(xi-h)) / (h*h); // Diferença finita centrada para a segunda derivada
    } else if (order == 3) {
        return (F(xi - h)-2*F(xi) + F(xf)) / (h*h*h); // Diferença finita centrada para a terceira derivada
    } else {
        double result = 0.0;
        double factor = 1.0;
        for (int i = 1; i <= order; i++) {
            factor *= i;
            result += (factor*(F(xi+i*h)- F(xi-i*h))) / (pow(h,i+1));
        }
        return result;
    }
}

double IntegDeriv::fivePointDiff(double xi, double xf, int order) {
    double h=xf-xi;
    if (order == 1) {
        return (-F(xi+2*h) + 8 * F(xf) - 8 * F(xi-h) + F(xi-2*h)) / (12*h); // Diferença finita de 5 pontos para a primeira derivada
    } else if (order == 2) {
        return (-F(xi+2*h) + 16 * F(xf) - 30 * F(xi) + 16 * F(xi-h) - F(xi-2*h)) /(12*h*h); // Diferença finita de 5 pontos para a segunda derivada
    } else if (order == 3) {
        return (-F(xi+ 2*h) + 2 * F(xf) - 2 * F(xi - h) + F(xi - 2 * h)) / (2 * h * h * h); // Diferença finita de 5 pontos para a terceira derivada
    } else {
        double result = 0.0;
        double factor = 1.0;
        for (int i = 1; i <= order; i++) {
            factor *= i;
            result += (factor * (-F(xi + 2 * i * h) + 16 * F(xi + i * h) - 30 * F(xi) + 16 * F(xi - i * h) - F(xi - 2 * i * h))) / (12 * pow(h, i + 1));
        }
        return result;
    }
}