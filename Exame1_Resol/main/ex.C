#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <array>

#include "Func1.h"
#include "IntegDeriv.h"
#include "ODEpoint.h"
//ROOT

#include "TH1F.h"
#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TGraph.h" 

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
    
    //Exercício 1, preencher a função com estes valores
    TCanvas canvas("canvas", "Graph", 800, 600);
    Func1 fI1("Exam01", 1); 
    array<string, 2> titles = {"I(t)", "time(s)"};
    fI1.Draw({0,400},200,titles);
    canvas.Update(); 
    canvas.SaveAs("grafico.pdf");

    //fazer a integração com o método midpoint
    IntegDeriv IG1(fI1);
    double Integral=0, RError=0;
    IG1.MidPoint(0,400,Integral,200, RError); // 200 slices
    cout << "alinea b: Integral=" << Integral << "+/-" << Integral*RError << endl;  


    ODEpoint P0(0, {0});
    vector< function<double(ODEpoint)> > F1 {
        [V,R,C](ODEpoint P)->double { return V/R*exp(-P.T()/(R*C)); }
    };
    ODEsolver S1(F1);
    auto vTRAP1 = S1.Trapezoidal(P0, 0.01, 500);
    TGraph G1(vTRAP1.size());
    for (size_t i = 0; i < vTRAP1.size(); ++i) {
        G1.SetPoint(i, vTRAP1[i].T(), vTRAP1[i].X()[0]);  
    }

    G1.SetTitle("ODE Solution (Trapezoidal Method)");
    G1.GetXaxis()->SetTitle("Time (s)");
    G1.GetYaxis()->SetTitle("Variable");

    TCanvas canvas2("canvas2", "Graph", 800, 600);
    G1.Draw("AL");
    canvas2.SaveAs("solution.pdf");


}