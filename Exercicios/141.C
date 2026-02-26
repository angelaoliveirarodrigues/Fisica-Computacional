#include <iostream>
#include <random>

using namespace std;
int main(){
mt19937 R;
minstd_rand T;
auto Rmax= R.max();
auto Rmin= R.min();
auto Tmin=T.min();
auto Tmax=T.max();

cout << " Rmax type: " << typeid(Rmax).name() << " Rmax value: " << Rmax << endl;
cout << " Rmin type: " << typeid(Rmin).name() << " Rmin value: " << Rmin << endl;
cout << " Tmax type: " << typeid(Tmax).name() << " Tmax value: " << Tmax << endl;
cout << " Tmin type: " << typeid(Tmin).name() << " Tmin value: " << Tmin << endl;
}

//

#include <iostream>
#include <random>

using namespace std;
int main(){

    mt19937 MT;
    minstd_rand MR;

    for (int i=0; i<3; i++){
        cout<<MT()<<endl;

        cout<<MR()<< endl;
    };
}

//Definindo uma seed
#include <iostream>
#include <random>
using namespace std;
int main(){

    mt19937 MT(82);
    minstd_rand MR(400);

    for (int i=0; i<3; i++){
        cout<<MT()<<endl;

        cout<<MR()<< endl;
    };
}

