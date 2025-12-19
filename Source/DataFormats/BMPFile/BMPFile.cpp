#include "BMPFile.hpp"

#include <cstdint>
#include <fstream>

BMPFile::BMPFile(int width, int height) {
	bmpFileHeader.identification[0] = 'B'; bmpFileHeader.identification[1] = 'M';	
	bmpFileHeader.pixelArrayOffset = sizeof(bmpFileHeader) + sizeof(bmpInfoHeader);

	bmpInfoHeader.headerSize = sizeof(bmpInfoHeader);
	bmpInfoHeader.imageHeight = height;
	bmpInfoHeader.imageWidth = width;
	bmpInfoHeader.colourPlanesCount = 1;
	bmpInfoHeader.bitsPerPixel = 8 * sizeof(uint8_t)*4;
	bmpInfoHeader.compressionMethod = NULL;

	bmpInfoHeader.pixelArraySizeInBytes = width * height * sizeof(uint8_t)*4;
	bmpFileHeader.fileSize = bmpFileHeader.pixelArrayOffset + bmpInfoHeader.pixelArraySizeInBytes;

	// Initialise pixel array
	pixelArray = new Colour[width*height];
	for (int i = 0; i < width*height; ++i) {
		int y = (int)(i/width);
		SetPixel(i-(y*width), y, {255, 0, 0, 0});
	}
}
BMPFile::~BMPFile() {
	delete[] pixelArray;
}

BMPFile::Colour BMPFile::SamplePixel(int x, int y) const {

}
void BMPFile::SetPixel(int x, int y, const Colour& colour) {
	pixelArray[y*bmpInfoHeader.imageWidth+x] = colour;
}

void BMPFile::Write(std::ofstream& stream) {
	stream.write(reinterpret_cast<char*>(this), bmpFileHeader.pixelArrayOffset);
	stream.write(reinterpret_cast<char*>(pixelArray), bmpInfoHeader.pixelArraySizeInBytes);
}
