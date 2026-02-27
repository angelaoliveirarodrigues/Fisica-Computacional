#include<Eigen/Dense> 
#include <iostream>
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TSystem.h"

using namespace std;
using namespace Eigen;

int main(){
    //randoms entre -1 e 1
    MatrixXd M1(10,4); //Matriz 10 por 4 de doubles dinâmica
    M1.setRandom();
    cout<<"M1 randoms [-1,1]:\n"<< M1<<endl;

   MatrixXd M2=MatrixXd::Random(25000,4);
    cout<<"M2 randoms [-1,1]:\n"<< M2<<endl;

    //Para gerar números noutra gama exemplo [5,10]
    /*
    [-1, 1], média é 0
    [5,10], média é 7,5
    Multiplicar [-1, 1] por 2.5 e somar 7.5
    
    */
  // M2:[5,10]
    MatrixXd M3=(2.5*M2.array()+7.5).matrix();
    cout<<"M3 randoms [5,10]:\n"<< M3<<endl;

#ifdef DISPLAY
    TApplication A("A", 0,0);
    TCanvas c("c", "", 1200,1200);
    TH1F h("h", "M3 randoms", 100, 0., 20.);
    for(int i=0; i<M3.rows(); i++){
        for(int j=0; j<M3.cols(); j++){
            h.Fill(M3(i,j));
        };
    };
    h.SetFillColor(42);
    h.Draw();
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();
#endif

//Recentrar em 0
RowVectorXd Vmean=M3.colwise().mean(); // fazer a média de cada coluna
cout<<"Column mean: \n" <<Vmean <<endl;
MatrixXd Mcentered = M3.rowwise()-Vmean;

#ifdef DISPLAY2
 TApplication A("A", 0,0);
    TCanvas c("c", "", 1200,1200);
    TH1F h("h", "M3 randoms", 100, -10., 10.);
    for(int i=0; i<M3.rows(); i++){
        for(int j=0; j<M3.cols(); j++){
            h.Fill(M3(i,j));
        };
    };
    h.SetFillColor(42);
    h.Draw();
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();
#endif

}