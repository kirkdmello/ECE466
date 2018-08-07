#include "systemc.h"
#include "stim.h"
#include "filter.h"
#include "mon.h"

int sc_main(int argc, char* argv[])
{
  sc_signal<float> xSig, ySig;
  sc_clock TestClk("TestClock", 10, SC_NS, 0.5, 1, SC_NS); 
  
  stim Stim1("Stimulus");
  Stim1.x(xSig);
  Stim1.clock(TestClk);
    
  filter DUT("filter");
  DUT.x(xSig);
  DUT.y(ySig);
  DUT.clock(TestClk);

  mon Monitor1("Monitor");
  Monitor1.x(xSig);
  Monitor1.y(ySig);
  Monitor1.clock(TestClk); 
  
  sc_trace_file* Tf = sc_create_vcd_trace_file("filter_traces");
  Tf->set_time_unit(1, SC_NS);
  sc_trace(Tf, xSig  , "X" );
  sc_trace(Tf, ySig  , "Y" );


  sc_start(100,SC_NS);  // run for 100 ns
  sc_close_vcd_trace_file(Tf);
  
  return 0;
}
