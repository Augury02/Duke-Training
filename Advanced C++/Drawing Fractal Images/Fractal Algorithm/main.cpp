#include <iostream>
#include <cstdint>
#include "Mandelbrot.h"
#include "Mandelbrot.m"
#include "Bitmap.h"
#include "Bitmap.m"

using namespace std;
using namespace caveofprogramming;

int main() {

    int const WIDTH = 800;
    int const HEIGHT = 600;

    Bitmap bitmap(WIDTH, HEIGHT);

    double min = 999999;
    double max = -999999;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double xFractal = (x - WIDTH / 2) * 2.0 / WIDTH;
            double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

            int iterations = Mandelbrot::getIterations(xFractal, yFractal);

           
            if (iterations == Mandelbrot::MAX_ITERATIONS) {
                bitmap.setPixel(x, y, 255, 255, 255); 				// White color
                continue; 
            }

            // Color mapping
            double smoothColor = log(iterations + 0.5);
            uint8_t red = 255 - (uint8_t)(smoothColor * 255);  
            uint8_t green = 0;  
            uint8_t blue = 0;   

            bitmap.setPixel(x, y, red, green, blue);
            if (blue < min) min = blue;
            if (blue > max) max = blue;
        }
    }

    cout << min << ", " << max << endl;

    bitmap.write("test.bmp");

    cout << "Finished." << endl;
    return 0;
}
