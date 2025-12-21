#include "BMPFile.hpp"

BMPFile::BMPFile(int width, int height, bool initialisePixelArray) {
	bmpFileHeader.identification[0] = 'B'; bmpFileHeader.identification[1] = 'M';	
	bmpFileHeader.pixelArrayOffset = sizeof(bmpFileHeader) + sizeof(bmpInfoHeader);

	bmpInfoHeader.headerSize = sizeof(bmpInfoHeader);
	bmpInfoHeader.imageHeight = height;
	bmpInfoHeader.imageWidth = width;
	bmpInfoHeader.colourPlanesCount = 1;
	bmpInfoHeader.bitsPerPixel = 8 * sizeof(uint8_t)*4;
	bmpInfoHeader.compressionMethod = NULL;

	bmpInfoHeader.pixelArraySizeInBytes = width * height * sizeof(Colour);
	bmpFileHeader.fileSize = bmpFileHeader.pixelArrayOffset + bmpInfoHeader.pixelArraySizeInBytes;

	pixelArray = new Colour[width*height];

	// Initialise pixel array
	if (initialisePixelArray)
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
				SetPixel(x, y, {255, 0, 0, 0});
}
BMPFile::BMPFile(std::istream& input) {
	Read(input);
}

BMPFile::~BMPFile() {
	delete[] pixelArray;
}

const BMPFile::Colour& BMPFile::SamplePixel(int x, int y) const {
	int pos = y*bmpInfoHeader.imageWidth+x;
	if (pos > bmpInfoHeader.imageHeight*bmpInfoHeader.imageWidth)
		throw std::out_of_range("");
	return pixelArray[pos];
}
void BMPFile::SetPixel(int x, int y, const Colour& colour) {
	int pos = y*bmpInfoHeader.imageWidth+x;
	if (pos > bmpInfoHeader.imageHeight*bmpInfoHeader.imageWidth)
		throw std::out_of_range("");
	pixelArray[pos] = colour;
}

void BMPFile::Read(std::istream& input) {
	input.read(reinterpret_cast<char*>(&bmpFileHeader), sizeof(bmpFileHeader));
	input.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));

	pixelArray = new Colour[bmpInfoHeader.imageWidth * bmpInfoHeader.imageHeight];
	input.read(reinterpret_cast<char*>(pixelArray), bmpInfoHeader.imageWidth * bmpInfoHeader.imageHeight * sizeof(Colour));
}
void BMPFile::Write(std::ostream& stream) {
	stream.write(reinterpret_cast<char*>(this), bmpFileHeader.pixelArrayOffset);
	stream.write(reinterpret_cast<char*>(pixelArray), bmpInfoHeader.pixelArraySizeInBytes);
}

BMPFile::ImageDimensions BMPFile::GetImageDimensions() const {
	return {
		.w = static_cast<int>(bmpInfoHeader.imageWidth),
		.h = static_cast<int>(bmpInfoHeader.imageHeight)
	};
}
