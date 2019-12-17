/*
	 Author: Jiajiang Xie
*/
#include <iostream>
using namespace std;

int main(){
    int n = 100;
    int gaussr = 0;
    int loopr = 0;
    gaussr = n*(n+1)/2;
    cout << "Gauss Result: " << gaussr << endl;
    for(int i = 1; i<=100 ; i++){
        loopr += i;
    }
    cout << "Loop Result: " << loopr <<endl;
    if(gaussr == loopr){
        cout << "Both results are the same." << endl;
    }
}