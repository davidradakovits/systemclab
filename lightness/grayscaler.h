#ifndef GRAY_H_
#define GRAY_H_

#include "systemc.h"

SC_MODULE(Gray)
{
	sc_signal <sc_logic> s_R;
	sc_signal <sc_logic> s_G;
	sc_signal <sc_logic> s_B;
	sc_in <bool> CLK;
	sc_in <int> R;
	sc_in <int> G;
	sc_in <int> B;

	sc_out <int> gray_R;
	sc_out <int> gray_G;
	sc_out <int> gray_B;

	SC_CTOR(Gray) :
		CLK("clock"),
		R("red"),
		G("green"),
		B("blue"),
		gray_R("gray_R"),
		gray_G("gray_G"),
		gray_B("gray_B")
	{
		SC_CTHREAD(do_gray, CLK.pos());
	}

	void do_gray(void)
	{
		while(true){
			wait();

			int int_red=R.read(), int_green=G.read(), int_blue=B.read();
			int gray,min,max;

			if( (int_red >= int_green) && (int_red >= int_blue) ) 			max = int_red;
			else if ( (int_green >= int_red) && (int_green >= int_blue) ) 	max = int_green;
			else if ( (int_blue >= int_red) && (int_blue >= int_green) ) 	max = int_blue;

			if( (int_red <= int_green) && (int_red <= int_blue) )			min = int_red;
			else if ( (int_green <= int_red) && (int_green <= int_blue) )	min = int_green;
			else if ( (int_blue <= int_red) && (int_blue <= int_green) )	min = int_blue;

			gray=(int)(max+min)>>1;	//use shift instead of division to stay synthable
			gray_R.write(gray);
			gray_G.write(gray);
			gray_B.write(gray);
		}
	}
};

#endif /* GRAY_H_ */
