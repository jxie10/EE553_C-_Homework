/*
	 Author: Jiajiang Xie
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){
    double WC = 0;
    cout << setiosflags(ios::right);
    for(int V = 0; V <= 60; V += 5){
        if (V == 0){
            cout << setw(4) << ' ';
            for(int T = 40; T >= -45; T -= 5){
                cout << setw(4) << T;
            }
            cout << '\n';
        }
        else{
            cout << setw(4) << V;
            for(int T = 40; T >= -45; T -=5){
                WC = 35.74 + 0.6215 * T - 35.75 * (pow(V,0.16)) + 0.4275 * T * (pow(V,0.16));
                cout << setw(4) << round(WC);
            }
            cout << '\n';
        }
    }
}

