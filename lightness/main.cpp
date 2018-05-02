#include "systemc.h"
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iterator>

//"/home/sclab64/workspace/lightness/test_pattern.bmp"

unsigned char* readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    return data;
}

int sc_main(int argc, char* argv[])
{
	unsigned char* data;

	data=readBMP("/home/sclab64/workspace/lightness/test_pattern.bmp");
	cout << "erster wert: " << data;

	return 0;
}
