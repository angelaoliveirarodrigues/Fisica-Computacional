#include <iostream>
#include <array>
#include <vector>
#include <algorithm> //sort
#include <cmath>
#include "lightmap.h"

using namespace std;

//indices das celulas começam em 0,0

//mudei o z para 10

float distance2cell(array<float,3> SourceCoo,array<float,3> PointCoo){

return(sqrt((SourceCoo[0]-PointCoo[0])*(SourceCoo[0]-PointCoo[0])+(SourceCoo[1]-PointCoo[1])*(SourceCoo[1]-PointCoo[1])+(SourceCoo[2]-PointCoo[2])*(SourceCoo[2]-PointCoo[2])));
}


//vetor normal ao map (0,0,-1)

float Irradiance(std::array<float,3>SourceCoo,array<float,3> PointCoo,float power){
    array<float,3> r;
    double r_norm, cos_a;
    r[0] = PointCoo[0]-SourceCoo[0];
    r[1] = PointCoo[1]-SourceCoo[1];
    r[2] = PointCoo[2]-SourceCoo[2];

    r_norm = sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);

    cos_a = r[2]/r_norm;
    //cout << r_norm << "norma \n";
    //cout << cos_a << "cos_a \n\n";


    
    return (power/(4*M_PI))*(cos_a/(r_norm*r_norm));
}



//Constructors
lightmap::lightmap(array<int,2> f_ncell, array<float,2> f_size){      //ncell numero de celulas em x e y    size -> tamanho do plano em x e y
float area,dim_x,dim_y;
ncell = f_ncell;
size = f_size;

dim_x = size[0]/ (float(ncell[0]));
dim_y = size[1]/(float(ncell[1]));

cell_size[0] = dim_x;
cell_size[1] = dim_y;
area = dim_y*dim_x;
cell leitura;
array<float,3> coo {dim_x/2,dim_y/2,10};

for(int i =0;i<ncell[0];i++){
    vector<cell> vec;
    coo[1]=dim_y/2;

    for(int j =0;j<ncell[1];j++) {
        leitura.center_coo = coo;
        coo[1]=coo[1]+dim_y;
        leitura.area=area;
        leitura.power = 0;
        vec.push_back(leitura);
    }
    GRID.push_back(vec);
    coo[0]=coo[0]+dim_x;
}

  
}

lightmap::lightmap(lightsource S, array<int,2>f_ncell, array<float,2>f_size){ 
float area,dim_x,dim_y;
ncell = f_ncell;
size = f_size;

dim_x = size[0]/ (float(ncell[0]));
dim_y = size[1]/(float(ncell[1]));
area = dim_y*dim_x;
cell leitura;
array<float,3> coo {dim_x/2,dim_y/2,10};

for(int i =0;i<ncell[0];i++){
    vector<cell> vec;
    coo[1]=dim_y/2;
    

    for(int j =0;j<ncell[1];j++) {
        leitura.center_coo = coo;
        coo[1]=coo[1]+dim_y;
        leitura.area=area;
        leitura.power = 0;
        vec.push_back(leitura);
    }

    GRID.push_back(vec);
    coo[0]=coo[0]+dim_x;
}
LightSource.push_back(S);
}

/*
lightmap::lightmap(const lightmap& L){
    ncell=L.ncell;
    size=L.size;
}*/

//getters

pair<int,int> lightmap::GetCellIndex(float x, float y) const{
    int cell_x = x/cell_size[0];
    int cell_y = y/cell_size[1];
    return make_pair(cell_x, cell_y);
}

pair<float,float> lightmap::GetCellCoo(int index_x, int index_y) const{
    return make_pair(GRID[index_x][index_y].center_coo[0], GRID[index_x][index_y].center_coo[1]); // Return the pair of coordinates
}

double lightmap::GetCellPower(int index_x, int index_y) const{
   return GRID[index_x][index_y].power;
} 

double lightmap::GetCellPower(float x, float y) const{
    int index_x = x/cell_size[0];
    int index_y = y/cell_size[1];

    return GRID[index_x][index_y].power;
}

int lightmap::GetCellNx() const{
    return ncell[0]; 
}

int lightmap::GetCellNy() const{
    return ncell[1]; 
}

const vector<vector<cell>>& lightmap:: GetCells() const{
   return GRID;  
}

vector<vector<cell>>& lightmap::GetCells(){
    return GRID;
}

//outras funcoes

void lightmap::AddLightSource(lightsource S){
    LightSource.push_back(S);
}

void lightmap::CellPower(){
    for(auto& e: LightSource){
        for(int i=0; i<ncell[0];i++){
            for(int j=0;j<ncell[0];j++){
                
                GRID[i][j].power = Irradiance(e.coo,GRID[i][j].center_coo,e.power)*GRID[i][j].area+GRID[i][j].power;
            }
        }

    }
    return;
}

vector<cell> lightmap::GetCellVector(){
    vector<cell> vec;
    for(int i =0;i<ncell[0];i++){
        for(int j=0;j<ncell[1];j++){
            vec.push_back(GRID[i][j]);
        }
    }

    return vec;
}

float lightmap::TotalPower(){
    float total=0;
    for(int i =0;i<ncell[0];i++){
        for(int j=0;j<ncell[1];j++){
           total = GRID[i][j].power + total;
        }
    }

return total;
}

