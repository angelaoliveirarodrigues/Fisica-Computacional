
#include "Functor.h"

#include "TApplication.h"
#include "TSystem.h"
#include "TGraph.h"
#include "TAxis.h"

#include <vector>
using namespace std;
#include <cstdio>

TCanvas* Functor::c = nullptr;

Functor::Functor(string name_){
    name=name_;
    if(!c) c=new TCanvas("c","", 1000, 1000);
    printf("[%s] \n", __PRETTY_FUNCTION__);
}

/*Functor::~Functor(){
    if (c) delete c;
    printf("[%s] \n", __PRETTY_FUNCTION__);
}*/

double Functor::operator() (double x) {
    return 0;
}

void Functor::Draw(double xi, double xf, int npoints, string xtitle, string ytitle){
    printf("[%s] xi=%.2f xf=%.2f npoints=%d xtitle=%s ytitle=%s\n", __PRETTY_FUNCTION__, xi, xf, npoints, xtitle.c_str(), ytitle.c_str());
    vector <double> x(npoints), y(npoints);
    double h= (xf-xi)/(npoints-1);
    for(int j = 0 ;j!= npoints;++j ){
        x[j]=xi+j*h;
        y[j]=this->operator()(x[j]);
    }
    TGraph *g=new TGraph(x.size(), x.data(), y.data());
    g->GetXaxis()->SetTitle(xtitle.data());
    g->GetYaxis()->SetTitle(ytitle.data());
    g->SetLineColor(kBlue-2);
    g->SetLineWidth(4);
    g->SetTitle(name.c_str());

    printf("TGraph done... numb of points= %d \n", g->GetN());

    //display 
    TApplication A("A", 0,0);
    TCanvas c(("c_"+name).c_str(), "", 1000, 1000);
    g->Draw("AL");
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();
}


