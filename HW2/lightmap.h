#include<vector>
#include<array>
#include<utility>

#ifndef __LIGHTMAP__
#define __LIGHTMAP__

using namespace std;

//mudei o z das cells default para 10

struct lightsource {
std::array<float,3> coo; // source coordinates (cm)
float power; // source power (W)
};

struct cell {
std::array<float,3> center_coo {0,0,10}; 
float area; // cell area (cmˆ2)
float power; // cell incident power (W)
};

//funcoes para o calculo da energia nas celulas

float distance2cell(std::array<float,3> SourceCoo,std::array<float,3> PointCoo);

float Irradiance(std::array<float,3> PointCoo);



class lightmap{
    public:

    //constructors
    lightmap() = default; // default
    lightmap(array<int,2> f_ncell, array<float,2> f_size); //número de células em x e y (ncell) e dimensões do plano (size)
    lightmap(lightsource S, array<int,2> f_ncell, array<float,2> f_size);
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

    void CellPower();
    vector<cell> GetCellVector();

    float TotalPower();

    //const cell& GetMaxCell() const; // get cell with max power
    //float distance_to_cell(array<float,3> SourceCoo, array<float,3> PointCoo); //get distance between the lightsource and the cell
    //float CellPower(const cell& C); para o 4


private:
    vector<vector<cell>> GRID; // cell grid
    array<float, 2> size; //dimensões do plano
    array<int,2> ncell; //número de células ao longo de x e y 
    vector<lightsource> LightSource; //vetor das lightsources
    lightsource LS; //lightsource
    array<float,2> cell_size;

};

#endif