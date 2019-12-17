/*
	 Author: Jiajiang Xie
*/
#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n);

int main() {
    int n = 0;
    cout << "Please enter a positive integer:" << endl;
    cin >> n;
    if(isPrime(n)){
        cout << "The number " << n << ' ' << "is: PRIME" << endl;
    }
    else{
        cout << "The number " << n << ' ' << "is: NOT PRIME" << endl;
    }
}

bool isPrime(int n){
    int s;
    if(n == 1){
        return false;
    }
    else if(n == 2 || n == 3){
        return true;
    }
    else{
        s = sqrt(n);
        for(int i = 2; i <= s; i++){
            if(n % i == 0){
                return false;
            }
        }
        return true;
    }
}
