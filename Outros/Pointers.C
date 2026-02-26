/* Em C++, pointers são variáveis que armazenam o memory adress de outras variáveis
*/

//Exemplo 1- Endereço- Se tivermos uma variável var no nosso programa, &var dá-nos o memory adress dessa variável

#include <iostream>
using namespace std;

int main(){
    int var1=3;
    int var2=24;
    int var3=37;
    //queremos fazer print do endereço das variáveis
    cout<< "Endereço da Variável 1:" << &var1 << endl;
    cout<< "Endereço da Variável 2:" << &var2 << endl;
    cout << "Endereço da Variável 3:" << &var3 << endl;
    return 0;
}

/*  Os pointers são usados para armazenar os endereços
Declaramos pointers do seguinte modo:*/
int* pointVar;

// Atribuir endereços a ponteiros
int* pointVar; //declaramos que é um pointer
int var=5; // é atribuido varlor 5 à variável var
pointVar= &var; //o endereço de var é atribuído ao pointer

//Obter o valor do endereço usando pointers

int* pointVar;
int var=5;
// atribuir o endereço de var a pointVar
pointVar= &var;
cout<< *pointVar << endl; //O output é 5

/* * opera num ponteiro e dá o valor apontado pelo endereço armazenado no ponteiro*/

//Exemplo de funionamento de Ponteiros

#include <iostream>
using namespace std;

int main(){
    int var=5;
    int* pointerVar;
    pointerVar = &var;
    cout<<"var =" << var << endl; //imprime a variável
    cout<< "Address of var (&var)= " << &var <<endl; //imprime o endereço da variável
    cout<< "pointerVar= " <<pointerVar<< endl; 
    cout<< "Content of the address pointed to by pointerVar= "<< *pointerVar<< endl;
    }

/* Para alterar valores apontados por ponteiros*/

int var =5;
int* pointVar;
pointVar=&var;
*pointVar =1;
cout<< var << endl; // o output é 1

//Exemplo 

#include <iostream>
using namespace std;
int main(){
    int var =5;
    int* pointVar= &var;
    cout<< "var=" << var<< endl;
    cout<<"*pointVar=" << *pointVar<< endl;
    var=7;
    cout<< "var=" << var<< endl;
    cout<<"*pointVar=" << *pointVar<< endl;
    *pointVar=120;
    cout<< "var=" << var<< endl;
    cout<<"*pointVar=" << *pointVar<< endl;
    return 0;
}

