#include <iostream>
#include "Bitmap.h"
#include "Bitmap.m"

using namespace std;
using namespace caveofprogramming;

int main() {

	Bitmap bitmap(800, 600);

	bitmap.write("test.bmp");

	cout << "Finished." << endl;
	return 0;
}