#include "systemc.h"

SC_MODULE(grayscale)	//macro that creates class grayscale
{
	static int SIZE = 8;

	//sc_vector< sc_in<bool> > R,G,B;
	//sc_vector< sc_out<bool> > grey_R,grey_G,grey_B;
	sc_in< sc_uint<SIZE> > R,G,B;
	sc_in< sc_uint<SIZE> > grey_R,grey_G,grey_B;
	sc_in<bool> CLK;

	sc_uint<SIZE> max;
	sc_uint<SIZE> min;

	void do_gray()		//actual functionality
	{
		if( (R >= G) && (R >= B) )
		{
			max = R;
		}
		else if ( (G >= R) && (G >= B) )
		{
			max = G;
		}
		else if ( (B >= R) && (B >= G) )
		{
			max = B;
		}
		/////////////////////////////////
		if( (R <= G) && (R <= B) )
		{
			min = R;
		}
		else if ( (G <= R) && (G <= B) )
		{
			min = G;
		}
		else if ( (B <= R) && (B <= G) )
		{
			min = B;
		}
		/////////////////////////////////
		grey_R=grey_G=grey_B=((max+min)<<2);
	}

	//SC_CTOR(grayscale) : R("R"),G("G"),B("B"),grey_R("grey_R"),grey_G("grey_G"),grey_B("grey_B")
	SC_CTOR(grayscale)
	{
		//Constructor (macro)

		//R.init(SIZE);
		//G.init(SIZE);
		//B.init(SIZE);
		//grey_R.init(SIZE);
		//grey_G.init(SIZE);
		//grey_B.init(SIZE);

		SC_METHOD(do_gray);	//register do_gray at simulation kernel
		sensitive << CLK;
	}
};
