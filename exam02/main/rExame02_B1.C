#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <array>

#include "Functor.h"
#include "funcT.h"
#include "IntegDeriv.h"

using namespace std;

//ROOT

#include "TH1F.h"
#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TGraph.h" 


/*
Pendulo gravítico 

comprimento L=1
aceleração grav=9.81
T=a sqrt(L/g)*h()

*/


int main(){

    double pi=4*atan(1); //definir pi com arc-tangent

    double L=1; // comprimento em metros
    double g=9.81; // aceleração gravítica em m/s^2

    vector<double> vtheta0, vT;
    double step=0.01;
    
    double theta0=0;
    FuncT F0("h", theta0);
    IntegDeriv I0(F0);
    double Integral=0, Error=0;
    I0.TrapezoidalRule(0., pi/2, Integral, step, Error);
        
    //Armazenar os valores de theta0 e dos períodos
    vtheta0.push_back(theta0);
    double T=4*Integral*sqrt(L/g);
    vT.push_back(T);

    theta0=15;
    FuncT F15("h", theta0);
    IntegDeriv I1(F15);
    double Integral1=0, Error1=0;
    I1.TrapezoidalRule(0., pi/2, Integral1, step, Error1);
        
    //Armazenar o valor de theta0 e do período
    vtheta0.push_back(theta0);
    double T1=4*Integral1*sqrt(L/g);
    vT.push_back(T1);

    theta0=30;
    FuncT F30("h", theta0);
    IntegDeriv I2(F30);
    double Integral2=0, Error2=0;
    I2.TrapezoidalRule(0., pi/2, Integral2, step, Error2);
        
    //Armazenar o valor de theta0 e do período
    vtheta0.push_back(theta0);
    double T2=4*Integral2*sqrt(L/g);
    vT.push_back(T2);

    theta0=45;
    FuncT F45("h", theta0);
    IntegDeriv I3(F45);
    double Integral3=0, Error3=0;
    I3.TrapezoidalRule(0., pi/2, Integral3, step, Error3);
        
    //Armazenar o valor de theta0 e do período
    vtheta0.push_back(theta0);
    double T3=4*Integral3*sqrt(L/g);
    vT.push_back(T3);

    for(int i=0; i<4; i++){
        cout<<vT[0]<< "   "<< endl;
    }

    TGraph G1(vT.size());
    for (size_t i = 0; i < vT.size(); ++i) {
        G1.SetPoint(i, vtheta0[i], vT[i]);  
    }

    G1.SetTitle("ODE Solution (Trapezoidal Method)");
    G1.GetXaxis()->SetTitle("Tempo (s)");
    G1.GetYaxis()->SetTitle("Angulo");

    TCanvas canvas2("canvas2", "Graph", 800, 600);
    G1.Draw("AL");
    canvas2.SaveAs("Exame02_B2_a.pdf");

}