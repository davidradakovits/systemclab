#ifndef GRAY_H_
#define GRAY_H_

#include "systemc.h"
#include "stack.h"

SC_MODULE(Gray)
{
	sc_signal <sc_logic> s_R;
	sc_signal <sc_logic> s_G;
	sc_signal <sc_logic> s_B;

	sc_in <bool> CLK;

	sc_port<stack_read_if> in;
	sc_port<stack_write_if> out;

	SC_CTOR(Gray) :
		CLK("clock"),
		in("in"),out("out")
	{
		SC_CTHREAD(do_gray, CLK.pos());
	}

	void do_gray(void)
	{
		while(true){
			wait();

			char int_red, int_green, int_blue;
			in->nb_read(int_red);
			in->nb_read(int_green);
			in->nb_read(int_blue);

			char min,max,gray;

			if( (int_red >= int_green) && (int_red >= int_blue) ) 			max = int_red;
			else if ( (int_green >= int_red) && (int_green >= int_blue) ) 	max = int_green;
			else if ( (int_blue >= int_red) && (int_blue >= int_green) ) 	max = int_blue;

			if( (int_red <= int_green) && (int_red <= int_blue) )			min = int_red;
			else if ( (int_green <= int_red) && (int_green <= int_blue) )	min = int_green;
			else if ( (int_blue <= int_red) && (int_blue <= int_green) )	min = int_blue;

			gray=(char)(max+min)>>1;	//use shift instead of division to stay synthable

			out->nb_write(gray);
			out->nb_write(gray);
			out->nb_write(gray);
		}
	}
};

#endif /* GRAY_H_ */
