/*
	Author: Jiajiang Xie & Siyang Wu
    cite from: https://blog.csdn.net/xianyun2009/article/details/39012415
 */

/*
  You have to write:
  1. Constructor (that allocates dynamic memory)
  2. Destructor (free the memory delete [])
  3. Copy Constructor
  4. Operator = (use either old way or copy and swap)
  5. Move Constructor
 */
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <cmath>
using namespace std;

class DynamicBitmap {
private:
    uint32_t w, h;
    uint32_t* pixels;


public:
    DynamicBitmap(uint32_t width, uint32_t height, uint32_t color) : w(width), h(height), pixels(new uint32_t[w*h]) {
        for(int i = 0; i < w*h; i++){
            pixels[i] = color;
        }
    }
    ~DynamicBitmap(){
        delete [] pixels;
    }
    //copy:DynamicBitmap():{}
    DynamicBitmap& operator =(DynamicBitmap copy){
        w = copy.w;
        h = copy.h;
        swap(pixels,copy.pixels);
        return *this;
    }
    DynamicBitmap(DynamicBitmap&& orig) : w(orig.w), h(orig.h), pixels(orig.pixels){
        orig.pixels = nullptr;
    }

    void horizLine(int start, int end, int y, uint32_t color) {
        for (int i = start; i <= end; i++) {
            pixels[y*w+i] = color;
        }
    }

    void vertLine(int start, int end, int x, uint32_t color) {
        for (int i = start; i <= end; i++) {
            pixels[i*w+x] = color;
        }
    }

    void drawRect(int topleft_x, int topleft_y, int W, int H, uint32_t color) {
        //TODO
    }

    void fillRect(int topleft_x, int topleft_y, int W, int H, uint32_t color) {
        //TODO
    }
    void line(int start_x, int start_y, int end_x, int end_y, uint32_t color) {
        if (abs(end_y - start_y) > abs(end_x - start_x)) {
            swap(start_x, start_y);
            swap(end_x, end_y);
        }
        if (start_x > end_x) {
            swap(start_x, end_x);
            swap(start_y, end_y);
        }
        int deltax = end_x - start_x;
        int deltay = abs(end_y - start_y);
        int error = deltax / 2;
        int ystep;
        int y = start_y;
        if (start_y < end_y) {
            ystep = 1;
        } else {
            ystep = -1;
        }
        for (int i = start_x; i <= end_x; i++) {
            if (abs(end_y - start_y) > abs(end_x - start_x)) {
                pixels[y*w+i] = color;
            } else {
                pixels[i*w+y] = color;
            }
            error = error - deltay;
            if (error < 0) {
                y = y + ystep;
                error = error + deltax;
            }
        }
    }

    void ellipse(int xCenter, int yCenter, int Rx, int Ry, uint32_t color) {
        //TODO
    }

    void save(const char filename[]) {
        stbi_write_png(filename, w, h, 4, pixels, w*4);
    }
};

int main() {
    // FIRST PART (ADD COLORS HERE)
    constexpr uint32_t BLACK = 0xFF000000; // black opaque
    constexpr uint32_t RED = 0xFF0000FF; // red opaque
    constexpr uint32_t BLUE = 0xFFFF0000;
    constexpr uint32_t WHITE = 0xFFFFFFFF;
    constexpr uint32_t YELLOW = 0xFF00FFFF;



    // SECOND PART (DO NOT EDIT)
    int xcenter = 100;
    int ycenter = 100;
    int xdiameter = 200;
    int ydiameter = 100;

    DynamicBitmap b(1024, 1024, BLACK); // Potentially dynamic size (Now: 1024 x 1024 pixels)

    b.horizLine(0, 500, 200, RED); // horizontal line from x=0 to x=500, @y = 200
    b.vertLine(0, 399, 300, RED); // y=0 to y=399 @ x= 300, red vertical line

    //b.drawRect(200,200, 100,50, BLUE); // blue rectangle, top-left=200,200 w=100 h=50
    //b.fillRect(201,201, 98,48, WHITE); // same but filled

    b.line(400,0, 550,300, YELLOW); // draw a line https://en.wikipedia.org/wiki/Bresenham's_line_algorithm

    //b.ellipse(xcenter, ycenter, xdiameter, ydiameter);

    b.save("bitmap.png");

}



