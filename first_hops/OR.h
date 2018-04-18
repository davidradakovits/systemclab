#include "systemc.h"

SC_MODULE(or2)				//macro that creates class or2
{
	sc_in<bool> A,B;
	sc_out<bool> Y;

	void do_or2()			//actual gate functionality
	{
		Y.write( A.read() || B.read() );
		// F = A || B
	}

	SC_CTOR(or2)			//constructor macro
	{
		SC_METHOD(do_or2);	//register do_or2 at kernel
		sensitive << A << B;
	}
};
