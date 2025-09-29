#include <iostream>
#include <cstdint>
#include <memory>
#include "Mandelbrot.h"
#include "Mandelbrot.m"
#include "Bitmap.h"
#include "Bitmap.m"
#include "Zoom.h"
#include "ZoomList.h"
#include "ZoomList.m"

using namespace std;
using namespace caveofprogramming;

int main() {
    // Image dimensions
    int const WIDTH = 800;
    int const HEIGHT = 600;

    // Maximum number of iterations
    constexpr int MAX_ITERATIONS = 500;

    // Create ZoomList object
    ZoomList zoomList(WIDTH, HEIGHT);
    zoomList.add(Zoom(WIDTH / 3 - 1000, HEIGHT / 5 - 200, 10.0));     //Changed from 0.1 > 0.2 > 5.9 ; Colors inside varied
    
    // Create Bitmap object
    Bitmap bitmap(WIDTH, HEIGHT);

    // Vectors to store histogram and fractal data
    vector<int> histogram(MAX_ITERATIONS, 0);
    vector<int> fractal(WIDTH * HEIGHT, 0);

    // Generate fractal and compute histogram
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double xFractal = (x - WIDTH / 2) * 2.0 / WIDTH;
            double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

            // Apply zoom
            zoomList.doZoom((xFractal/2)-300, (yFractal*2)+400);

            int iterations = Mandelbrot::getIterations(xFractal, yFractal);

            fractal[y * WIDTH + x] = iterations;

            if (iterations != MAX_ITERATIONS) {
                histogram[iterations]++;
            }
        }
    }

    // Calculate total number of iterations
    int total = 0;
    for (int i = 0; i < MAX_ITERATIONS; i+=2) {         //Changed from i++
        total += histogram[i];
    }

    // Generate fractal image
    for (int y = 0; y < HEIGHT; y++) {         
        for (int x = 0; x < WIDTH; x++) {
            int iterations = fractal[y * WIDTH + x];

            double hue = 0.0;

            for (int i = 0; i <= iterations; i++) {
                hue += ((double) histogram[i]) / total;
            }

            // Set pixel color
            uint8_t red = 0;
            uint8_t green = hue * 140;
            uint8_t blue = 220;

            bitmap.setPixel(x, y, red, green, blue);
        }
    }

    // Write bitmap to file
    bitmap.write("ChangeZoomAttempt1.bmp");
    cout << "Finished." << endl;
    return 0;
}
