#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    double a[]{0,1,2,3,4,5,6,7,8,9};
    for(int i=0; i<10; i++){
        cout<<"i= "<< i<< "|" <<a[i]<< "|";
        a[i]+=10;
        cout<<a[i]<<endl;
    };

    double* p=&a[0];
    for(int i=0; i<10; i++, p++){
        printf("a[%d]=%g | %p | %g \n", i, a[i], p, *p);
    };

    auto x=1; auto y=1.;
    cout<<typeid(x).name() <<endl;
    cout<<typeid(y).name()<<endl;

}