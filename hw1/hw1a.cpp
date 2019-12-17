/*
	 Author: Jiajiang Xie
*/
#include <iostream>
using namespace std;

int main(){
    int n = 0;
    cout << "Please enter a positive integer:" << endl;
    cin >> n;
    while(n != 1){
        if(n%2 != 0){
            n = n*3 + 1;
        }
        else{
            n /= 2;
        }
        cout << n << ' ';
    }
    return 0;
}

