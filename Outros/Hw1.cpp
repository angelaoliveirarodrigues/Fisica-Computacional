#include<fstream>
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<cmath>
#include<array>
#include <algorithm>


void ReadImage(std::string filename, std::vector<std::vector<int>>& M);
std::vector<std::vector<int>> inverter(std::string filename, std::vector<std::vector<int>> M,int max, int nrows, int ncols);
std::vector<std::vector<int>> ruido1(std::string filename, std::vector<std::vector<int>> M,int max, int nrows, int ncols);
void ruido2(std::string filename, std::vector<std::vector<int>> M, int max, int nrows, int ncols);
int reduzir_ruido(std::vector<std::vector<int>>& M, int i ,int j);
std::array<float,3> calculo_estimadores(std::vector<std::vector<int>> M,int WhiteValue, int nrows,int ncols);

int main()
{
// 1. read image configuration (3 first lines)
//... abrir o ficheiro da imagem
std::ifstream FI("glassware_noisy.ascii.pgm");
std::string line,teste;

if (!FI.is_open()){
    printf("erro na abertura do ficheiro \n");
    return 0;
}

//... ler a primeira linha
std::getline(FI,line);
std::getline(FI,line);

//... ler a 2a linha e recuperar o numero de linhas e colunas*/
std::stringstream iss;
iss.str(line);
int nrows=1, ncols=1;
iss >> ncols >> nrows;

printf("teste peek %d \n",iss.peek());
iss.clear();


//... ler a 3a linha e recuperar o codigo maximo de 

printf("teste das col %d \n",ncols);

std::getline(FI, line);

iss.str(line);

int WhiteValue;

iss >> WhiteValue;
iss.clear();

printf("teste whitevalue :%d \n",WhiteValue);
// 2. creation of matrix M [nrows, ncols] da que vai ser invertida da ruido reduzido

std::vector<std::vector<int>> M(nrows, std::vector<int>(ncols));
std::vector<std::vector<int>> MI(nrows, std::vector<int>(ncols));
std::vector<std::vector<int>> MR(nrows, std::vector<int>(ncols));


// 3. read image to matrix

ReadImage("glassware_noisy.ascii.pgm",M);

//printf("teste valor m : %d \n",M[0][0]);


FI.close();

//abrir ficheiro para inverter e inverter

MI = inverter("glassware_noisy_inverted.ascii.pgm",M,WhiteValue,nrows,ncols);


//reduzir ruido

MR=ruido1("glassware_reduced_noise.ascii.pgm",M,WhiteValue,nrows,ncols);

//reduzir ruido tendo em conta o pixel central

ruido2("glassware_box_blur.ascii.pgm",M,WhiteValue,nrows,ncols);

//Calcular momentos

printf("Matriz normal \n");
calculo_estimadores(M,WhiteValue,nrows,ncols);
//printf("Matriz reduzida\n");
//calculo_estimadores(MR,WhiteValue,nrows,ncols);
//printf("Matriz invertida \n");
//calculo_estimadores(MI,WhiteValue,nrows,ncols);


return 0;
}



void ReadImage(std::string filename, std::vector<std::vector<int>>& M){
 
 int i=0,j;

 std::string line;
 std::ifstream F1 (filename);
 std::getline(F1, line);

 std::getline(F1,line);
 std::istringstream iss(line);
 int nrows, ncols;
 iss >> ncols >> nrows;
 iss.clear();

 std::getline(F1,filename);


 printf("teste cols func %d \n",ncols);
  
   while(i<nrows)
  {
    j=0;
    //mandar reiniciar a stream quando só falta o char lf ou eof
    if(i == 0 || iss.rdbuf()->in_avail() == 1){
     iss.clear();
     std::getline(F1,line);
     iss.str(line);
    }

    for(j=0;j<ncols;j++)
    {

      if(iss.rdbuf()->in_avail() == 1){
        iss.clear();
        std::getline(F1,line);
        iss.str(line);
      }

     iss >> M[i][j];
    }
  
   i++;
  }

  printf("teste M func %d \n", M[0][0]);
 return;  
}

//funcao para inverter uma matriz e escreve la num ficheiro retorna a matriz inversa

std::vector<std::vector<int>> inverter(std::string filename, std::vector<std::vector<int>> M, int max, int nrows, int ncols){

 std::ofstream F1 (filename);
 F1 << "P2 \n";
 F1 << ncols << " " << nrows << "\n";
 F1 << max <<"\n";
 for (int i =0; i<nrows;i++){
  for(int j=0;j<ncols;j++){
    M[i][j]=max - M[i][j];
    F1 << M[i][j] << " ";
  }
  F1 << "\n";
 // printf("linha feita \n");
 }
 F1.close();
 printf("invertida bem \n");
 return M;
}


