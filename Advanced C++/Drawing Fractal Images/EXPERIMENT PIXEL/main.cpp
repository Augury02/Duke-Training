#include <iostream>
#include "Bitmap.h"
#include "Bitmap.m"

using namespace std;
using namespace caveofprogramming;

int main() {

	int const WIDTH = 800;
	int const HEIGHT = 600;

	Bitmap bitmap(WIDTH, HEIGHT);
	
	//WRITING LETTER H
	for (int y = 100; y < 500; y++) {			//The vertical length of the line will be 400 pixels
		for (int x = 250; x < 260; x++) {			//and it will be 10 pixels thick
		bitmap.setPixel(x, y, 127, 0, 255);		//x and y are the coordinates of pixels; the last 3 values correspond
		}										//Red (255), Green (0) and Blue (0)
	}
	
	for (int y = 295; y < 305; y++) {		
		for (int x = 260; x < 410; x++) {
		bitmap.setPixel(x, y, 0, 255, 70);
		}
	}

	for (int y = 100; y < 500; y++) {			
		for (int x = 410; x < 420; x++) {			
		bitmap.setPixel(x, y, 120, 70, 0);		
		}										
	}
	
	//WRITING LETTER i
	for (int y = 100; y < 300; y++) {			
		for (int x = 500; x < 510; x++) {			
		bitmap.setPixel(x, y, 255, 165, 0);		
		}										
	}

	for (int y = 400; y < 410; y++) {			
		for (int x = 500; x < 510; x++) {			
		bitmap.setPixel(x, y, 0, 255, 255);		
		}										
	}


	bitmap.write("test.bmp");

	cout << "Finished." << endl;
	return 0;
}