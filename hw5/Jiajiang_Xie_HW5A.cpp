/*

	Author: Jiajiang Xie

 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

/*
	suggestion:
for this assignment:

class Shape {
public:
  virtual void draw(ostream& s) = 0;
};

class Polygon : public Shape {
 void draw(ostream& s) {...}
};
 */
class Shape{
private:
    double x,y;
public:
    Shape(double x, double y) : x(x), y(y){}
    virtual void draw(ostream& s) = 0;
    double getx(){
        return x;
    }
    double gety(){
        return y;
    }
};

class FilledRect : public Shape{
private:
    double w, h;
public:
    FilledRect(double x, double y, double w, double h) : Shape(x,y), w(w), h(h){}
    void draw(ostream& s){
        s << getx() << ' ' << gety() << ' ' << "moveto" << ' '
          << getx() + w << ' ' << gety() << ' ' << "lineto" << ' '
          << getx() + w << ' ' << gety() + h<< ' ' << "lineto" << ' '
          << getx() << ' ' << gety() + h<< ' ' << "lineto" << ' '
          << "closepath" << ' '
          << "fill\n";
    }
};

class Rect : public Shape{
private:
    double w,h;
public:
    Rect(double x, double y, double w, double h) : Shape(x,y), w(w), h(h) {}
    void draw(ostream& s){
        s << getx() << ' ' << gety() << ' ' << "moveto" << ' '
          << getx() + w << ' ' << gety() << ' ' << "lineto" << ' '
          << getx() + w << ' ' << gety() + h<< ' ' << "lineto" << ' '
          << getx() << ' ' << gety() + h<< ' ' << "lineto" << ' '
          << "closepath" << ' '
          << "stroke\n";
    }
};

class FilledCircle : public Shape{
private:
    double r;
public:
    FilledCircle(double x, double y, double r) : Shape(x,y), r(r){}
    void draw(ostream& s){
        s << getx() << ' ' << gety() << ' ' << r << ' '
          << 0 << ' ' << 360 << ' ' << "arc" << ' '
          << "fill\n";
    }
};

class Circle : public Shape{
private:
    double r;
public:
    Circle(double x, double y, double r) : Shape(x,y), r(r){}
    void draw(ostream& s){
        s << getx() << ' ' << gety() << ' ' << r << ' '
          << 0 << ' ' << 360 << ' ' << "arc" << ' '
          << "stroke\n";
    }
};

class Line : public Shape{
private:
    double x2, y2;
public:
    Line(double x, double y, double x2, double y2) : Shape(x,y), x2(x2), y2(y2){}
    void draw(ostream& s){
        s << getx() << ' ' << gety() << ' ' << "moveto" << ' '
          << x2 << ' ' << y2 << ' ' << "lineto" << ' '
          << "stroke\n";
    }
};

class Polygon : public Shape{
private:
    double r;
    int n;
public:
    Polygon(double x, double y, double r, int n) : Shape(x,y), r(r), n(n){}
    void draw(ostream& s){
        const double a2r = M_PI /180;
        double dx,dy,theta;
        theta = (360.0/n/2) * a2r;
        dx = r * sin(theta);
        dy = r * cos(theta);
        s << getx() + dx << ' ' << gety() + dy << ' ' << "moveto\n";
        for(int i = 1; i < n; i++){
            theta += (360.0/n) * a2r;
            dx = r * sin(theta);
            dy = r * cos(theta);
            s << getx() + dx << ' ' << gety() + dy << ' ' << "lineto\n";
        }
        s << "closepath" << ' ' << "stroke\n";
    }
};

class Drawing {
private:
    ofstream f;
    vector<Shape*> shapes;
    vector<int> color;
public:
    Drawing(const string& filename) : f(filename.c_str()), shapes() {
    }
    void add( Shape* s ) {
        shapes.push_back(s);
    }
    void setrgb(int red, int green, int blue){
        add(nullptr);
        color.push_back(red);
        color.push_back(green);
        color.push_back(blue);
    }

    void draw() {
        uint64_t numShapes;
        int r;
        numShapes = shapes.size();
        for (uint64_t i = 0; i < numShapes; i++){
            if(shapes[i] == nullptr){
                f << color[0] << ' ' << color[1] << ' ' << color[2] << ' ' << "setrgbcolor\n";
                color.erase(color.begin(),color.begin()+3);
            } else{
                shapes[i]->draw(f);
            }
        }
    }
};

int main() {
    ofstream f(  );
    Drawing d("test2.ps");
    d.setrgb(1,0,0); // set drawing color to be bright red:  1 0 0 setrgbcolor
    d.add(new FilledRect(100.0, 150.0, 200.0, 50)); // x y moveto x y lineto ... fill
    d.add(new Rect(100.0, 150.0, 200.0, 50));       // x y moveto x y lineto ... stroke
    for (int x = 0; x < 600; x += 100)
        d.add(new FilledCircle(x,200,50.0)); // x y r 0 360 arc fill
    d.setrgb(0,1,0); // the rest are green

    d.add(new Circle(0,0, 100)); // 0 0 100 0 360 stroke
    d.add(new Line(400,500, 600,550));
    d.add(new Polygon(200,200, 50, 6));
    d.draw();
}

