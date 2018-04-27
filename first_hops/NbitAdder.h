#include "systemc.h"
#include "full_adder.h"

SC_MODULE(Nadder)	//macro that creates class adder
{
	static const int SIZE = 8;

	sc_in<bool> CLK;
	sc_vector< sc_in<bool> > A,B;
	sc_vector< sc_out<bool> > Sum;
	sc_out<bool> Carry;

	sc_vector< sc_signal<bool> > S1;

	sc_vector<fulladd> adders;

	//SC_CTOR(Nadder) : A("A",SIZE),B("B",SIZE),Sum("Sum",SIZE),S1("S1",SIZE+1),adders("adders",SIZE)
	SC_CTOR(Nadder) : A("A"),B("B"),Sum("Sum"),S1("S1"),adders("adders",SIZE)
	{
		A.init(SIZE);
		B.init(SIZE);
		Sum.init(SIZE);
		S1.init(SIZE);
		//S1[0].write(false);

		for(int i = 0; i < SIZE; i++)
		{
			adders[i].A(A[i]);
			adders[i].B(B[i]);
			adders[i].Cin(S1[i]);
			adders[i].Sum(Sum[i]);
			//adders[i].Carry(S1[i+1]);	//ripple carry
		}
		for(int i = 0; i < SIZE-1; i++)
		{
			adders[i].Carry(S1[i+1]);
		}

		adders[SIZE-1].Carry(Carry);	//last carry is global carry out

		//SC_THREAD(Nadder);
		//sensitive << CLK.pos();
	}
};
