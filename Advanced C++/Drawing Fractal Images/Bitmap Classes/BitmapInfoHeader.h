#ifndef BITMAPINFOHEADER_H_
#define BITMAPINFOHEADER_H_

#include <cstdint>

using namespace std;

namespace caveofprogramming {

#pragma pack(push, 2)

struct BitmapInfoHeader {
	int32_t headerSize{40};     			//Actual size of the struct; counting the entire struct yields to 40 bytes
                                			//int32_t are 4 bytes * 9 = 36 bytes ; int16_t are 2 bytes * 2 = 4 bytes
    int32_t width;              			//Will be defined later in the program
	int32_t height;
	int16_t planes{1};
	int16_t bitsPerPixel{24};   			//1 byte = 8 bits; 3 * 8 = 24 bits; where 3 bytes corresponds to each color RGB
	int32_t compression{0};
	int32_t dataSize{0};        			//Will be set later
	int32_t horizontalResolution{2400};     //2400 bits per pixel
	int32_t verticalResolution{2400};
	int32_t colors{0};
	int32_t importantColors{0};
};

#pragma pack(pop)

}

#endif