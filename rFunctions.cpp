#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

//criar a matriz a partir do ficheiro
void ReadImage(string filename, vector<vector<int>>& M){
    ifstream F(filename);
    string line;
    vector<int> values;
    getline(F,line);
    getline(F,line);
    getline(F,line);
    while(getline(F,line)){
        istringstream iss(line);
        int value;
        while(iss >> value){
            values.push_back(value);
        }
    }
    F.close();
    for (int i=0;i<M.size();i++){
        for (int j=0;j<M[i].size();j++){
            M[i][j]=values[j+i*M[i].size()];
        }
    }
}

//inverter a imagem
void inverte(string filename, vector<vector<int>>& M){
    ifstream File(filename);
    string line; int WhiteValue, nrows, ncols;
    getline(File, line);
    getline(File,line);
    istringstream iss(line);
    iss >> nrows >> ncols;
    iss.clear();
    getline(File, line);
    iss.str(line);
    iss >> WhiteValue;
    for (int i=0;i<nrows;i++){
        for (int j=0;j<ncols;j++){
            M[i][j]=WhiteValue-M[i][j];
        }
    }
}

//eliminar o ruído da matriz
void noiseElim(string filename,vector<vector<int>>& M){
    ifstream F(filename);
    string line;
    getline (F,line);
    getline (F,line);
    istringstream iss(line);
    int nrows, ncols;
    iss >> nrows >> ncols;
    iss.clear();
    for (int i=0;i<nrows;i++){
        if (M[i]==M[0]){
            for (int j=0;j<ncols;j++){
                if (M[i][j]==M[i][0]){
                    M[i][j]=(M[i][j+1]+M[i+1][j]+M[i+1][j+1])/3;
                }
                else if (M[i][j]==M[i][ncols-1]){
                    M[i][j]=(M[i][j-1]+M[i+1][j]+M[i+1][j-1])/3;
                }
                else{
                    M[i][j]=(M[i][j+1]+M[i][j-1]+M[i+1][j+1]+M[i+1][j]+M[i+1][j-1])/5;
                }
            }
        }
        else if (M[i]==M[nrows-1]){
            for (int j=0;j<ncols;j++){
                if (M[i][j]==M[i][0]){
                    M[i][j]=(M[i][j+1]+M[i-1][j]+M[i-1][j+1])/3;
                }
                else if(M[i][j]==M[i][ncols-1]){
                    M[i][j]=(M[i][j-1]+M[i-1][j]+M[i-1][j-1])/3;
                }
                else{
                    M[i][j]=(M[i][j-1]+M[i][j+1]+M[i-1][j]+M[i-1][j+1]+M[i-1][j-1])/5;
                }
            }
        }
        else{
            for (int j=0;j<ncols;j++){
                if (M[i][j]==M[i][0]){
                    M[i][j]=(M[i][j+1]+M[i-1][j]+M[i-1][j+1]+M[i+1][j]+M[i+1][j+1])/5;
                }
                else if(M[i][j]==M[i][ncols-1]){
                    M[i][j]=(M[i][j-1]+M[i-1][j]+M[i-1][j-1]+M[i+1][j]+M[i+1][j-1])/5;
                }
                else{
                    M[i][j]=(M[i][j-1]+M[i][j+1]+M[i-1][j]+M[i-1][j+1]+M[i-1][j-1]+M[i+1][j]+M[i+1][j+1]+M[i+1][j-1])/8;
                }
            } 
        }
    }
}
