#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include<sstream>
#include<cmath>
#include<array>


using namespace std;

//Declaração de funções
void ReadImage(string filename, vector<vector<int>>& M);
//void Frequencia(vector<vector<int>>& M, int WhiteValue, int nrows, int ncols);
array<float,3> calculo_estimadores(vector<vector<int>> M,int WhiteValue, int nrows,int ncols);


/*
void Open(ifstream F){
   if(!F.is_open()){
    cout<< "Não foi possível abrir o ficheiro."<<endl;
  } else {
    cout<<"Ficheiro aberto com sucesso."<<endl;
  };
}*/

int main(){
  ifstream F("glassware_noisy.ascii.pgm"); //Abrir o ficheiro 
  
  //Verificar se o ficheiro foi aberto; só efetua se aberto
  if (F.is_open()){

  cout<<"Ficheiro aberto com sucesso."<<endl;

  string line;
  getline(F,line); //ler a 1a linha
  getline(F,line);

  istringstream iss;  // a string line tem os dados que queremos ler
  iss.str(line);
  int nrows, ncols;
  iss>> ncols>> nrows; // semelhante ao cin mas para ficheiros- recuperámos o número de colunas e de linhas
  iss.clear();

  printf("Colunas %d \n",ncols);
  printf("Linhas %d \n",nrows);

  getline(F, line);
  iss.str(line);
  int WhiteValue;
  iss>> WhiteValue;
  iss.clear();

  printf("teste Whitevalue %d \n",WhiteValue);

  vector<vector<int>> M(nrows, vector<int>(ncols)); //Criar uma matrix M[nrows, ncols]
  vector<vector<int>> MInv(nrows, vector<int>(ncols)); //Cria uma matriz MInv (para inverter)
  vector<vector<int>> MRed(nrows, vector<int>(ncols)); //Cria uma matriz MRed (para a redução de ruído)

  ReadImage("glassware_noisy.ascii.pgm", M); //Ler a imagem

  F.close(); //Fechar a imagem

  vector<int> ColourFreq(WhiteValue +1);
   for(int i =0 ; i<nrows ; i++)
 {
    for(int j=0; j<ncols ; j++){
    ColourFreq[M[i][j]]++;
   }
 };

 /*vector <int> FreqRela(WhiteValue+1);
    for (int i=0;i<WhiteValue+1;i++){
        FreqRela[i]=ColourFreq[i]/(nrows*ncols);
    };
  */
int somatorio=0;
for (vector<int> m:M){
  for(int n:m){
    somatorio+=n;
  };
};
printf("O somatorio: %d \n",somatorio);
double media;
media=somatorio/(nrows*ncols);
printf("A média: %f\n", media);


    

 /*vector<float> FreqRela(WhiteValue+1);
 for(int i =0 ; i<WhiteValue+1; i++){
  FreqRela[i] = ColourFreq[i]/(ncols*nrows) * 100;
  printf("cor %d tem : %d elementos",i,ColourFreq[i]);
  printf("tem frequência relativa %f  \n",FreqRela[i]);
    };
 */
  

  }else{
     cout<< "Não foi possível abrir o ficheiro."<<endl;
  };

}


//Implementação das funções
//1.Para ler a imagem
void ReadImage(string filename, vector<vector<int>>& M){

  ifstream F(filename);
  string line;

  getline(F,line); 
  getline(F,line);
  getline(F,line);

  vector<int> lidos;  
  while(getline(F,line)){
  istringstream iss(line);
  int lido;
  while(iss>>lido){
    lidos.push_back(lido);
  };
  };
  for (int i=0; i<M.size(); i++){
    for (int j=0; j<M[i].size(); j++){
      M[i][j]=lidos[j+i*M[i].size()];
    }
  };
}






