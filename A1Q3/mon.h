#include "systemc.h"
#include <iomanip>
using namespace std;

SC_MODULE(mon)
{
  sc_in<float> x, y;
  sc_in_clk  clock;

  void monitor()
  {
	cout << setw(10) << "Time";
	cout << setw(2) << "x";
	cout << setw(6) << "y" << endl;
	
	while (true) {
		cout << setw(10) << sc_time_stamp();
		cout << setw(2) << x.read();
		cout << setw(6) << y.read() << endl;
		wait();		
	}
  }
  SC_CTOR(mon)
  {
    SC_CTHREAD(monitor, clock.pos());
  }
};

