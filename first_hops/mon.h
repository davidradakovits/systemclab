#include "systemc.h"
#include <iostream>

SC_MODULE(mon)
{
	static const int SIZE = 8;

	sc_vector<sc_in<bool> >A,B,Sum;
	sc_in<bool>Carry;
	sc_in<bool>CLK;

	void monitor()
	{
		while(1)
			{
				//cout << sc_time_stamp() << " ";
				for(int i = 0; i < SIZE; i++) cout << B[i];
				cout << " ";
				for(int i = 0; i < SIZE; i++) cout << A[i];
				cout << " " << Carry << " ";
				for(int i = 0; i < SIZE; i++) cout << Sum[i];
				cout << endl;
				wait();
			}
	}

	//SC_CTOR(mon) : A("A",SIZE),B("B",SIZE),Sum("Sum",SIZE)
	SC_CTOR(mon) : A("A"),B("B"),Sum("Sum")
	{
		A.init(SIZE);
		B.init(SIZE);
		Sum.init(SIZE);

		SC_THREAD(monitor);
		sensitive << CLK.pos();
	}
};
