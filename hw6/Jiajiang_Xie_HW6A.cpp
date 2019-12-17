/*
	Author: Jiajiang Xie
    cite from: https://blog.csdn.net/xianyun2009/article/details/39012415
 */
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <cmath>
using namespace std;

class Bitmap {
private:
    constexpr static uint32_t w = 800, h = 600;
    uint32_t pixels[h][w];
public:
    Bitmap(uint32_t v) {
        for (uint32_t i = 0; i < h; i++)
            for (uint32_t j = 0; j < w; j++) {
                pixels[i][j] = v;
            }
    }

    void horizLine(int start, int end, int y, uint32_t color) {
        for (int i = start; i <= end; i++) {
            pixels[y][i] = color;
        }
    }

    void vertLine(int start, int end, int x, uint32_t color) {
        for (int i = start; i <= end; i++) {
            pixels[i][x] = color;
        }
    }

    void drawRect(int topleft_x, int topleft_y, int W, int H, uint32_t color) {
        for (int i = topleft_x; i <= topleft_x + W; i++) {
            pixels[topleft_y][i] = color;
            pixels[topleft_y + H][i] = color;
        }
        for (int j = topleft_y; j <= topleft_y + H; j++) {
            pixels[j][topleft_x] = color;
            pixels[j][topleft_x + W] = color;
        }
    }

    void fillRect(int topleft_x, int topleft_y, int W, int H, uint32_t color) {
        for (int i = topleft_x; i <= topleft_y + H; i++) {
            for (int j = topleft_y; j <= topleft_x + W; j++) {
                pixels[i][j] = color;
            }
        }
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
                pixels[y][i] = color;
            } else {
                pixels[i][y] = color;
            }
            error = error - deltay;
            if (error < 0) {
                y = y + ystep;
                error = error + deltax;
            }
        }
    }

    void ellipse(int xCenter, int yCenter, int Rx, int Ry, uint32_t color) {
        int a = Rx/2, b = Ry/2;
        double d = b * b + a * a * (-b + 0.25);
        int x = 0, y = b, fx = a * a / sqrt((double) a * a + b * b);
        while (x != fx) {
            if (d < 0) {
                d += b * b * (2 * x + 3);
            } else {
                --y;
                d += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            }
            ++x;
            pixels[yCenter + y][xCenter + x] = color;
            pixels[yCenter + y][xCenter - x] = color;
            pixels[yCenter - y][xCenter + x] = color;
            pixels[yCenter - y][xCenter - x] = color;
        }
        d = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
        while (y > 0) {
            if (d < 0) {
                ++x;
                d += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            } else
                d += a * a * (-2 * y + 3);
            --y;
            pixels[yCenter + y][xCenter + x] = color;
            pixels[yCenter + y][xCenter - x] = color;
            pixels[yCenter - y][xCenter + x] = color;
            pixels[yCenter - y][xCenter - x] = color;
        }
        pixels[yCenter - b][xCenter] = color;
        pixels[yCenter + b][xCenter] = color;
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
    constexpr uint32_t GREEN = 0xFF00FF00;


    // SECOND PART (DO NOT EDIT)
    int xcenter = 100;
    int ycenter = 100;
    int xdiameter = 200;
    int ydiameter = 100;

    Bitmap b(BLACK); // Hardcoded size (***800 x 600 pixels***)

    b.horizLine(0, 500, 200, RED); // Red horizontal line, from x=0 to x=500, at y = 200
    b.vertLine(0, 399, 300, RED); // Red vertical line, from y=0 to y=399, at x = 300

    b.drawRect(200,200, 100,50, BLUE); // Blue rectangle, TOP-LEFT at x=200, y=200. width=100, height=50
    b.fillRect(201,201, 98,48, WHITE); // White rectangle, same rules as above, but filled with color

    b.line(400,0, 550,300, YELLOW); // Line drawn using https://en.wikipedia.org/wiki/Bresenham's_line_algorithm

    b.ellipse(xcenter, ycenter, xdiameter, ydiameter,GREEN); //Ellipse using specs from above

    b.save("bitmap.png");


    // THIRD PART - OPTIONAL FUNCTION
    // 100pt bonus for properly implementing Wu's antialiasing
    //https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
    //b.antialiasedLine(400,0, 550,300, YELLOW);
}

