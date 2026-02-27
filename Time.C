#include <chrono>
#include <cmath> // pow()
#include <iostream> // cout
constexpr int N = 1000000;
int main() {
    
double a=12345678967598.0, b; //variable declaration
// compute time spent on power to the fourth
auto t1 = std::chrono::steady_clock::now();
for (int i=0; i<N; i++) b=a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a;
auto t2 = std::chrono::steady_clock::now();
auto dt1_msec = duration_cast<std::chrono::milliseconds>(t2-t1).count();
auto dt1_musec = duration_cast<std::chrono::microseconds>(t2-t1).count();
cout << "xelev19: " << dt1_msec << " [msec] "
<< dt1_musec << " [musec]" << endl;

// wait 10 second
std::this_thread::sleep_for(std::chrono::seconds(10))

t1 = steady_clock::now();
for ( int i=0; i<N; i ++) b=pow(a, 19.) ;
t2 = steady_clock::now();
auto dt2_msec = duration_cast<std::chrono::milliseconds>(t2-t1).count();
auto dt2_musec = duration_cast<std::chrono::microseconds>(t2-t1).count();
cout << "pow(x,4): " << dt2_msec << " [msec] " << dt2_musec << " [musec]" << endl;
}