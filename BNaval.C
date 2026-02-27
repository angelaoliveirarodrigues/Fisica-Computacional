#include <iostream>

using namespace std;

int main(){
    bool ships[5][5]={
{0,1,1,0,0},
{0,0,0,0,1},
{0,1,0,1,1},
{1,0,0,1,0},
{0,0,1,1,1}};

int tiros = 0;
int numberOfTurns =0;

while (tiros<11){
int row, col;
cout<<"Seleciona as coordenadas\n";
cout<<"Escolhe uma linha entre 0 e 4\n";
cin>>row;
cout<<"Escolhe uma coluna entre 0 e 4\n";
cin>>col;
    if (ships[row][col]){
        ships[row][col]=0;
        tiros++;
        cout<<"Acertaste numa embarcação! Restam-te "<<(11-tiros)<<" embarcações.\n";
    }else{
        cout<<"Falhaste.";
    }
    numberOfTurns++;
}
cout<<"Fim!\n";
cout<<"Ganhaste em "<< numberOfTurns<< " turnos.";
}



