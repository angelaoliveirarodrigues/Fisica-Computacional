//1- Com o mersenne twister

#include <iostream>
#include <random> 
using namespace std;

int main(){
    mt19937 mt{};

    for (int count=1; count<=40; count ++){
        cout<< mt() << '\t';
         if (count%5==0){
        cout<< '\n';
    };
    };

    return 0;
}


//1.1-Distribuição uniforme

#include <iostream>
#include <random>

using namespace std;

int main(){
    mt19937_64 mt{};
    uniform_int_distribution<int> Uni6(1,6);
    for(int i=1; i<=40; i++){
         cout<< Uni6(mt) << '\t';
         if (i%5==0){
        cout<< '\n';
    };
    };
}

//1.2-Seeding com o clock do sistema

#include <iostream>
#include <chrono>
#include <random>
using namespace std;

int main(){
    mt19937 MT{static_cast<mt19937::result_type>(
    chrono::steady_clock::now().time_since_epoch().count())};

    uniform_int_distribution Die6{1,6};

    for (int i=0; i<=40; i++){
        cout<<Die6(MT)<<'\t';
            if (i%10==0){
                cout<<'\n';
            };
    };

}

//seeding com  random device

#include <iostream>
#include <random>

using namespace std;

int main(){
    mt19937 MT{random_device{}()};
    uniform_int_distribution die8(1,8);

    for(int i=0; i<20; i++){
        cout<<die8(MT)<<'\t';
    };
    return 0;
}


//Bernoulli

#include <iostream>
#include <ctime>
#include <random>

using namespace std;

int main(){
    mt19937 R1(time(0));

    bernoulli_distribution Ber(0.5);
    int verdade=0;
    for(int i=0; i<20; i++){
        if (Ber(R1)==1){
            verdade=verdade+1;
        };
    };
    cout<<"Verdadeiro:"<< verdade<<endl;
    cout<<"Falso:"<<20-verdade<<endl;
    return 0;
}

//Binomial
#include <iostream>
#include <ctime>
#include <random>

using namespace std;

int main(){
    mt19937 R1(time(0));

    int ne=1000;
    int nmax=100;
    binomial_distribution<> D(10,0.3);

    int p[10];

    for (int i=0; i<20; i++){
        cout<<D(R1)<<endl;
    };
}
//Poisson
#include <iostream>
#include <ctime>
#include <random>

using namespace std;

int main(){
    int nrolls =10000,nstars=100;
    mt19937 MT(time(0));
    poisson_distribution<> PD(4.1);

    int p[10];
    for (int i=0; i<nrolls; ++i){
        int number=PD(MT);
        if (number<10) ++p[number];
    };

    cout << "poisson_distribution (média=4.1):" << endl;
    for(int i=0; i<10; i++){
        cout<<i<<": "<< string(p[i]*nstars/nrolls,'*') << endl;
    };  
}

//Normal
#include <iostream>
#include <ctime>
#include <random>

using namespace std;

int main(){
    
}
//Exponencial
#include <iostream>
#include <ctime>
#include <random>

using namespace std;

int main(){
    
}