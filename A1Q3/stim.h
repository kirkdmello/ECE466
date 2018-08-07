#include "systemc.h"
#include <iomanip>

SC_MODULE(stim)
{
  sc_out<float> x;
  sc_in_clk clock;

  void stimgen()
  {
	x.write(0);
	wait();
	x.write(1);
	wait();
	x.write(0);
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
	//sc_stop();
  }
  SC_CTOR(stim)
  {
    SC_CTHREAD(stimgen, clock.pos());
  }
};
