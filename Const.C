#include <iostream>
#include <string>

using namespace std;

class Carro{
    public: 
        string brand;
        string model;
        int ano;
        Carro(string x, string y, int z){ // Constructor with parameters
            brand=x;
            model=y;
            ano=z;
        }
};

int main(){
    Carro carroObj1("BMW", "X5", 1999);
    Carro carroObj2("Ford", "Mustang", 1969);

    cout << carroObj1.brand << " "<< carroObj1.model<<" "<<carroObj1.ano <<"\n";
    cout << carroObj2.brand <<" "<< carroObj2.model<<" "<<carroObj2.ano<<"\n";
    return 0;

}


//Outside the class
#include <iostream>
#include <string>

using namespace std;

class Carros{
    public:
    string brand;
    string model;
    int year;
    Carros(string x, string y, int z);
};

Carros::Carros(string x, string y, int z ){
brand=x;
model=y;
year=z;
}

int main(){
    Carros carrosObj("BMW","X5",1999);
    Carros carrosObj2("Ford", "Mustang", 1969);

    cout<< carrosObj.brand<<","<<carrosObj.model<<","<<carrosObj.year<<endl;
    cout<<carrosObj2.brand<<","<<carrosObj2.model<<","<<carrosObj2.year<<endl;
    return 0;
}
