#include "systemc.h"

SC_MODULE(and2)				//macro that creates class and2
{
	sc_in<bool> A,B;
	sc_out<bool> Y;

	void do_and2()			//actual gate functionality
	{
		Y.write( A.read() && B.read() );
		// F = A && B
	}

	SC_CTOR(and2)			//constructor macro
	{
		SC_METHOD(do_and2);	//register do_or2 at kernel
		sensitive << A << B;
	}
};
