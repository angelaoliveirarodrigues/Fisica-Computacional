#include <random>
#include <fstream>
#include <array>
#include <algorithm>

using namespace std;

#include <cstdio>
#include <ctime>
#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TGraph.h"

int main() {
    printf("%lu \n", sizeof(array<float,1>));
    ofstream F("random.txt");
    printf("time (since 1st january 1970, in seconds): %ld \n", time(0));

// random generators 
    auto t = time(0);
    minstd_rand R1(t), R2(t+1111);
    F<< t << endl;

    printf("R1: ");
    for (int i=0; i<10; i++) {
        printf("%lu ",R1());
    }

    printf("\n");

    printf("R2: ");
    for (int i=0; i<10; i++) {
        printf("%lu ",R2());
    }
    printf("\n");

    F.close();


// uniform distribution
    uniform_real_distribution<float> D1(0.,10.), D2(0.,10.);
    array<float,10> tmp1;

    printf("D1: ");
    for (int i=0; i<10; i++) {
        auto r = D1(R1);
        printf("%.3f ",r);
        tmp1[i] = r;
    }

    printf("\n");

    {
    float sum = accumulate(tmp1.begin(), tmp1.end(), 0.0);
    float mean = sum/10;
    printf("média 1: %.3f \n",mean);
    }

    array<float,10> tmp2;
    printf("D2: ");
    for (int i=0; i<10; i++) {
        auto r = D2(R2);
        printf("%.3f ",r);
        tmp2[i] = r;
    } 

    printf("\n");
    {
    float sum = accumulate(tmp2.begin(), tmp2.end(), 0.0);
    float mean = sum/10;
    printf("média 2: %.3f \n",mean);
    }

// generate N random's
    const int N = 800000;
    array<float, N> aR1;
    generate(aR1.begin(), aR1.end(), [&D1, &R1](){ return D1(R1); } );
    const int Nelem = 25;
    const int Nsample = N/Nelem;

    // printf("sample means: ")

    array<float,Nsample> mean;
    for (int i=0; i<Nsample; i++) {
        auto b = aR1.begin() + i*Nelem;
        auto e = b + Nelem;
        double sum = accumulate(b, e, 0.0);
        mean[i] = sum/Nelem;
    // printf("%.3f ", mean[i]);
    }

    // printf("\n");

// histogram
    TH1F h("h","random means", 100, 0, 10);
    h.SetFillColor(42);
    h.SetLineColor(kBlue+1);
    for (int i=0; i<Nsample; i++) {
    h.Fill(mean[i]);
    }
// display ROOT

    TApplication A("A",0,0);
    TCanvas c("c","",1000,800);
    h.Draw();
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();

// grafico com numeros aleatorios
    c.Clear();
    TGraph g[10];
    array<float,500> x[10], y[10];
    for (int i=0; i<10; ++i) {
    auto b = aR1.begin()+i*1000;
    auto e = b+500;
    copy(b, e, x[i].begin());
    copy(b+500, e+500, y[i].begin());
//
    g[i] = TGraph(500, x[i].data(), y[i].data());
    g[i].SetMarkerStyle(20);
    g[i].SetMarkerColor(42+i);
//
    if (i==0)
        g[i].Draw("AP");
    else
        g[i].Draw("P");
    c.Update();
    gSystem->ProcessEvents();
    }
    c.WaitPrimitive();
}
