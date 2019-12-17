/*
	 Author: Jiajiang Xie
*/
#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n = 0;
    int n1 = 1e6;
    float sum1 = 0;
    float sum2 = 0;
    float sum3 = 0;
    float result1 = 0;
    float result2 = 0;
    float result3 = 0;
    cout << "Please enter a positive integer:" << endl;
    cin >> n;
    for(float i=1; i<=n; i++){
        sum1 += 1/(i*i);
    }
    result1 = sqrt(6*sum1);
    cout << "result1 = " << result1 << endl;
    for(float i=1; i<=n1; i++){
        sum2 += 1/(i*i);
    }
    result2 = sqrt(6*sum2);
    for(float i=n1; i>=1; i--){
        sum3 += 1/(i*i);
    }
    result3 = sqrt(6*sum3);
    cout << "result2 = " << result2 << endl;
    cout << "result3 = " << result3 << endl;
}
