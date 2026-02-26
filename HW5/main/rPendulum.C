#include <iostream>
#include "ODEpoint.h"
#include <string>
#include <functional>
#include <cmath>
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TPad.h"

/*
ODEpoint:[t; (x1,x2)]

1- 
    eq.movimento= d^2theta/dt^2 + sin(theta)g/L=0

 2-   dx1/dt= omega= f0(t,theta,omega)
      dx2/dt= -sin(theta)= f1(t,theta,omega)

*/ 


double deg2rad(double angle_deg) { //converter degrees em rad; a função sen só aceita rads
    return angle_deg * M_PI / 180.0;
}

int main(){

    const double g=9.80665; //m/s^2
    const int L=4 ;// metros
    const double m=0.5; //kg
 
    ODEpoint P(0,{200,150});
    cout<< P<< endl;
 
    //functions
    vector<function<double(ODEpoint)>> F{
    [](ODEpoint P)-> double{return P.X()[1];},
    [](ODEpoint P)-> double{return -sin(deg2rad(P.X()[0]));}
    };
   
    cout<<"F[0](P)=" << F[0](P) << endl;
    cout<<"F[1](P)=" << F[1](P) <<endl;

    double step= 0.2; //em segundos, step=h
    double DT= 33; //Tempo final
    vector<double> stepValues = {0.1, 0.01, 0.001}; // Step values
    ODEsolver solver(F);


    const vector<ODEpoint> V1 = solver.Euler(P, step, DT);
    //const vector<ODEpoint> V2 = solver.PredictorCorrector(P, step, DT);
    //const vector<ODEpoint> V3 = solver.LeapFrog(P, step, DT);
    //const vector<ODEpoint> V4 = solver.RK2(P, step, DT);
    //const vector<ODEpoint> V5 = solver.RK4(P, step, DT);

    vector<double> vt, vy, vvel;

    for (const auto& point : V1) {
        ODEpoint mutablePoint = point; // Criar uma cópia mutável
        vt.push_back(mutablePoint.T());
        vy.push_back(mutablePoint.X()[0]);
        vvel.push_back(mutablePoint.X()[1]);
        cout<<point<<endl;
    }

//ver os gráficos e as legendas
    TGraph gy(vt.size(), vt.data(), vy.data());
    TGraph gvel(vt.size(), vt.data(), vvel.data());

    gy.SetLineWidth(4);
    gy.SetLineColor(42);
    gy.GetXaxis()->SetTitle("time (sec)");
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
    gy.SetTitle("theta");
    gy.Draw("AL");
    c.cd(2);
    gPad->SetGrid();
    gvel.SetTitle("omega");
    gvel.Draw("AL");
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();
    //c.SaveAs("ode_euler.png");
    //c.SaveAs("ode_prcorr.png");
    //c.SaveAs("ode_leap.png");
    //c.SaveAs("RK2.png");
}




/* Para fazer 3 gráficos diferentes

vector<double> stepValues = {0.1, 0.01, 0.001}; //para vários valores de step

 TApplication A("A", 0, 0);

    for(const auto& step:stepValues){
        const vector<ODEpoint>& solution=solver.Euler(P,step, DT);
        vector<double> time;
        vector<double> xValues;
        vector<double> yValues;
        for(const auto& point : solution){
            ODEpoint mutablePoint = point; 
            time.push_back(mutablePoint.T());
            xValues.push_back(mutablePoint.X()[0]);
            yValues.push_back(mutablePoint.X()[1]);
        }
        TGraph gy(time.size(), time.data(), xValues.data());
        TGraph gvel(time.size(), time.data(), yValues.data());


        gy.SetLineWidth(4);
        gy.SetLineColor(42);
        gy.GetXaxis()->SetTitle("time (sec)");
        // gy.GetYaxis()->SetTitle("height(m)");

        gvel.SetLineWidth(4);
        gvel.SetLineColor(42);
        gvel.GetXaxis()->SetTitle("time (sec)");
        // gvel.GetYaxis()->SetTitle("velocity(m)");

        // Create a TCanvas to display the graphs
        TCanvas c("c", "", 1400, 800);
        c.Divide(2, 1);
        c.cd(1);
        gPad->SetGrid();
        gy.SetTitle("theta");
        gy.Draw("AL");
        c.cd(2);
        gPad->SetGrid();
        gvel.SetTitle("omega");
        gvel.Draw("AL");
        c.Update();
        gSystem->ProcessEvents();
        c.WaitPrimitive();
    }






//Para fazer no mesmo gráfico


   TMultiGraph mg;

    for(const auto& step:stepValues){
        const vector<ODEpoint>& solution=solver.Euler(P,step, DT);
        TGraph f;
        for(const auto& point : solution){
            ODEpoint mutablePoint = point;
            f.SetPoint(f.GetN(), mutablePoint.T(), mutablePoint.X()[0]);
        }
        mg.Add(&f);
    }

    //display
    TApplication A("A", 0, 0);
    TCanvas c("c", "", 1400, 800);
    gPad->SetGrid();
    mg.Draw("AL");
    mg.Draw("AL");
    mg.GetXaxis()->SetTitle("time (sec)");
    mg.GetYaxis()->SetTitle("theta");
    c.BuildLegend();
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();
*/