#include "systemc.h"

SC_MODULE(stim)
{
	int SIZE = 8;

	sc_vector<sc_out<bool>> A,B;
	sc_in<bool> CLK;

	void stim_gen()
	{
		A[0].write(false);
		A[1].write(false);
		A[2].write(false);
		A[3].write(false);
		A[4].write(false);
		A[5].write(false);
		A[6].write(false);
		A[7].write(false);
		B[0].write(true);
		B[1].write(false);
		B[2].write(false);
		B[3].write(true);
		B[4].write(false);
		B[5].write(false);
		B[6].write(true);
		B[7].write(false);
		wait();

		A[0].write(false);
		A[1].write(false);
		A[2].write(false);
		A[3].write(false);
		A[4].write(false);
		A[5].write(false);
		A[6].write(false);
		A[7].write(false);
		B[0].write(false);
		B[1].write(false);
		B[2].write(false);
		B[3].write(false);
		B[4].write(false);
		B[5].write(false);
		B[6].write(false);
		B[7].write(false);
		wait();

		sc_stop();
	}

	SC_CTOR(stim) : A("A",SIZE),B("B",SIZE)
	{
		SC_THREAD(stim_gen);
		sensitive << CLK.neg();
	}
};
