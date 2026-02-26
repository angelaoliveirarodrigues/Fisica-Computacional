/* Para além de armazenarem o endereço de uma variável única, 
os pointers podem armazenar o enderço de um array*/

int* ptr;
int arr[5];
ptr=&arr[0]; //armazena o endereço do primeiro elemento do array
/*ptr+1 é equivalente a &arr[1];
  ptr+2 é equivalente a &arr[2];
  ptr+3 é equivalente a &arr[3];
  ptr+4 é equivalente a &arr[4];

  OU SEJA

*(ptr+1) é equivalente a arr[1];
 *(ptr+2) é equivalente a arr[2];
  *(ptr+3) é equivalente a arr[3];
  *(ptr+4) é equivalente a arr[4];
*/

//Exemplo 1

#include <iostream>
using namespace std;

int main(){
    float arr[3];
    float* ptr;
    for (int i=0; i<3; i++){
        cout<< "&arr [" << i <<"] = "<< &arr[i] <<endl; //displaying address using arrays
    };

    ptr=arr; //ptr=&arr[0]

    cout<<"\nDisplaying address using pointers: "<< endl;
    for (int i=0; i<3; i++){
        cout<< "ptr +" << i <<" = "<<ptr +1 << endl;
    };
    return 0;
}


//Programa para inserir e mostrar dados adicionados pelo utilizador usando pointers
#include <iostream>
using namespace std;

int main(){
    float arr[5];
    cout<< "Enter 5 numbers: "<< endl;
    for (int i=0; i<5; i++){
        cin>> *(arr +i); //armazenar os números introduzidos pelo utilizador
    // ou cin>>arr[i]
    };
    cout<< "Displaying data: "<<endl;
    for (int i=0; i<5; i++){
        cout<<*(arr +i)<< endl;
        //ou cout<<arr[i]<< endl;
    };
    return 0;

}