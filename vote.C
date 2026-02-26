#include <iostream>

using namespace std;

int main(){
    int myAge;
    int votingAge=18;
     cout<<"Please write your age:";
     cin>> myAge;
    if (myAge>=votingAge){
        cout<<"You are old enough to vote!";
    } else{
        cout<<"Sorry you are too young to vote.";
    }
    return 0;
}