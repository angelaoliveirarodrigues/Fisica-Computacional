/*
dy/dt= v= f0(t,y,v)
dv/dt= -g= f1(t,y,v)

ODEpoint:[t; (y,v)]

ODEsolver:
    -ODEsolver(vector<std::fuction<double(ODEpoints)>> )

*/

#include <vector>
#include <iostream>
#include <functional>

using namespace std;

#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TPad.h"

class ODEpoint{
    public:
    ODEpoint(): tempo(0){;}
    ODEpoint(double t0, vector<double> var_): tempo(t0), var(var_){;}

    const vector<double>& X() const;
    const double & T() const;

    friend ostream& operator << (ostream&, const ODEpoint&);

    private:
    double tempo;
    vector<double> var;
};

//Declarações
const vector<double>& ODEpoint::X() const{return var;}

const double& ODEpoint::T() const {return tempo;}

ostream& operator<<(ostream& s,const ODEpoint& P ){
    s<<"[t="<<P.tempo<<",(";

    for(int i=0; i<int(P.var.size())-1; i++){
        s<< P.var[i]<<",";
    }

    s<<P.var.back()<<")]";
    return s;
}
double deg2rad(double angle_deg) { //converter degrees em rad; a função sen só aceita rads
    return angle_deg * M_PI / 180.0;
}

int main(){
    const double g=9.80665;
    const int L=4 ;// metros
    const double m=0.5; //kg
    //init point
    ODEpoint P0(0,{200,150});
    cout<< P0<< endl;
    
    //functions
   vector<function<double(ODEpoint)>> F{
        [](ODEpoint P)-> double{return P.X()[1];},
        [g](ODEpoint P)-> double{return -g;}
    };

    //tests

    cout<<"F[0](P0)=" << F[0](P0) << endl;
    cout<<"F[1](P0)=" << F[1](P0) <<endl;

    //Solver system
    double step= 0.2; //em segundos, step=h
    double DT= 33; //Tempo final


    //Euler
   vector<ODEpoint> V1; 
    V1.push_back(P0);
    while(V1.back().T()<DT){ //Enquanto o tempo for menor que o tempo total
        ODEpoint Pcurrent= V1.back(); 
        V1.push_back(ODEpoint(V1.back().T()+step, {Pcurrent.X()[0]+ step*F[0](Pcurrent), Pcurrent.X()[1]+ step*F[1](Pcurrent)}));
    };

    //trapezoidal
    vector<ODEpoint> V2; 
    V2.push_back(P0);
    while(V2.back().T()<DT){ //Enquanto o tempo for menor que o tempo total
        ODEpoint Pcurrent= V2.back(); 
        ODEpoint Pnext(V2.back().T()+step, {Pcurrent.X()[0]+ step*F[0](Pcurrent), Pcurrent.X()[1]+ step*F[1](Pcurrent)});
        V2.push_back(ODEpoint(
            V2.back().T()+step, 
            {Pcurrent.X()[0]+ 0.5*step*(F[0](Pcurrent) +F[0](Pnext)), 
             Pcurrent.X()[1]+ 0.5*step*(F[1](Pcurrent)+ F[1](Pnext))}));
    };


    //TGraph
    vector<double> vt, vy, vvel;
    for (int i=0; i<V1.size(); i++){
        cout<<V1[i]<<endl;
        vt.push_back(V1[i].T());
        vy.push_back(V1[i].X()[0]);
        vvel.push_back(V1[i].X()[1]);
    };

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


    //trapezoidal
    vt.clear();
    vy.clear(); 
    
    for (int i=0; i<V2.size(); i++){
        vt.push_back(V2[i].T());
        vy.push_back(V2[i].X()[0]);
        vvel.push_back(V2[i].X()[1]);
    };

    TGraph gy2(vt.size(), vt.data(), vy.data());
    TGraph gvel2(vt.size(), vt.data(), vvel.data());

    gy2.SetLineWidth(4);
    gy2.SetLineColor(kRed+1);
    gy2.GetXaxis()->SetTitle("time (sec)");

    gvel2.SetLineWidth(4);
    gvel2.SetLineColor(kRed+1);
    gvel2.GetXaxis()->SetTitle("time (sec)");
    //gvel.GetYaxis()->SetTitle("velocity(m)"); 

    
    //display
    TApplication A("A", 0, 0);
    TCanvas c("c", "", 1400, 800);
    c.Divide(2,1);
    c.cd(1);
    gPad->SetGrid();
    gy.SetTitle("height (m)");
    gy.Draw("AL");
    gy2.Draw("L");
    c.cd(2);
    gPad->SetGrid();
    gvel.SetTitle("velocity (m/s)");
    gvel.Draw("AL");
    gvel2.Draw("L");
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();

}











