#include "systemc.h"
#include "grayscaler.h"
#include "fileIO.h"
#include "stack.h"

SC_MODULE(TB)
{
	sc_in <bool> CLK;

	sc_signal<int> s_R;
	sc_signal<int> s_G;
	sc_signal<int> s_B;
	sc_signal <int> s_R_gray;
	sc_signal <int> s_G_gray;
	sc_signal <int> s_B_gray;

	Gray grayscaler;
	fileIO fileIO1;
	stack in,out;

	SC_CTOR(TB) :
		grayscaler("grayscaler_1"),
		fileIO1("File_In_Out"),
		in("in"),out("out")
	{
		grayscaler.CLK(CLK);
		grayscaler.in(in);
		grayscaler.out(out);
		fileIO1.CLK(CLK);
		fileIO1.in(out);
		fileIO1.out(in);
	}
};
