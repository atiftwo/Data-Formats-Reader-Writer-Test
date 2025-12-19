#include <fstream>
#include <iostream>

#include <BMPFile/BMPFile.hpp>
#include <JPEGFile/JPEGFile.hpp>

int main()
{
	std::ofstream myFile("output.bmp");
	if (!myFile) return 1;

	BMPFile myImage(16, 16);
	myImage.Write(myFile);

	return 0;
}