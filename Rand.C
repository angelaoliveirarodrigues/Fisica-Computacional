#include <random>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ctime> // dá o número de segundos contado a partir
#include "TH1F.h"
#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TGraph.h"

using namespace std;

int main(){
    // random generators
    ranlux24 R1(time(0)), R2(time(0)+1); //definir seeds diferentes

    printf("time(0): %lu\n", time(0)); 

    printf("R1: ");
    for (int i=0; i<10; i++){printf("%lu ", R1()); }
    cout <<endl;
    printf("R2: ");
    for (int i=0; i<10; i++){printf("%lu ", R2()); }
    cout << endl;


    // distribuições
    uniform_real_distribution<double> D1(0.,10.); //Queremos obter números de 0 a 10
    printf("D1: ");
    for (int i=0; i<10; i++){printf("%f ", D1(R1));}
    cout<< endl;

    // STL: gerar 2000 números aleaórios

    array<double,4000> aR1; // criar um array com 2000 elementos
    // array <double, 4000> aR2;
    generate(aR1.begin(), aR1.begin()+2000, [& /* captura tudo; também podíamos usar &D1, &R1 */](){return D1(R1);}); //neste caso queremos gerar 2000 números(ou seja o mesmo número de elementos do vetor)
    // generate (aR2.begin(), aR2.begin +2000, [& /* captura tudo; também podíamos usar &D1, &R1 */](){return D1(R1);}))

    TH1F h("h", "", 20, 0., 10.);
    for (int i=0; i<2000; i++){
        h.Fill(aR1[i]);
    }

TGraph g1(1000, aR1.data(), aR1.data()+1000); //data vai indicar que é a partir da informação do array
g1.SetMarkerStyle(20);
g1.SetMarkerColor(42);

    //ROOT Display
    TApplication A("A", 0, 0);
    TCanvas c("canvas","canvas teste", 1000,800 ); 
    g1.Draw("AP");
    h.SetLineWidth(5);
    h.SetLineColor(kBlue+1);
     h.Draw();
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive(); 

    return 0; 

/*
    // SE QUISESSEMOS USAR 2 GRAFICOS
   //TGraph g[2]={(500, aR1.data(), aR1.data()+1000),(500, aR1.data()+500, aR1.data()+1500)} ; 
    //ou ainda 
    array<TGraph,2> g={(500, aR1.data(), aR1.data()+1000),(500, aR1.data()+500, aR1.data()+1500)};
    g[0].SetMarkerStyle(20);
    g[0].SetMarkerColor(42);
    g[1].SetMarkerStyle(24);
    g[0].SetMarkerColor(kBlue+1);

    //ROOT Display
    g[0].Draw("AP");
    g[1].Draw("P");
    gSystem->ProcessEvents(); */
     

    return 0;
}
