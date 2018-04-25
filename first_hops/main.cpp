#include "systemc.h"
#include "NbitAdder.h"
#include "stim.h"
#include "mon.h"
#include <string>
#include <stdio.h>

int sc_main(int argc, char* argv[])
{
	static const int SIZE = 8;

	sc_signal<bool> CLK;
	sc_vector<sc_signal<bool> > sig_A,sig_B,sig_Sum;
	sig_A.init(SIZE);
	sig_B.init(SIZE);
	sig_Sum.init(SIZE);
	sc_signal<bool> sig_Carry;
	sc_clock TestCLK("TestClock", 10, SC_NS, 0.5, 1, SC_NS);

	stim stim1("Stimulus");
	stim1.A(sig_A);
	stim1.B(sig_B);
	stim1.CLK(TestCLK);

	Nadder DUT("bitAdderUT");
	DUT.A(sig_A);
	DUT.B(sig_B);
	DUT.Sum(sig_Sum);
	DUT.Carry(sig_Carry);
	DUT.CLK(TestCLK);
	DUT.S1[0].write(false);

	mon mon1("Monitor");
	mon1.A(sig_A);
	mon1.B(sig_B);
	mon1.Carry(sig_Carry);
	mon1.Sum(sig_Sum);
	mon1.CLK(TestCLK);

	sc_trace_file* Tf;
	Tf = sc_create_vcd_trace_file("traces");
	//((vcd_trace_file*)Tf)->sc_set_vcd_time_unit(-9);
	Tf->set_time_unit(5, SC_PS);
	for(int i = 0; i < SIZE; i++)
	{
		char buffer[5];
		sprintf(buffer,"A%d",i);
		sc_trace(Tf, sig_A[i], buffer);
		sprintf(buffer,"B%d",i);
		sc_trace(Tf, sig_B[i], buffer);
		sprintf(buffer,"Sum%d",i);
		sc_trace(Tf, sig_Sum[i], buffer);
	}
	sc_trace(Tf, sig_Carry, "Carry");
	//sc_trace(Tf, TestCLK, "CLK");

	cout << endl << endl << "       B " << "       A " << "C " << "       S" << endl;

	sc_start(30, SC_NS);
	sc_close_vcd_trace_file(Tf);

	cout << endl;

	return 0;
}
