#ifndef BITMAPINFOHEADER_H_
#define BITMAPINFOHEADER_H_

#include <cstdint>

using namespace std;

namespace caveofprogramming {

#pragma pack(push, 2)

struct BitmapInfoHeader {
	int32_t headerSize{40};			//Total of 40 bytes; each int32 is 4 bytes * 9 = 36; each int15  is 2 bytes*2 = 4
	int32_t width;
	int32_t height;
	int16_t planes{1};
	int16_t bitsPerPixel{24};		//3 bytes per color of Red, Green and Blue; each byte is 8 bits thus 24
	int32_t compression{0};
	int32_t dataSize{0};			//will be given value later
	int32_t horizontalResolution{2400};		//no. of pixels
	int32_t verticalResolution{2400};
	int32_t colors{0};
	int32_t importantColors{0};
};

#pragma pack(pop)

}

#endif