#include "systemc.h"
#include <iostream>

SC_MODULE(mon)
{
	int SIZE = 8;

	sc_vector<sc_in<bool>>A,B,Sum;
	sc_in<bool>Carry;
	sc_in<bool>CLK;

	void monitor()
	{
		while(1)
			{
				cout 	<< sc_time_stamp() << " "
			    << B << A << Carry << Sum << endl;
				wait();
			}
	}

	SC_CTOR(mon) : A("A",SIZE),B("B",SIZE),Sum("Sum",SIZE)
	{
		SC_THREAD(monitor);
		sensitive << CLK.pos();
	}
};
