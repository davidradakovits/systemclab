#include "systemc.h"
#include <iostream>

SC_MODULE(mon)
{
	sc_in<bool>A,B,Sum,Carry;

	void monitor()
	{
		cout 	<< sc_simulation_time() << " "
				<< B << A << Carry << Sum << endl;
	}

	SC_CTOR(mon)
	{
		SC_METHOD(monitor);
		sensitive << A << B << Sum << Carry;
	}
};
