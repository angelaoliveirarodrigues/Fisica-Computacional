#ifndef __MYFUNCTION__
#define __MYFUNCTION__

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

Functor::~Functor(){
    if (c) delete c;
    printf("[%s] \n", __PRETTY_FUNCTION__);
}

double Functor::operator() (double x) {
    return 0;
}


void Functor::Draw(array<double,2> range, int npoints, array<string,2> titles){
    printf("[%s] range=[%.2f, %.2f] npoints=%d titles=[%s,%s]\n", __PRETTY_FUNCTION__, range[0], range[1], npoints, titles[0].c_str(), titles[1].c_str());

    vector <double> x(npoints), y(npoints);
    double h= (range[1]-range[0])/(npoints-1);
    for(int i = 0 ;i!= npoints;++i ){
        x[i]=range[0]+i*h;
        y[i]=this->operator()(x[i]);
    }
    TGraph *g=new TGraph(x.size(), x.data(), y.data());
    g->GetXaxis()->SetTitle(titles[0].data());
    g->GetYaxis()->SetTitle(titles[1].data());
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

#endif