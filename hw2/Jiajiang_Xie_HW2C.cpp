/*
	 Author: Jiajiang Xie
*/
#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n);
int countPrimes(int a, int b);

int main() {
    int a = 0; int b = 0;
    cout << "Please enter a positive integer as the minimum:" << endl;
    cin >> a;
    cout << "Please enter a positive integer as the maximum:" << endl;
    cin >> b;
    cout << " There are " << countPrimes(a,b) << " " << "primes in the range [" << a << ',' << b << "]." <<endl;
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

int countPrimes(int a, int b){
    int count = 0;
    for (int i = a; i <= b; i++){
        if(isPrime(i)){
            count += 1;
        }
    }
    return count;
}