#include <iostream>
#include<string>

using namespace std;

class pessoa{

    public:
    pessoa(string, unsigned int);  //constructor (nome do aluno, data de nascimento)
    virtual ~pessoa()=default; //destutor

    void SetName(string);
    void SetBornDate(unsigned int);

    string GetName();
    unsigned int GetBornDate();
    virtual void Print();

    private:
    string name;
    unsigned int DataN;
};

//Implementação do código
pessoa::pessoa(string S, unsigned int i){
    name=S;
    DataN={i};
}

void pessoa::SetBornDate(unsigned int i){
    DataN=i;
}

void pessoa::SetName(string s){
    name=s;
}

string pessoa::GetName(){
    string n;
    cin>> n;
    name=n;
    return name;
}

unsigned int pessoa::GetBornDate(){
    unsigned int n;
    cin>>n;
    DataN=n;
    return DataN;
}
/*
void pessoa::Print(){
    
}
*/

int main(){
    printf("___constructor\n");
    pessoa P1(/*string,un int*/);
}