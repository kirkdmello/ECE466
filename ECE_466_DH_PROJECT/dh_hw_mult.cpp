#include "systemc.h"
#include "digit.h"
#include "dh_hw_mult.h"

void dh_hw_mult::state_reg(){
  while(1){  
    state.write(next_state.read());
    wait();
  }
}

void dh_hw_mult::state_diagram(){

  
  //self loop is default
  next_state.write(state.read());
  
  switch(state.read()){
    
    case S0_WAIT:
      //printf("wait state\n");
      if(hw_mult_enable.read() == true){
	      next_state.write(S1_EXECUTE);
      } 
      //else{next_state.write(S0_WAIT);}
      break;
      
    case S1_EXECUTE: 
      //printf("execute state\n");
      
      // Hardware multiplication delay = 100 ns
      //wait (100, SC_NS);
      next_state.write(S2_OUTPUT);
      break;
      
    case S2_OUTPUT:
      //printf("output state\n");
      next_state.write(S3_FINISH);
      break;
      
    case S3_FINISH:
    //printf("finsih state\n");
      if(hw_mult_enable.read() == false){
      	next_state.write(S0_WAIT);
      }
      break;
    
    default:
      break;
      
  }
}

void dh_hw_mult::state_output(){
 //default outputs
  out_data_low.write(out_data_low.read());
  out_data_high.write(out_data_high.read());
  hw_mult_done.write(false);
  
  NN_DIGIT a[2], b, c, t, u;
  NN_HALF_DIGIT bHigh, bLow, cHigh, cLow;

  switch(state.read()){

    case S0_WAIT:
      hw_mult_done.write(false);
      break;

    case S1_EXECUTE:
      // Read inputs	
        b = in_data_1.read();
        c = in_data_2.read();
      
        // Original code from NN_DigitMult()...		
        bHigh = (NN_HALF_DIGIT)HIGH_HALF (b);
        bLow = (NN_HALF_DIGIT)LOW_HALF (b);
        cHigh = (NN_HALF_DIGIT)HIGH_HALF (c);
        cLow = (NN_HALF_DIGIT)LOW_HALF (c);

        a[0] = (NN_DIGIT)bLow * (NN_DIGIT)cLow;
        t = (NN_DIGIT)bLow * (NN_DIGIT)cHigh;
        u = (NN_DIGIT)bHigh * (NN_DIGIT)cLow;
        a[1] = (NN_DIGIT)bHigh * (NN_DIGIT)cHigh;
        
        if ((t += u) < u) a[1] += TO_HIGH_HALF (1);
        u = TO_HIGH_HALF (t);
    
        if ((a[0] += u) < u) a[1]++;
        a[1] += HIGH_HALF (t);
        out_data_low.write(a[0]);
        out_data_high.write(a[1]);
      break;  

    case S2_OUTPUT:
      hw_mult_done.write(true);
      break;

    case S3_FINISH:
      hw_mult_done.write(true);
      break;

    default:
      break;
		
  }


}
