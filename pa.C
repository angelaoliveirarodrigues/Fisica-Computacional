#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

//ROOT

#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"

int main(){

double y0=200; // posição inicial em metros
double v0=25; //velocidade inicial em metros por segundo
double g=9.80665; //aceleração (metros por segundo^2)

//lambda function
auto y= [y0,v0,g](double t){ // auto porque é uma declaração genérica de uma função
    return y0+v0*t-0.5*g*t*t; // ou pow(t,2)
};  
cout<< "t(s)=0.5 h(m)= "<<y(0.5)<< endl;

//queremos registar os valores de altura
// vector< array<double,2>v;
// vector<pair<double,double> >v; queremos armazenar o tempo e a posição

vector< pair<double,double> >v;

for (double t=0; t<10. ; t+=0.01){
    v.push_back(make_pair(t,y(t)));  //permite  adicionar um elemento ao fim
}
cout << "vector size: "<< v.size() << endl;

for(auto e: v){
cout << "t(s)= "<< e.first <<"y(m)=" << e.second <<endl;
}

//time to ground
int idx;
for (int i=0; i<v.size()-1; i++){
    if (v[i].second*v[i+1].second <0){
        idx=i;
        break;
    }
  }

  cout<< "idx="<< idx<< endl;
  printf("t(s):[%6.3f,%6.3f] y(m):[%6.3f,%6.3f])\n", v[idx].first, v[idx+1].first,  v[idx].second, v[idx+1].second);

//aproximação linear para saber quando interseta (quando y=0)
double m_line=(v[idx].second- v[idx+1].second)/(v[idx].first- v[idx+1].first);
double b_line= v[idx].second- m_line*v[idx].first;
double t_crossing = -b_line/m_line; 

cout<< "t_crossing(s)= "<< t_crossing <<"y(t_crossing)=" <<y(t_crossing)<< endl;

//display 

//TF1

auto f =[g](double* x, double* par){
x[0]:t
par[0]:y0
par[1]:v0
 return par[0]+par[1]*x[0]-0.5*g*x[0]*x[0];
};
TF1 F("F", f, 0, 10, 2);
F.SetParameters(y0,v0);

TApplication A("A", 0, 0);
TCanvas c("canvas","canvas teste", 1000, 800 );
F.SetLineWidth(5);
F.SetLineColor(kBlue+1);
F.Draw();
c.Update();
gSystem->ProcessEvents();
c.WaitPrimitive();
}
