#include<iostream>
#include <random>

using namespace std;

int main(){
    mt19937 MT;
    minstd_rand MR;
    uniform_int_distribution<int> Uni1(0,1);
    cout<< "Números aleatórios com mersenne twister:"<<endl;
    for(int i=1; i<=50; i++){
         cout<< Uni1(MT) << '\t';
         if (i%5==0){
        cout<< '\n';
    };
    };
    cout<< "Números aleatórios com minst_rand:"<<endl;
    for(int i=1; i<=50; i++){
         cout<< Uni1(MR) << '\t';
         if (i%5==0){
        cout<< '\n';
    };
    };
}

//
#include<iostream>
#include <random>

using namespace std;

int main(){
    mt19937 MT;
    minstd_rand MR;
    uniform_int_distribution<int> Uni1(5,55);
    cout<< "Números aleatórios com mersenne twister:"<<endl;
    for(int i=1; i<=50; i++){
         cout<< Uni1(MT) << '\t';
         if (i%5==0){
        cout<< '\n';
    };
    };
    cout<< "Números aleatórios com minst_rand:"<<endl;
    for(int i=1; i<=50; i++){
         cout<< Uni1(MR) << '\t';
         if (i%5==0){
        cout<< '\n';
    };
    };
}


//
#include<iostream>
#include <random>

using namespace std;

int main(){
    mt19937 MT;
    minstd_rand MR;
    uniform_int_distribution<int> Uni1(5,55);
    cout<< "Números aleatórios com minst_rand:"<<endl;
    double sum=0;
    for(int i=1; i<=1000; i++){
         cout<< Uni1(MR) << '\t';
         if (i%5==0){
        cout<< '\n';
    };
    sum=sum+Uni1(MR);
    };

    cout<<"A média corresponde a: "<< sum/1000;
}


#include<iostream>
#include <random>

using namespace std;

int main(){
    mt19937 MT;
    minstd_rand MR;
    uniform_int_distribution<int> Uni1(0,1);
    cout<< "Números aleatórios com minst_rand:"<<endl;
    double sum=0.;
    for(int i=1; i<=1000; i++){
         cout<< Uni1(MR) << '\t';
         if (i%5==0){
        cout<< '\n';
    };
    sum=sum+Uni1(MR);
    };

    cout<<"A média corresponde a: "<< sum/1000;
}

//
#include<iostream>
#include <random>

using namespace std;

int main(){
    mt19937 MT;
    minstd_rand MR;
    uniform_int_distribution<int> Uni1(5,55);
    cout<< "Números aleatórios com mersenne twister:"<<endl;
    double sum=0;
    for(int i=1; i<=1000; i++){
         cout<< Uni1(MT) << '\t';
         if (i%5==0){
        cout<< '\n';
    };
    sum=sum+Uni1(MT);
    };

    cout<<"A média corresponde a: "<< sum/1000;
}

#include<iostream>
#include <random>

using namespace std;

int main(){
    mt19937 MT;
    minstd_rand MR;
    uniform_int_distribution<int> Uni1(0,1);
    cout<< "Números aleatórios com mersenne twister:"<<endl;
    double sum=0;
    for(int i=1; i<=1000; i++){
         cout<< Uni1(MT) << '\t';
         if (i%20==0){
        cout<< '\n';
    };
    sum=sum+Uni1(MT);
    };

    cout<<"A média corresponde a: "<< sum/1000;
}

