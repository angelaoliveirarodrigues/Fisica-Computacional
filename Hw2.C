#include <iostream>
#include <array>
#include <vector>
#include <algorithm> //sort
#include <cmath> //pi, sqrt
/*
para o histograma
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TSystem.h" */

using namespace std;

//Struct cell
struct cell{
    array<float,3> center_coo {0,0,100}; //coordenadas centro
    float area; // área da célula
    float power; // potência incidente na célula
};

//Struct lightsource 
struct lightsource{
    array<float, 3> coo; //coordenadas da fonte
    float power=100.; //potência da fonte
};


class lightmap{
    public:

    //constructors
    lightmap() = default; // default
    lightmap(array<int,2> ncell, array<float,2> size); //número de células em x e y (ncell) e dimensões do plano (size)
    lightmap(lightsource S, array<int,2> ncell, array<float,2> size);
    //lightmap(const lightmap&); construtor cópia


    //Getters
    pair<int,int> GetCellIndex(float x, float y) const; // return célula
    pair<float,float> GetCellCoo(int index_x, int index_y) const; //return coordenadas centrais da célula

    double GetCellPower(int index_x, int index_y) const; // return power (Watts) da célula
    double GetCellPower(float x, float y) const; // return power (Watts) da célula

    int GetCellNx() const; // get number of cells along x
    int GetCellNy() const; // get number of cells along y

    const vector<vector<cell>>& GetCells() const;
    vector<vector<cell>>& GetCells(); // return cells grid

    array<float,3> GetNormal(); // return normal to plane

// Outras funções
    void AddLightSource(lightsource S); // adicionar fontes 
    const cell& GetMaxCell() const; // get cell with max power
    float distance_to_cell(array<float,3> SourceCoo, array<float,3> PointCoo); //get distance between the lightsource and the cell
    //float CellPower(const cell& C); para o 4


private:
    vector<vector<cell> > GRID; // cell grid
    array<float, 2> size; //dimensões do plano
    array<int,2> ncell; //número de células ao longo de x e y 
    vector<lightsource> LightSource; //vetor das lightsources
    lightsource LS; //lightsource
    array<float,2> coo_centre;

};


//Implementação

//Constructors
lightmap::lightmap(array<int,2> ncell, array<float,2> size){  
   this-> ncell=ncell;
   this-> size=size;
}

lightmap::lightmap(lightsource S, array<int,2> ncell, array<float,2> size){ 
    LS=S;
    this->ncell=ncell;
    this->size=size;
}

/*
lightmap::lightmap(const lightmap& L){
    ncell=L.ncell;
    size=L.size;
}*/



//Getters
pair<int,int> lightmap::GetCellIndex(float x, float y) const{
    int cell_x = static_cast<int>(x / (ncell[0]*size[0])); // Calculate the x index based on the x coordinate and cell size 
    int cell_y = static_cast<int>(y / (ncell[1]*size[1])); // Calculate the y index based on the y coordinate and cell size
    return make_pair(cell_x, cell_y);
}

/*
 pair<float,float> lightmap::GetCellCoo(int index_x, int index_y) const{
    float x = (index_x + 0.5f) * ncell[0]; // Calculate the x coordinate of the cell center
    float y = (index_y + 0.5f) * ncell[1]; // Calculate the y coordinate of the cell center
    return make_pair(x, y); // Return the pair of coordinates
} */

pair<float,float> lightmap::GetCellCoo(int index_x, int index_y) const{
    float x_centre=(index_x+size[0]/2)*ncell[0];
    float y_centre=(index_y+size[1]/2)*ncell[1];
    return make_pair(x_centre, y_centre);
}

double lightmap::GetCellPower(int index_x, int index_y) const{
    if (index_x >= 0 && index_x < GRID[0].size() && index_y >= 0 && index_y < GRID[1].size()){ //verificar se é possível aceder à célula
        float Power= GRID[index_x][index_y].power;
        return Power;
     }
} 

double lightmap::GetCellPower(float x, float y) const{
    return GRID[x][y].power;
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

//array<float,3> lightmap::GetNormal(){ }


//Outras funções

void lightmap::AddLightSource(lightsource S){
    LightSource.push_back(S);
}

const cell& lightmap::GetMaxCell() const{
    const cell* MaxCell=nullptr;
    float MaxPower=0;
    for(const auto& row: GRID){
        for(const cell& cell_atual:row){
            if (cell_atual.power> MaxPower){
                MaxPower=cell_atual.power;
                MaxCell=&cell_atual;
            }else{
                MaxPower=MaxPower;
            };
        };
    };
return *MaxCell;
}


float lightmap::distance_to_cell(array<float,3> SourceCoo, array<float,3> PointCoo){
    float dist_x= PointCoo[0]-SourceCoo[0];
    float dist_y= PointCoo[1]-SourceCoo[1];
    float dist_z= PointCoo[2]-SourceCoo[2];
    float distancia=sqrt(dist_x*dist_x+dist_y*dist_y+dist_z*dist_z);
    return distancia;
}




int main(){
    //1- Determina a Intensidade radiante da fonte
    lightmap LM; 
    lightsource LS;
    float SolidAng=4*M_PI;
    float IntRad=LS.power/(SolidAng);

    cout<<"A intensidade Radiante da fonte é: "<< IntRad <<endl;
/*
    //3- Cálculo da Irradiância

    //4- Potência média

    //5- Organizar as células num vetor por ordem crescente de luminosidade

    vector<cell> vGRID;
    sort(vGRID.begin(), vGRID.end(), [](const cell& a, const cell& b)->bool {
            return a.power<b.power;
        }); 




    //6-Obtenha num histograma bi-dimensional adaptado ao tamanho das células, a distribuição da potência incidente nas células


    //7-Calculem agora a potência total incidente no plano. Afixem o resultado no ecrã.



    //8-

*/
}






