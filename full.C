#include <iostream>
#include <string>

using namespace std;

int main(){
    string fullName;
    cout<<"Type your name:";
    getline (cin,fullName); //read a line of text; the first argument is cin
    cout<< "Your full name\'s: "<< fullName;
    return 0;
}