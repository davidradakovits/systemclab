#include "systemc.h"
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iterator>

int sc_main(int argc, char* argv[])
{
	unsigned char info[26];
	FILE* f = fopen("/home/sclab64/workspace/lightness/test_pattern.bmp", "rb");

	fread(info, sizeof(unsigned char), 26, f); // read header

	int width = info[18];
	int height = info[20];
	int size = width * height;

	unsigned char data[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once

	fclose(f);

	FILE* g = fopen("/home/sclab64/workspace/lightness/test_pattern_gray.bmp", "w+b");
	int success=fwrite(info, sizeof(unsigned char), 26, g); // write header
	fclose(g);

	cout << width << " " << height << " " << success << " The End.";

	return 0;
}
