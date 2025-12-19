#include <cstdint>
#include <fstream>

// All storage units are in bytes, unless explicitly mentioned
#pragma pack(push, 1)
class BMPFile {
	public:
	typedef struct {uint8_t r, g, b, a;} Colour;
	BMPFile(int width, int height);
	~BMPFile();

	private:
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
	Colour* pixelArray;

	public:
	Colour SamplePixel(int x, int y) const;
	void SetPixel(int x, int y, const Colour& colour);

	void Read(const std::ifstream&) const = delete;
	void Write(std::ofstream&);
};
#pragma pack(pop)