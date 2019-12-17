/*

	Author: Jiajiang Xie

 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
int main() {
    cout << setiosflags(ios::left);
    ifstream f("3C.dat");
    int r, c, tsum=0;
    f >> r >> c ;
    int array[r+1][c+1];
    for (int i = 0; i < r+1; i++){
        for(int j = 0; j < c+1; j++ ){
            if(i < r && j < c){
                f >> array[i][j];
            } else{
                array[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            array[i][c] += array[i][j];
        }
        tsum += array[i][c];
    }
    array[r][c] = tsum;
    for (int j = 0; j < c; j++){
        for (int i = 0; i < r; i++){
            array[r][j] += array[i][j];
        }
    }
    string s(35,'-');
    for (int i = 0; i <= r+1; i++){
        if(i <= r-1){
            for (int j = 0; j < c+1; j++){
                if(j < c){
                    cout << setw(4) << array[i][j] << " ";
                } else{
                    cout << "rowsum = " << array[i][j];
                }
            }
            cout << "\n";
        }
        else if(i == r){
            cout << s << "\n";
        }
        else{
            for(int j = 0; j < c+1; j++){
                if(j < c){
                    cout << setw(4) << array[i-1][j] << " ";
                }else{
                    cout << "totalsum = " << array[i-1][j];
                }
            }
            cout << "\n";
        }
    }
}