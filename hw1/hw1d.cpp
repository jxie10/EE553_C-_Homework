/*
	 Author: Jiajiang Xie
*/
#include <iostream>
using namespace std;

int main(){
    float sum1f = 0;
    float sum2f = 0;
    double sum1d = 0;
    double sum2d = 0;
    for(float i = 1; i<=100 ; i++){
        sum1f += 1/i;
        sum2f += 1/(101-i);
    }
    for(double i = 1; i<=100 ; i++){
        sum1d += 1/i;
        sum2d += 1/(101-i);
    }
    cout << "sum1F = " << sum1f <<", " << "sum2F = " << sum2f <<'\n';
    cout << "sum1D = " << sum2d <<", " << "sum2D = " << sum2d <<'\n';
    cout << "sum1F - sum2F = " << sum1f - sum2f << '\n';
    cout << "sum1D - sum2D = " << sum1d - sum2d << '\n';
}
