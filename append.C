#include <iostream>
#include <string>
using namespace std;
 
int main () {
  string firstName = "Ambrósio ";
  string lastName = "Anastácio";
  string fullName = firstName.append(lastName);
  cout << fullName;
  return 0;
}