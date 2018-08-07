#include "systemc.h"
#include "digit.h"

#ifndef _DH_HW_MULT_H_
#define _DH_HW_MULT_H_ 1

enum dh_hw_mult_state{S0_WAIT, S1_EXECUTE, S2_OUTPUT, S3_FINISH};

SC_MODULE (dh_hw_mult)
{
  sc_in_clk clock;
  sc_in<bool> hw_mult_enable; 
  sc_in<NN_DIGIT> in_data_1;
  sc_in<NN_DIGIT> in_data_2;
  sc_out<NN_DIGIT> out_data_low;
  sc_out<NN_DIGIT> out_data_high;
  sc_out<bool> hw_mult_done;
  
  sc_signal<dh_hw_mult_state> state, next_state;

  //void process_hw_mult();
  void state_reg();
  void state_diagram();
  void state_output();
  
  SC_CTOR (dh_hw_mult)
  {
    SC_CTHREAD (state_reg, clock.pos());
    SC_METHOD(state_output); sensitive << state;
    SC_METHOD(state_diagram); sensitive << state << hw_mult_enable;
  }
  
};

#endif /* end _DH_HW_MULT_H_ */
