#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>


//Classes
#include "MyFunction.h"
#include "IntegDeriv.h"
#include "ODEpoint.h"

using namespace std;

//ROOT

#include "TH1F.h"
#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"


/*
V=10 V
R= 20 ohm
C=5F

I(t)=V/R exp(-t/RC)

*/

int main(){
    double V= 10; //V
    double R=20; // ohm
    double C=5; //F


    //Exercício a
    //lambda function para definir a expressão da intensidade da corrente

    auto I= [&](double t){ // auto porque queremos uma declaração genérica de uma função
        return (V/R)*exp(-t/(R*C));
        };
    
    vector< pair<double,double> >v; //conjunto de Intensidade da corrente, tempo

    for (double t=0; t<400. ; t+=0.01){
        v.push_back(make_pair(t,I(t)));  
    }

    auto f =[V,R,C](double* x, double* par){
    x[0]:t
    return (V/R)*exp(-x[0]/(R*C));
    };

    TF1 F("F", f, 0, 10, 2);
    F.SetParameters(I,t);

    TApplication A("A", 0, 0);
    TCanvas c("função","função", 1000, 800 );
    F.SetLineWidth(5);
    F.SetLineColor(kBlue+1);   
    F.Draw();
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();
    
    
    //Exercício b e c
    MyFunction F1("function");
    IntegDeriv integ(F1);
    double xi=0.;
    double xf=400.;
    double integral= 0.0;
    double error=0.0;

    integ.MidPoint(xi,xf,integral, error);
    cout<<"Integral: "<<integral<<endl;
    cout<<"Erro: "<<error<<endl;

    //Exercício d
    ODEpoint P(0,0);
    cout<< P<< endl;
    vector<function<double(ODEpoint)>> F{
    [V,R,C,t](ODEpoint P)-> double{return (V/R)*exp(-t/(R*C));},
    };

    double step= 0.01; //em segundos, step=h
    double DT= 500;

    const vector<ODEpoint> V1 = solver.PredictorCorrector(P, step, DT);


    vector<double> v1, v2;

    for (const auto& point : V1) {
        ODEpoint mutablePoint = point; // Criar uma cópia mutável
        v1.push_back(mutablePoint.T());
        v2.push_back(mutablePoint.X()[0]);
        cout<<point<<endl;
    }

    TGraph gt(v1.size(), v1.data(), v2.data());

    gt.SetLineWidth(4);
    gt.SetLineColor(42);
    gt.GetXaxis()->SetTitle("time (sec)");


    TApplication A("A", 0, 0);
    TCanvas c("c", "", 1400, 800);
    c.Divide(2,1);
    c.cd(1);
    gPad->SetGrid();
    gt.SetTitle("theta");
    gt.Draw("AL");
    c.cd(2);
    gPad->SetGrid();
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();
    c.SaveAs("Exam01_d.pdf");

}







