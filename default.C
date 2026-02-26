#include <iostream>
#include <string>

using namespace std;

void myFunction(string country = "Noruega"){  //Noruega é o default value
    cout << country << "\n";
}

int main(){
    myFunction();
    myFunction("Suécia");
    myFunction("Portugal");
    return 0;
}