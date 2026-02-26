//Modelo de Bohr
#include <iostream>
#include <cmath>

using namespace std;

//a 
// argumento nível de energia; retornar o nível de enrgia

int main(){
   const double  e= 1.60218e-19;
   const int  Z= 1;
   const double  m= 9.1093837e-31;
   const double  h= 6.63e-34;
   const double  eps= 8.85e-12; 
    int n;
    cout<< "Introduza um valor de n: " ;
    cin>> n;
    //criar uma função que retorne o nível de energia
    auto fE=[&e, &Z, &h, &m, &eps](int n){
        double En= -(Z*Z*m*m*e*e*e*e)/(8*h*h*eps*eps)*1/(n*n);
        return En;
    };
     cout<<"fE(n)="<<fE(n)<< endl;
    return 0;
}


//b 
#include <iostream>

using namespace std;
 
// argumento nível de energia e Z; retornar o nível de enrgia

int main(){
    double  e= 1.60218E-19;
    double  m= 9.1093837E-31;
    double  h= 6.63E-34;
    double  eps= 8.85E-12; 
    int n, Z;
    //criar uma função que retorne o nível de energia
    auto fEZ=[&e, &h, &m, &eps](int n, int Z){
        cout<< "Introduza um valor de n: " ;
        cin>> n;
        cout<< "Introduza um valor de Z: " ;
        cin>> Z;
        double En= -(Z*Z*m*m*e*e*e*e)/(8*h*h*eps*eps)*1/(n*n);
        return En;
    };
    cout<<"fEZ(n)="<<fEZ(n,Z)<< endl;
    return 0;
}


//c 
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


//d
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
// argumento nível de energia; retornar comprimento de onda

int main(){

    double  e= 1.60218E-19;
    double  m= 9.1093837E-31;
    double  h= 6.63E-34;
    double  eps= 8.85E-12; 
    int n=1;
    int Z=1;

    while (n<20 & Z<10){
        auto fEZ=[&e, &h, &m, &eps](int n, int Z){

    };
    return 0;
    }
 // criar um array E[Z][n] em que sejam colocados os valores de energia




 vector<vector<double>> vE;
}
