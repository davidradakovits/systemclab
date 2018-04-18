#include "systemc.h"
#include "half_adder.h"
#include "stim.h"
#include "mon.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> sig_A,sig_B,sig_Sum,sig_Carry;
	sc_clock TestCLK("TestClock", 10, SC_NS, 0.5, 1, SC_NS);

	stim stim1("Stimulus");
	stim1.A(sig_A);
	stim1.B(sig_B);
	stim1.CLK(TestCLK);

	halfadd DUT("HalfAdder");
	DUT.A(sig_A);
	DUT.B(sig_B);
	DUT.Sum(sig_Sum);
	DUT.Carry(sig_Carry);

	mon mon1("Monitor");
	mon1.A(sig_A);
	mon1.B(sig_B);
	mon1.Carry(sig_Carry);
	mon1.Sum(sig_Sum);

	cout << "B" << "A" << "C" << "S" << endl;

	sc_start();

	return 0;
}
