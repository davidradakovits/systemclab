#include "systemc.h"

SC_MODULE(xor2)				//macro that creates class xor2
{
	sc_in<bool> A,B;
	sc_out<bool> Y;

	void do_xor2()			//actual gate functionality
	{
		Y.write( ( A.read() && !(B.read()) )||( !(A.read()) && B.read() ) );
		// F = A && !B || !A && B = A xor B
	}

	SC_CTOR(xor2)			//constructor macro
	{
		SC_METHOD(do_xor2);	//register do_xor2 at kernel
		sensitive << A << B;
	}
};
