#include "systemc.h"
#include "grayscaler.h"

SC_MODULE(fileIO)
{
	sc_in <bool> CLK;
	sc_out<int> R;
	sc_out<int> G;
	sc_out<int> B;
	sc_in <int> gray_R;
	sc_in <int> gray_G;
	sc_in <int> gray_B;

	int z;

	SC_CTOR(fileIO) :
		CLK("clock"),
		R("red"),
		G("green"),
		B("blue"),
		gray_R("gray_R"),
		gray_G("gray_G"),
		gray_B("gray_B")
	{
		SC_CTHREAD(readBMP, CLK.pos());
		z=0;
	}

	void readBMP(void)
	{
		//https://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file
		cout << "fopen source"<<endl;
	    int i;
	    FILE* f = fopen("/home/sclab64/workspace/lightness/test_pattern.bmp", "r");

	    if(f==0)
	    {
	    	cout<<"fail fopen source"<<endl;
	    	return;
	    }

	    unsigned char info[26];
	    fread(info, sizeof(unsigned char), 26, f); // read the 54-byte header

	    // extract image height and width from header
	    int width = *(char*)&info[18];
	    int height = *(char*)&info[20];

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

	    for(z=0; z<size; z+=3){
	    	R=data[z];
	    	G=data[z+1];
	    	B=data[z+2];
	    	wait();
	    	data[z]=gray_R;
	    	data[z+1]=gray_G;
	    	data[z+2]=gray_B;

	    }

	    cout << "fopen sink"<<endl;
	    f = fopen("/home/sclab64/workspace/lightness/test_pattern_gray.bmp","w");

	    if(f==0)
	    {
	    	cout<<"fail fopen sink"<<endl;
	    	return;
	    }

	    fwrite(info,sizeof(unsigned char),26,f);	//Header zurückschreiben
	    fwrite(data, sizeof(unsigned char), size, f); // write the rest of the data at once
	    fclose(f);
	}
};