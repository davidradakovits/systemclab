#include "systemc.h"
#include "grayscaler.h"
#include "fileIO.h"

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

	SC_CTOR(TB) : grayscaler("grayscaler_1"),fileIO1("File_In_Out")
	{
		grayscaler.CLK(CLK);
		grayscaler.R(s_R);
		grayscaler.G(s_G);
		grayscaler.B(s_B);
		grayscaler.gray_R(s_R_gray);
		grayscaler.gray_G(s_G_gray);
		grayscaler.gray_B(s_B_gray);

		fileIO1.CLK(CLK);
		fileIO1.R(s_R);
		fileIO1.G(s_G);
		fileIO1.B(s_B);
		fileIO1.gray_R(s_R_gray);
		fileIO1.gray_G(s_G_gray);
		fileIO1.gray_B(s_B_gray);
	}
};
