/*
	 Author: Jiajiang Xie
*/
#include <iostream>
#include <math.h>
using namespace std;

int main(){
    double r = 1;
    double angle = 0;
    for(double n = 3; n <= 1e6; n++){
        angle = (360/n/2/180)*M_PI;
        r = r/cos(angle);
        if(n == 10 || n == 1e2 || n == 1e3 || n == 1e4 || n == 1e5 || n == 1e6){
            cout << "n = " << n << "  \t" << "Radius = " << r << endl;
        }
    }
    return 0;
}