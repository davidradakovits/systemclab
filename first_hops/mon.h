#include "systemc.h"
#include <iostream>

SC_MODULE(mon)
{
	sc_in<bool>A,B,Sum,Carry;
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

	SC_CTOR(mon)
	{
		SC_THREAD(monitor);
		sensitive << CLK.pos();
	}
};
