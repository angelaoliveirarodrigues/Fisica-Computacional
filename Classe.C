#include <iostream>
#include <string>
using namespace std;

class MyClass{  // Criar a classe MyClass
    public:     // Tipo de acesso
        int myNum; //Atributo variável int
        string myString; // Atributo variável string
};

int main(){
    MyClass myObj;  //Cria um objeto da class

// Aceder aos atributos e atribuir-lhe um valor
    myObj.myNum =14;
    myObj.myString="Textinho";

//Print 
    cout<< myObj.myNum<< "\n";
    cout<< myObj.myString<<"\n";
    return 0;

}


//Multiplos objetos


#include <iostream>
#include <string>

using namespace std;

class AClass{
    public:
        string brand;
        string model;
        int year;
};

int main(){
    AClass classObj1;
    classObj1.brand ="BMW";
    classObj1.model ="X5";
    classObj1.year=1980;

    AClass classObj2;
    classObj2.brand="Ford";
    classObj2.model="Mustang";
    classObj2.year=1967;

    cout<<classObj1.brand<< " "<< classObj1.model<< " "<< classObj1.year<< "\n";
    cout<<classObj2.brand<< " "<< classObj2.model<< " "<< classObj2.year<< "\n";
    return 0;
}


//Class Methods
#include <iostream>
#include <string>

using namespace std;

class Class1{
    public:
        void Funcao(){
            cout<<"Sou uma função!"; //Função definida dentro da classe
        }
};

int main(){
    Class1 obj1;
    obj1.Funcao();
    return 0;
}
