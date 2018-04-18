#include "systemc.h"
#include "AND.h"
#include "XOR.h"

SC_MODULE(halfadd)				//macro that creates class halfadd
{
	sc_in<bool> A,B;
	sc_out<bool> Sum,Carry;

	and2 and_1;
	xor2 xor_1;

	SC_CTOR(halfadd) : and_1("andgate1"), xor_1("xorgate1")
	{
		and_1.A(A);
		and_1.B(B);
		and_1.Y(Carry);

		xor_1.A(A);
		xor_1.B(B);
		xor_1.Y(Sum);
	}
};
