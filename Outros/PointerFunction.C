#include <iostream>
using namespace std;

void func1(int numVal){
    // função cujo parâmetro é um valor
}


void func2(int &numRef){
    //função cujo parâmetro é uma referência
}

int main(){
    int num=5;
    func1(num);
    func2(num); // em vez de estarmos a passar o número 5, estamos a passar o seu endereço
}

//Passar por referência sem pointers

#include <iostream>
using namespace std;

void swap(int &n1, int &n2){
    int temp;
    temp=n1;
    n1=n2;
    n2=temp;
};

int main(){
    int a=1, b=2;
    cout<<"Before swapping" << endl;
    cout<< "a= "<< a<<endl;
    cout<<"b= "<<b <<endl;
    swap(a,b);
    cout<<"\n After swap"<<endl;
    cout<<"a= "<< a<<endl;
    cout<<"b= "<<b <<endl;
    return 0;
}

/* & denota que a função aceita endereços como parâmetros.
Assim, o compilador pode identificar que, em vez de valores reais, a referência das variáveis 
​​é passada para os parâmetros da função.
Na função swap(), os parâmetros da função n1 e n2 apontam para o mesmo valor que as variáveis a e b.
Portanto, a troca ocorre no valor real.*/


//Passar por referência com pointers

#include <iostream>
using namespace std;

void swap(int*, int*); //Pointers como parâmetros

int main(){
    int a=1, b=2;
    cout<<"Before swapping:"<< endl;
    cout<< "a= "<<a<< endl;
    cout<<"b= "<< b<< endl;

    swap(&a, &b);

    cout<<"After swapping:"<<endl;
    cout<<"a= "<<a<< endl;
    cout<<"b= "<< b<< endl;
    return 0;
}

void swap(int* n1, int* n2){
    int temp;
    temp=*n1;
    *n1=*n2;
    *n2=temp;
}

/* Como o endereço é passado em vez do valor, 
um operador de referência * deve ser usado para aceder ao valor armazenado nesse endereço. 
*n1 e *n2 dão o valor armazenado nos endereços n1 e n2 .*/
#include<iostream>
void refs(int a){
    a=9;
    std::cout<< &a;
}


