#include "systemc.h"
#include "TB.h"

int sc_main(int argc, char ** arv) {

	sc_clock CLK("ClockSignal", 20, SC_NS);

	TB tb1("Top_module");
	tb1.CLK(CLK);

	sc_start(5000, SC_US);
	return 0;
}
