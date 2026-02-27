#include <iostream>
#include <vector>

using namespace std;

int main() {
// define hydrogen object
ATOM hydrogen;
hydrogen.A = 1;
hydrogen.Z = 1;
hydrogen.mass = 938.89; //MeV - natural units
hydrogen.name = "Hydrogen";
// define other 5 elements

(...)
//allocate vector and fill it with ATOM's
vector<ATOM> vperiodic(6); //6 elems allocated
(...)
// print the contents of every element of the vector
...
return 0;
}