//funcao que remove o ruido sem ter em conta o pixel central.

std::vector<std::vector<int>> ruido1(std::string filename, std::vector<std::vector<int>> M, int max, int nrows, int ncols){
 std::ofstream F1 (filename);
 int redu;
 F1 << "P2 \n";
 F1 << ncols << " " << nrows << "\n";
 F1 << max <<"\n";
 for(int i =0; i<nrows;i++){
  for(int j =0;j<ncols;j++){
    //devia-se implementar uma funcao que conseguisse diminuir o ruidos dos pixeis das fronteiras
    if(i == 0 || j == 0 || i == nrows-1 || j ==ncols -1){
      F1<< M[i][j] << " ";
     }
    else{
       redu = (reduzir_ruido(M,i,j)-M[i][j]);
       redu=redu/8;
       F1 << redu << " ";
       M[i][j] = redu;
     }
  }
  F1 << "\n";
 // printf("linha %d \n",i);
 }

 F1.close();
 printf("reduzido bem \n");
 return M;
}


void ruido2(std::string filename, std::vector<std::vector<int>> M, int max, int nrows, int ncols){
  std::ofstream F1 (filename);
 int redu;
 F1 << "P2 \n";
 F1 << ncols << " " << nrows << "\n";
 F1 << max <<"\n";
 for(int i =0; i<nrows;i++){
  for(int j =0;j<ncols;j++){
    //devia-se implementar uma funcao que conseguisse diminuir o ruidos dos pixeis das fronteiras ou no minimo faze-lo igual ao que
    //esta ao seu lado 
    if(i == 0 || j == 0 || i == nrows-1 || j ==ncols -1){
      F1<< M[i][j] << " ";
     }
    else{
       redu = (reduzir_ruido(M,i,j));
       redu=redu/9;
       F1 << redu << " ";
       
     }
  }
  F1 << "\n";
  //printf("linha %d \n",i);
 }
 printf("reduzido box bem \n");
 F1.close();

 return;
}




int reduzir_ruido(std::vector<std::vector<int>> &M, int i ,int j)
{
 int soma=0;
  for(int a =i-1;a<=i+1;a++){
  for (int b =j-1; b<=j+1 ;b++){
    soma = M[a][b] + soma;
    
  }
 }
 //printf("%d soma \n",soma);
 return soma;
}


std::array<float,3> calculo_estimadores(std::vector<std::vector<int>> M,int WhiteValue, int nrows,int ncols){
  std::array<float,3> retorno;
  float variancia=0, size, media=0;
  std::vector<float>freqrelativas(WhiteValue+1);
  std::vector<int>colourfreq(WhiteValue+1,0);

  size= nrows*ncols;
  media = 0.0; variancia = 0.0;

  //calculo das frequencias de cada cor

 for(int i =0 ; i<nrows ; i++)
 {
    for(int j=0; j<ncols ; j++){
    colourfreq[M[i][j]]++;
   }
 }
  
  for(int i =0 ; i<WhiteValue+1; i++){
  freqrelativas[i] = colourfreq[i]/(size) * 100;
  printf("cor %d tem : %d elementos",i,colourfreq[i]);
  printf(" e tem freq relativa %f %% \n",freqrelativas[i]);
  media = media + i*colourfreq[i];
 }


  //encontrar as cores com as 3 maiores frequencias
 std::vector<int> colourfreq1(WhiteValue+1);
 colourfreq1 = colourfreq;
 std::sort(colourfreq1.begin(), colourfreq1.end(), [](int a, int b){ return a>b; } );
 int k =0;
 for(auto& e: colourfreq){
    
   if(e == colourfreq1[0]){
    printf("cor mais frequente %d \n", k);
   }
  if(e == colourfreq1[1]){
    printf("cor 2º frequente %d \n", k);
   }
  if(e == colourfreq1[2]){
    printf("cor 3º frequente %d \n", k);
   }
  k++;
 }
 
 
 //calculo da média
 retorno[0] = media/(size);
 media=media/size;
 //calculo da variancia 
 for(int i=0 ; i < nrows;i++)
 {
  for(int j=0; j<ncols;j++)
  {
    
    variancia = (M[i][j]-media)*(M[i][j]-media) + variancia;
    }
 }

 retorno[1] = variancia/(size-1);
 retorno[2] = sqrt(retorno[1]);

 printf("media %f : variancia : %f  desvio padrão %f , variancia %f \n",media,retorno[1],retorno[2],variancia);

  return retorno;
  }