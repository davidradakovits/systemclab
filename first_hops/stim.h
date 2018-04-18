#include "systemc.h"

SC_MODULE(stim)
{
	sc_out<bool> A,B;
	sc_in<bool> CLK;

	void stim_gen()
	{
		A.write(false);
		B.write(false);
		wait();
		A.write(true);
		B.write(false);
		wait();
		A.write(false);
		B.write(true);
		wait();
		A.write(true);
		B.write(true);
		wait();
		sc_stop();
	}

	SC_CTOR(stim)
	{
		SC_THREAD(stim_gen);
		sensitive << CLK.pos();
	}
};
