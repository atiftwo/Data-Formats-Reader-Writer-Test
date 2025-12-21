#pragma once

#include <iostream>
#include <cstdint>

// All storage units are in bytes, unless explicitly mentioned
class BMPFile {
	public:
	struct Colour {
		uint8_t b, g, r, a;
		Colour() : b(0), g(0), r(0), a(0) {}
		Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
		: b(blue), g(green), r(red), a(alpha) {}

		template<typename R, typename G, typename B, typename A,
			std::enable_if_t<std::is_arithmetic_v<R>
			&& std::is_arithmetic_v<G>
			&& std::is_arithmetic_v<B>
			&& std::is_arithmetic_v<A>, int> = 0>
		Colour(R red, G green, B blue, A alpha)
		: b(static_cast<uint8_t>(blue)), g(static_cast<uint8_t>(green)),
		r(static_cast<uint8_t>(red)), a(static_cast<uint8_t>(alpha)) {}
	};

	BMPFile(int width, int height, bool initialisePixelArray = true);
	BMPFile(std::istream& inputFile);
	~BMPFile();
	
	private:
	#pragma pack(push, 1)
	struct {
		char identification[2];
		uint32_t fileSize;
		char reserved[4]{'\0'};
		uint32_t pixelArrayOffset;
	} bmpFileHeader;
	struct {
		uint32_t headerSize;
		uint32_t imageWidth;
		uint32_t imageHeight;
		uint16_t colourPlanesCount;
		uint16_t bitsPerPixel;
		uint32_t compressionMethod;
		uint32_t pixelArraySizeInBytes;
		char reserved[16]{'\0'};
	} bmpInfoHeader;
	#pragma pack(pop)

	Colour* pixelArray; // Should be fine as we know the pixel array size (We do have to infer it from what we have)

	public:
	const BMPFile::Colour& SamplePixel(int x, int y) const;
	void SetPixel(int x, int y, const Colour& colour);

	void Read(std::istream&);
	void Write(std::ostream&);

	typedef struct {int w, h;} ImageDimensions;
	ImageDimensions GetImageDimensions() const;
};