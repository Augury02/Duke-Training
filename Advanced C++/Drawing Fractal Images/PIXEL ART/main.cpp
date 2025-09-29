#include <iostream>
#include "Bitmap.h"
#include "Bitmap.m"

using namespace std;
using namespace caveofprogramming;

int main() {

	int const WIDTH = 1000;
	int const HEIGHT = 640;

	Bitmap bitmap(WIDTH, HEIGHT);
	//FOR WHITE BG
	for (int y = 0; y < HEIGHT; y++) {		
		for (int x = 0; x < WIDTH; x++) {
		bitmap.setPixel(x, y, 255, 255, 255);
		}
	}
	//FOR TURTLE SHELL
	for (int y = 480; y < 520; y++) {			//The vertical length of the line will be 400 pixels
		for (int x = 400; x < 480; x++) {			//and it will be 10 pixels thick
		bitmap.setPixel(x, y, 76, 187, 23);		//x and y are the coordinates of pixels; the last 3 values correspond
		}										//Red (255), Green (0) and Blue (0)
	}
	
	for (int y = 440; y < 480; y++) {		
		for (int x = 360; x < 520; x++) {
		bitmap.setPixel(x, y, 76, 187, 23);
		}
	}

	for (int y = 360; y < 440; y++) {			
		for (int x = 320; x < 560; x++) {			
		bitmap.setPixel(x, y, 76, 187, 23);	
		}										
	}

	for (int y = 320; y < 360; y++) {			
		for (int x = 280; x < 560; x++) {			
		bitmap.setPixel(x, y, 76, 187, 23);		
		}										
	}

	//FOR TURTLE HEAD
	for (int y = 440; y < 480; y++) {			
		for (int x = 560; x < 640; x++) {			
		bitmap.setPixel(x, y, 50, 205, 50);		
		}										
	}
	for (int y = 400; y < 440; y++) {			
		for (int x = 560; x < 600; x++) {			
		bitmap.setPixel(x, y, 50, 205, 50);			
		}										
	}
	for (int y = 400; y < 440; y++) {			//BLACK DOT / EYE		
		for (int x = 600; x < 640; x++) {			
		bitmap.setPixel(x, y, 0, 0, 0);		
		}										
	}
	for (int y = 400; y < 440; y++) {			//LAST DOT OF EYE LINE
		for (int x = 640; x < 680; x++) {			
		bitmap.setPixel(x, y, 50, 205, 50);		
		}										
	}
	for (int y = 360; y < 400; y++) {					//LINE BELOW EYE
		for (int x = 560; x < 680; x++) {			
		bitmap.setPixel(x, y, 50, 205, 50);			
		}										
	}
	for (int y = 320; y < 360; y++) {					//LAST LINE OF HEAD
		for (int x = 560; x < 640; x++) {			
		bitmap.setPixel(x, y, 50, 205, 50);			
		}										
	}

	//LEGS
	for (int y = 280; y < 320; y++) {			
		for (int x = 320; x < 560; x++) {			
		bitmap.setPixel(x, y, 50, 205, 50);		
		}										
	}
	for (int y = 240; y < 280; y++) {			
		for (int x = 320; x < 400; x++) {			
		bitmap.setPixel(x, y, 50, 205, 50);		
		}										
	}
	for (int y = 240; y < 280; y++) {			
		for (int x = 480; x < 560; x++) {			
		bitmap.setPixel(x, y, 50, 205, 50);		
		}										
	}

	bitmap.write("Turtol.bmp");

	cout << "Finished." << endl;
	return 0;
}