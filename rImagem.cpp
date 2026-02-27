#include<fstream>
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<cmath>
#include <numeric>
#include "rFunctions.cpp"

using namespace std;
//Criador: João

int main(){
    //obter os conteúdos do ficheiro e armazená-los no objeto FI da classe ifstream
    ifstream FI("glassware_noisy.ascii.pgm");
    string line;
    //certificar que o ficheiro foi realmente aberto
    if (!FI.is_open()){
        printf("O ficheiro não foi aberto.\n");
    }
    //obter a primeira linha
    getline(FI, line);
    //obter a segunda linha e o número de linhas e colunas da matriz
    getline(FI, line);
    istringstream iss(line);
    double nrows, ncols;
    iss >> nrows >> ncols;
    iss.clear();
    //obter a terceira linha e o número máximo de colorização dos píxeis (o mínimo é 0)
    getline(FI,line);
    iss.str(line);
    int WhiteValue;
    iss >> WhiteValue;
    iss.clear();

    //criação da matriz e associação dos valores do ficheiro
    vector<vector <int>> M(nrows,vector<int>(ncols));
    ReadImage("glassware_noisy.ascii.pgm",M);
    FI.close();

    //criação do vetor frequência absoluta
    vector<int> ColourFreq(WhiteValue);
    for (vector<int> i:M){
        for (int j:i){
            ColourFreq[j]+=1;
    
        }
    }
    //criação do vetor frequência relativa
    vector <int> RelFreq(WhiteValue+1);
    for (int i=0;i<WhiteValue+1;i++){
        RelFreq[i]=ColourFreq[i]/(nrows*ncols);
    }
    cout << ColourFreq[0];
    //cálculo da média
    double sum;
    for (vector<int> i:M){
        for (int j:i){
            sum+=j;
        }
    }
    double mean=sum/(nrows*ncols);
    printf("The mean is: %f \n",mean);

    //cálculo da variância
    double variance=0;
    for(vector<int> i:M){
        for (int j: i){
            variance+=(j-mean)*(j-mean);
        }
    }
    variance=variance/(nrows*ncols-1);
    printf("Variance: %f \n", variance);
    double stdDev=sqrt(variance);
    printf("O valor do desvio padrão é: %f \n",stdDev);

    //criação da matriz a inverter e posterior inversão
    vector<vector<int>> IM=M;
    inverte("glassware_noisy.ascii.pgm",IM);

    //criação da matriz a retirar o ruído e eliminação do ruído
    vector<vector<int>> NM=M;
    noiseElim("glassware_noisy.ascii.pgm",NM);
    vector<int> vec={23,45,61};
    int sum2=accumulate(vec.begin(),vec.end(),0);
    cout << sum2;
}


