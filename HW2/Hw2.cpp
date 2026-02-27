#include <iostream>
#include <array>
#include <vector>
#include <algorithm> //sort
#include <cmath>
#include "lightmap.h"
#include<cstdio>


//root
#include "TH1F.h"
#include "TH2F.h"
#include "TApplication.h"
#include "TSystem.h"
#include"TCanvas.h"
#include "TGraph.h"
#include "TRootCanvas.h"
#include "TGraph.h"



//unidades em metros

using namespace std;


float mediana(vector<cell> &med){
    if (med.size() % 2 == 0)
    {
      return (med[med.size()/2 -1 ].power + med[med.size() / 2 ].power) / 2;
    }
    else 
    {
      return med[med.size()/2 ].power;
    }

}

int main(){
array<int,2> ncell{10,10};
array<float,2> map_size{1,1};
lightmap map(ncell,map_size);


lightsource source_a;

source_a.coo = {0.5,0.5,9.75};
source_a.power = 10000;

map.AddLightSource(source_a);

map.CellPower();

cout << map.GetCellPower(1,2) << " valor da energia numa cell \n";
cout << map.GetCellCoo(9,9).first <<" valor y " << map.GetCellCoo(9,9).second << "\n";

vector<cell> cell_vector_1;

cell_vector_1 = map.GetCellVector();

sort(cell_vector_1.begin(), cell_vector_1.end(),[](cell &a, cell &b){ return a.power<b.power; } );

cout << cell_vector_1[0].power << "1º valores e ultimo "<<cell_vector_1[cell_vector_1.size()-1].power << "\n";

float val;
val = mediana(cell_vector_1)/cell_vector_1[cell_vector_1.size()-1].power;

cout << "valor cociente " << val << "\n";

//root codigo

/*
TH1F h("h","valores de intensidade nas celulas", 20, 0, cell_vector_1[cell_vector_1.size()].power);

h.SetFillColor(42);
h.SetLineColor(kBlue+1);

for (int i=0; i<cell_vector_1.size(); i++) {
h.Fill(cell_vector_1[i].power);
}
// display ROOT
*/

TApplication A("A",0,0);

TCanvas c("c","",1000,800);

int Nx_m = map.GetCellNx();
int Ny_m = map.GetCellNx();

TH2F h1("h","Valores pow em cada celula",Nx_m,0,map_size[0],Ny_m,0,map_size[1]);

for (int i=0; i<cell_vector_1.size(); i++) {
h1.Fill(cell_vector_1[i].center_coo[0],cell_vector_1[i].center_coo[1],cell_vector_1[i].power);
}

h1.SetFillColor(42);
h1.SetLineColor(kBlue+1);
h1.Draw("LEGO");
c.Update();

c.SaveAs("lightmap_power.pdf");


vector<float> t_power;
vector<lightmap> map_vector;


//inicialização das fontes 

ncell={5,5};
map_size={1,1};
lightmap map_20(ncell,map_size);
map_vector.push_back(map_20);

ncell={8,8};
map_size={1,1};
lightmap map_125(ncell,map_size);
map_vector.push_back(map_125);


ncell={16,16};
map_size={1,1};
lightmap map_06(ncell,map_size);
map_vector.push_back(map_06);


ncell={25,25};
map_size={1,1};
lightmap map_04(ncell,map_size);
map_vector.push_back(map_04);


ncell={40,40};
map_size={1,1};
lightmap map_025(ncell,map_size);
map_vector.push_back(map_025);

ncell={50,50};
map_size={1,1};
lightmap map_02(ncell,map_size);
map_vector.push_back(map_02);

ncell={100,100};
map_size={1,1};
lightmap map_01(ncell,map_size);
map_vector.push_back(map_01);


vector<float> x_values = {0.20,0.125,0.0625,0.04,0.025,0.02,0.01};

for(auto& e:map_vector){
  e.AddLightSource(source_a);
  e.CellPower();
  t_power.push_back(e.TotalPower());
}

TCanvas b("b","",1000,800);

for(int i =0;i<t_power.size();i++){
  cout<< "valor power= "<< t_power[i];
  cout<< "  valor x= " <<x_values[i] << "\n";
}

printf("teste do size : %ld \n",x_values.size());

auto g = new TGraph(x_values.size(),x_values.data(),t_power.data());
g->SetTitle("Grafico;Area das celulas (cm); Potencia total no mapa(W)");

b.cd();

g->Draw();

b.Update();

b.SaveAs("lightmap_totalpower.pdf");

//gSystem->ProcessEvents();

b.WaitPrimitive();





return 0;

}