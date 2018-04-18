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
	mon1.CLK(TestCLK);

	cout << "B" << "A" << "C" << "S" << endl;

	sc_trace_file* Tf;
	Tf = sc_create_vcd_trace_file("traces");
	//((vcd_trace_file*)Tf)->sc_set_vcd_time_unit(-9);
	sc_trace(Tf, sig_A, "A");
	sc_trace(Tf, sig_B, "B");
	sc_trace(Tf, sig_Sum, "Sum");
	sc_trace(Tf, sig_Carry, "Carry");

	sc_start();
	sc_close_vcd_trace_file(Tf);
	return 0;
}
