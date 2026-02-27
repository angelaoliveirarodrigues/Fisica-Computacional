#include <iostream>

using namespace std;
 
// argumento nível de energia; retornar comprimento de onda

int main(){
    double  e= 1.60218E-19;
    double  m= 9.1093837E-31;
    double  h= 6.63E-34;
    double  eps= 8.85E-12;
    double  c= 2.99E8;
int n1, n2, Z;
    //criar uma função que retorne o nível de energia
    auto fEL=[&](int n1, int Z, int n2){
        cout<< "Introduza um valor de n1: " ;
        cin>> n1;
        cout<< "Introduza um valor de n2: " ;
        cin>> n2;
        cout<< "Introduza um valor de Z: " ;
        cin>> Z;
        double En1= -(Z*Z*m*m*e*e*e*e)/(8*h*h*eps*eps)*1/(n1*n1);
        double En2= -(Z*Z*m*m*e*e*e*e)/(8*h*h*eps*eps)*1/(n2*n2);
        double E=En2-En1;
        double EL=(h*c)/E;
        return EL;
    };
    cout<<"fEL(n)="<<fEL(n1,Z, n2)<< endl;
    return 0;
    }