/*
	 Author: Jiajiang Xie
*/
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

void polar2Rect(double r,double theta,double& dx,double& dy);

int main(){
    ifstream f("hw2e.dat");
    double r,theta,dx,dy,x = 0, y = 0;

    while(!f.eof()){
        f >> theta >> r;
        if (r < 0 || theta < 0){
            cout << "Robot has reached final destination." << endl;
            break;
        }
        else{
            polar2Rect(r, theta, dx, dy);
            x += dx;
            y += dy;
            x = round(x * 1e4)/1e4;
            y = round(y * 1e4)/1e4;
            cout << showpoint << setprecision(5) << "New robot position (X,Y): (" << x << ',' << y << ")." << '\n';
        }
    }
}

void polar2Rect(double r,double theta,double& dx,double& dy){
    constexpr double dt = M_PI/180;
    dx = r * sin(theta * dt);
    dy = r * cos(theta * dt);
}