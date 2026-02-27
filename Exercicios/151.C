#include <iostream>
#include <random>
#include <vector>
#include <ctime>

using namespace std;

vector<double> rand2vec(int n){
    vector<double> vec2; //criar o vetor para armazenar os números
    mt19937 MT(time(0)); //para gerar os números aleatórios

    uniform_real_distribution Uni(0,360); // Queremos valores entre 0 e 360, os valores têm a mesma probabildade de sair

    for (int i=0; i< n; i++){
        double random=static_cast<double>(Uni(MT));
        vec2.push_back(random);
    };
    return vec2;
};


vector<double>* rand2vecp(int n){
    vector<double>* vec1= new vector<double>; //criar o pointer 
    mt19937 MT(time(0)); //para gerar os números aleatórios

    uniform_real_distribution Uni(0,360); // Queremos valores entre 0 e 360, os valores têm a mesma probabildade de sair

    for (int i=0; i< n; i++){
        double random=static_cast<double>(Uni(MT));
        vec1->push_back(random);
    };
    return vec1;
}

int main(){
    int n;
    cout<<"Digite a quantidade de números aleatórios a gerar:";
    cin>> n;

    vector<double> vetor1 = rand2vec(n);
    cout<<"Os números obtidos com a função rand2vec são:"<< endl;
        for(double numeros: vetor1){
            cout<< numeros << " "; 
        };

    vector<double>* vetorpoin=rand2vecp(n);
    cout<<"Os números obtidos com a função rand2vecp são:" <<endl; 
    for (double point: *vetorpoin){
        cout<< point<< " ";
    };
}
