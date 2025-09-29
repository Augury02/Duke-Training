#include <iostream>
#include <cstdint>
#include <memory>
#include "Mandelbrot.h"
#include "Mandelbrot.m"
#include "Bitmap.h"
#include "Bitmap.m"

using namespace std;
using namespace caveofprogramming;

int main() {
    // Define image dimensions
    int const WIDTH = 800;
    int const HEIGHT = 600;

    // Define a smaller maximum number of iterations
    constexpr int MAX_ITERATIONS = 1000;

    // Create Bitmap object
    Bitmap bitmap(WIDTH, HEIGHT);

    // Arrays to store histogram and fractal data
    unique_ptr<int[]> histogram(new int[MAX_ITERATIONS]);
    unique_ptr<int[]> fractal(new int[WIDTH * HEIGHT]);

    // Initialize arrays with 0
    fill(histogram.get(), histogram.get() + MAX_ITERATIONS, 0);
    fill(fractal.get(), fractal.get() + WIDTH*HEIGHT, 0);

    // Generate fractal and compute histogram
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double xFractal = (x - WIDTH / 2 - 200) * 2.0 / HEIGHT;
            double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

            int iterations = Mandelbrot::getIterations(xFractal, yFractal);

            fractal[y * WIDTH + x] = iterations;

            if (iterations != MAX_ITERATIONS) {
                histogram[iterations]++;
            }
        }
    }

    // Calculate total number of iterations
    int total = 0;
    for (int i = 0; i < MAX_ITERATIONS; i++) {
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
    bitmap.write("testMODIFIED.bmp");

    cout << "Finished." << endl;
    return 0;
}
