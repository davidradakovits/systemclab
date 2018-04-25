#include "systemc.h"
#include "half_adder.h"
#include "OR.h"

SC_MODULE(fulladd)		//macro that creates class fulladd
{
	sc_in<bool> A,B,Cin;
	sc_out<bool> Sum,Carry;

	sc_signal<bool> S1,S2,S3;

	halfadd half_1,half_2;
	or2 or_1;

	SC_CTOR(fulladd) : half_1("half1"),half_2("half2"),or_1("or1")	//constructor macro
	{
		half_1.A(A);
		half_1.B(B);
		half_1.Carry(S1);
		half_1.Sum(S2);

		half_2.A(S2);
		half_2.B(Cin);
		half_2.Carry(S3);
		half_2.Sum(Sum);

		or_1.A(S1);
		or_1.B(S3);
		or_1.Y(Carry);
	}
};
