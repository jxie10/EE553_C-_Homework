/*
	Make the following main work by writing a class Complex.
	Author: Jiajiang Xie

	Notice that since objects are const, you will have to promise not to change them
 */
#include <iostream>
#include <iomanip>
using namespace std;

class Complex{
private:
    double Re, Im;
public:
    Complex(double r, double i) : Re(r), Im(i) { }
    friend Complex operator +(Complex x, Complex y);
    void print() const{
        cout << fixed << setprecision(1) << "(" << Re << "," << Im << ")" << "\n";
    }
    Complex add(Complex y) const{
        return {this->Re + y.Re, this->Im + y.Im};
    }
    Complex operator -() const{
        return {-Re, -Im};
    }
};

Complex operator +(Complex x, Complex y){
    return {x.Re + y.Re, x.Im + y.Im};
}


int main() {
    const Complex a(1.0, 2.0); // create a complex number with real=1.0 imag=2.0
    const Complex b(0.5, 0.0); // real = 0.5, imag = 0.0
    const Complex c = a + b;   // overload operator + using a friend function
    c.print(); // should print the following to cout: (1.5,2.0)
    // (member syntax).  Should look the same as method add where the name add
    // is replaced by operator +
    const Complex d = a.add(b); // this should be the same as the above except the name
    d.print();
    Complex e = -d; // implement unary - using a member operator. Since it has one parameter which is this should have ZERO PARAMETERS!!!
    e.print();
}
