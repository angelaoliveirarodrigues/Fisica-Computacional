#include <iostream>

using namespace std;

int readNumber(){
int num;
 cin>> num;
 return num;
}

void writeAnswer(int num){
    cout<< "A resposta é " << num << endl;
}

int main(){
    int  x{readNumber()};
    int y{readNumber()};
    writeAnswer(x+y);
    return  0;
}