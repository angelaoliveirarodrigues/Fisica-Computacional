#include <iostream>
using namespace std;

//Operador new
/* O operador new aloca memória para uma variável*/
int* pointVar;
pointVar =new int; //alocamos memória dinamicamente para uma variável int usando o operador new

// No caso de um array, o operador new retorna o endereço do primeiro elemento do array

//Operador delete
/*Podemos desalocar a memória ocupada pela variável. O operador delete retorna a memória para o sistema operacional*/
delete pointerVariable;

// declare um pointer
int* pointVar;
//  alocação de memória
// para uma variável int 
pointVar = new int;
*pointVar = 45;
cout << *pointVar; // Output: 45
// desalocar a memória
delete pointVar;


//Alocação dinâmica de memória
#include <iostream>
using namespace std;

int main(){
    int* pointInt; //declarar um pointer int
    float* pointFlo; //declarar um pointer floa3t

    //Alocar memória dinamicamente 
    pointInt= new int;
    pointFlo= new float;

    //Atribuir
    *pointInt=45;
    *pointFlo=45.45f;

    cout<< *pointInt << endl;
    cout<< *pointFlo<< endl;

    //desalocar memória

    delete pointInt;
    delete pointFlo;

    return 0;
}

//Para arrays

#include <iostream>
using namespace std;

int main(){
    int num;
    cout<< "Inserir número de alunos:";
    cin>> num;
    float* ptr;

    ptr=new float;

    cout<<"Insira as notas dos alunos:"<<endl;
    for(int i=0; i<num; i++){
        cout<< "Aluno "<< i+1<<":";
        cin>>*(ptr +i);
    };

    cout<<"Notas dos alunos."<<endl;
    for(int i=0; i<num; i++){
        cout<< "Aluno "<< i+1<<":" <<*(ptr +i)<< endl;
    };

    delete[] ptr;

    return 0;
}

/* Neste programa, pedimos ao usuário para inserir o número de alunos e armazená-lo no num variável.
Em seguida, alocamos a memória dinamicamente para o float array usando new.
Entramos com os dados no array (e depois imprimimos) usando a notação de pointer.
Depois que não precisarmos mais do array, desalocamos a memória do array usando o código delete[] ptr;.
[] para indicar que a desalocação de memória é a de um array.*/

