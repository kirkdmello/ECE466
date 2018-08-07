#include "systemc.h"

SC_MODULE(filter){
	
	sc_in <float> x;		//input port x
	sc_out <float> y;		//output port y
	sc_in_clk clock;		//clock input for Cthread
	

	
	//internal signal wires
	sc_signal <float> s1, s2, s3;
	
	void filter_process() {
		float x_samp, y_samp;
		//filter coefficients
		float a1 = 0.4;
		float a2 = -0.8;
		float a3 = -0.5;
		float b1 = 0.24;
		float b2 = 0.2;
		float b3 = 0.25;
		while(1){
			y_samp = y.read();
			x_samp = x.read();
			y.write(b1*s1.read() + b2*s2.read() + b3*s3.read());
			s1.write(a1*s1.read() + x_samp);
			s3.write(s2.read());
			s2.write(x_samp + a2*s2.read() + a3*s3.read());
			wait();
		}
	}
	
	SC_CTOR (filter) {
		SC_CTHREAD (filter_process, clock.pos() );
		s1.write(0);
		s2.write(0);
		s3.write(0);
		y.initialize(0);
	}
};
