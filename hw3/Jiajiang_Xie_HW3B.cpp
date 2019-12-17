/*

	Author: Jiajiang Xie

 */
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main(){
    ifstream f("3B.dat");
    double g, max, min, mean, sum = 0;
    int amount = 0;
    while (!f.eof()) {
        f >> g;
        sum += g;
        amount++;
    }
    mean = sum/amount;
    ifstream fin("3B.dat");
    double array[amount];
    for (int i = 0; i < amount; i++){
        fin >> array[i];
    }
    cout << fixed << setprecision(1);
    cout << "Elements = " << double(amount) << "\n";
    max = array[0]; min = array[0];
    double var = (array[0] - mean)*(array[0] - mean);
    for(int i = 1; i < amount; i++){
        if (array[i] > max){
            max = array[i];
        }
        if (array[i] < min){
            min = array[i];
        }
        var += (array[i] - mean)*(array[i] - mean);
    }
    var /= amount;
    cout << "Max = " << max << "\n";
    cout << "Min = " << min << "\n";
    cout << "Mean = " << mean << "\n";
    cout << "Var = " << var << endl;
}