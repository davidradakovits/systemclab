#include "systemc.h"
#include "grayscaler.h"
#include "stack_if.h"
#include "stack.h"

SC_MODULE(fileIO)
{
	sc_in <bool> CLK;
	/*
	sc_out<int> R;
	sc_out<int> G;
	sc_out<int> B;
	sc_in <int> gray_R;
	sc_in <int> gray_G;
	sc_in <int> gray_B;
	*/
	sc_port<stack_write_if> out;
	sc_port<stack_read_if> in;

	int z;

	SC_CTOR(fileIO) :
		CLK("clock"),
		/*R("red"),
		G("green"),
		B("blue"),
		gray_R("gray_R"),
		gray_G("gray_G"),
		gray_B("gray_B")*/
		out("out"),
		in("in")
	{
		SC_CTHREAD(readBMP, CLK.pos());
		z=0;
	}

	void readBMP(void)
	{
		//https://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file
		cout << "fopen source"<<endl;
	    int i;
	    FILE* f = fopen("/home/sclab64/workspace/lightness_hierarchical/new_test.bmp", "r");

	    if(f==0)
	    {
	    	cout<<"fail fopen source"<<endl;
	    	return;
	    }

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

	    for(z=0; z<size; z+=3)
	    {
	    	out->nb_write(data[z]);
	    	out->nb_write(data[z+1]);
	    	out->nb_write(data[z+2]);
	    	wait();
	    	char buf;
	    	in->nb_read(buf);
	    	data[z+2]=buf;
	    	in->nb_read(buf);
	    	data[z+1]=buf;
	    	in->nb_read(buf);
	    	data[z]=buf;

	    }

	    cout << "fopen sink"<<endl;
	    f = fopen("/home/sclab64/workspace/lightness_hierarchical/new_test_gray.bmp","w");

	    if(f==0)
	    {
	    	cout<<"fail fopen sink"<<endl;
	    	return;
	    }

	    fwrite(info,sizeof(unsigned char),54,f);	//Header zurückschreiben
	    fwrite(data, sizeof(unsigned char), size, f); // write the rest of the data at once
	    fclose(f);
	}
};
