/*

	Author: Jiajiang Xie

 */
#include <iostream>
#include <cmath>
using namespace std;

class Shapes{
private:
    double x,y;
public:
    Shapes(double x, double y) : x(x), y(y) {}
    virtual double area() const = 0;
};

class Rect : public Shapes{
private:
    double w,h;
public:
    Rect(double x, double y, double w, double h) : Shapes(x,y), w(w), h(h) {}
    double area() const{
        return w * h;
    }
};

class Circle : private Shapes{
private:
    double r;
public:
    Circle(double x, double y, double r) : Shapes(x,y), r(r){}
    double area() const{
        return M_PI * r * r;
    }
};

class Line : public Shapes{
private:
    double x2, y2;
public:
    Line(double x, double y, double x2, double y2) : Shapes(x,y), x2(x2), y2(y2){}
    double area() const{
        return 0;
    }
};

int main() {
    Rect r1(100, 50, 20, 40);	// Rect(x,y, width, height)
    cout << r1.area() << '\n';
    Circle c1(400, 300, 50); // Circle(x,y,radius)
    cout << c1.area() << '\n'; // area should be pi * radius squared
    Line L1(0,0, 300, 400);
    cout << L1.area() << '\n'; // area should be 0
#if 0
    Shape* shapes[6];
	shapes[0] = &r1;
	shapes[1] = &c1;
	shapes[2] = &L1;
	for (int i = 0; i < 2; i++)
		cout << shapes[i]->area() << '\n';
	for (auto s : shapes)
		if (s != nullptr)
			cout << s->area() << '\n';

#endif
}




