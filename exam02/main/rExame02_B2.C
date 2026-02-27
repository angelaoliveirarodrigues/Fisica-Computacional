#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <array>

#include "ODEpoint.h"
//ROOT

#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TPad.h"

using namespace std;

/*
int m=2;
int k=40;
double a=0.07;

x(t=0)=1;
v(t=0)=-0.5;

mx''=-kx -amgv/|v|


*/


int main(){
    int m=2;
    int k=40;
    double a=0.07;
    double g=9.81;

    ODEpoint P0(0, {1,-0.5}); // Ponto de acordo com as coordenadas iniciais

    vector<function<double(ODEpoint)>> F{
        [](ODEpoint P0)-> double{return P0.X()[1];},
        [m,k,a,g](ODEpoint P0)-> double{return (-k/m)*P0.X()[0] -a*g*P0.X()[1]/abs(P0.X()[1]);};
    };
    
    ODEsolver S1(F);
    double step=0.01;
    const vector<ODEpoint> V = solver.RK4(P0, step, 12);

    vector<double> vt, vx, vvel;

    for (const auto& point : V) {
        ODEpoint mutablePoint = point; // Criar uma cópia mutável
        vt.push_back(mutablePoint.T());
        vx.push_back(mutablePoint.X()[0]);
        vvel.push_back(mutablePoint.X()[1]);
        cout<<point<<endl;
    }

//ver os gráficos e as legendas
    TGraph gx(vt.size(), vt.data(), vx.data());
    TGraph gvel(vt.size(), vt.data(), vvel.data());

    gx.SetLineWidth(4);
    gx.SetLineColor(42);
    gx.GetXaxis()->SetTitle("time (sec)");
    //gy.GetYaxis()->SetTitle("height(m)");

    gvel.SetLineWidth(4);
    gvel.SetLineColor(42);
    gvel.GetXaxis()->SetTitle("time (sec)");
    //gvel.GetYaxis()->SetTitle("velocity(m)");

    //display
    TApplication A("A", 0, 0);
    TCanvas c("c", "", 1400, 800);
    c.Divide(2,1);
    c.cd(1);
    gPad->SetGrid();
    gx.SetTitle("theta");
    gx.Draw("AL");
    c.cd(2);
    gPad->SetGrid();
    gvel.SetTitle("omega");
    gvel.Draw("AL");
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();
    c.SaveAs("Exam02_B2_a.pdf")



    //Energia total do sistema
    /*
    Energia= 0.5*m*(P0.X()[1])*(P0.X()[1]) +0.5*k*(P0.x()[0])*(P0.x()[0]);

    Potência=Energia/intevalo de tempo;
    
    
    */


}