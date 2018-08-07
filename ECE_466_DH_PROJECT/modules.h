#ifndef MODULES_H
#define MODULES_H
#include "systemc.h"

#define word_length 32
#define half_word_length 16
enum selection (sel_a, sel_b, sel_c);
enum controller_state {}

//adder
SC_MODULE(adder2){
    sc_in< sc_uint<word_length> > a_32;
    sc_in< sc_uint<word_length> > b_32;
    sc_out< sc_uint<word_length> > sum_32;

    void add_process(){
        sum_32.write(a_32.read() + b_32.read());
    }

    SC_TOR(adder2){
        SC_METHOD(add_process);
        sensitive << a_32 << b_32;
    }
};

//32 bit register
SC_MODULE(reg_32){
    sc_in<sc_logic> load;
    sc_in< sc_uint<word_length> > in_32;
    sc_out< sc_uint<word_length> > out_32;
    sc_in_clk clock;

    void reg_32_process(){
        while(1){
            if(load.read == true) out_32.write(in_32.read());
            wait();
        }
    }

    SC_CTOR(reg_32){
        SC_CTHREAD(reg_32_process,clock.pos());
    }
};

//32 shift bit register
SC_MODULE(split_reg_32){
    sc_in<sc_logic> load;
    sc_in< sc_uint<word_length> > in_32;
    sc_out< sc_uint<half_word_length> > high_out_16, low_out_16;
    sc_in_clk clock;

    void split_reg_32_process(){
        short int high, low;
        while(1){
            if(load.read()==true)
            {
                high = (NN_HALF_DIGIT)HIGH_HALF (in_32.read());
                low = (NN_HALF_DIGIT)LOW_HALF (in_32.read());

                high_out_16.write(high);
                low_out_16.write(low);
            }
            wait();
        }

    }

    SC_CTOR(split_reg_32){
        SC_CTHREAD(splitt_reg_32_process,clock.pos());
    }
};


//multiplier
SC_MODULE(mult){
    sc_in< sc_uint<half_word_length> > a_16, b_16;
    sc_out< sc_uint<word_length> > product_32;

    void mult_process(){
        int product;
        product = (int)((NN_DIGIT)a_16.read()*(NN_DIGIT)b_16.read());
        product_32.write(product);
    }

    SC_CTOR(mult){
        SC_METHOD(mult_process);
        sensitive << a_16 << b_16;
    }
};

//comparator
SC_MODULE(comp){
    sc_in< sc_uint<word_length> > a_32, b_32;
    sc_out<sc_logic> LT, GT, EQ;

    void comp_process(){
        //default outputs
        LT.write(false);
        GT.write(false);
        EQ.write(false);

        if(a_32.read() == b_32.read()) EQ.write(true);
        if(a_32.read() > b_32.read()) GT.write(true);
        if(a_32.read() < b_32.read()) LT.write(true);
    }


    SC_CTOR(comp){
        SC_METHOD(comp_process);
        sensitive << a_32 <<b_32; 
    }
};

//3-in multiplexor
SC_MODULE(mux3){
    sc_in<selection> sel;
    sc_in< sc_uint<word_length> > in_a, in_b, in_c;
    sc_out< sc_uint<word_length> > out;

    void mux3_process(){
        switch(sel.read()){
            case sel_a:
                out.write(in_a.read());
            break;

            case sel_b:
                out.write(in_b.read());
            break;

            case sel_c:
                out.write(in_c.read());
            break;

            default:
            break;

        }
    }

    SC_CTOR(mux3){
        SC_METHOD(mux3_process);
        sensitive <<sel <<in_a <<in_b <<in_c;
    }
};

/*//2-in multiplexor
SC_MODULE(mux2){
    sc_in<selection> sel;
    sc_in< sc_uint<word_length> > in_a, in_b;
    sc_out< sc_uint<word_length> > out;

    void mux2_process();

    SC_CTOR(mux2){
        SC_METHOD(mux2_process);
        sensitive <<sel <<in_a <<in_b;
    }
};
*/
//controller(Moore)
SC_MODULE(controller){
    sc_in<sc_logic> LT0, GT0, EQ0, LT1, GT1, EQ1;
    sc_out<sc_logic> b_reg_load, c_reg_load, a0_reg_load, a1_reg_load, a1_mux_select, u_mux_select;
    sc_in_clk clock;
    sc_in<sc_signal> hw_mult_enable;
    sc_out<sc_signal> hw_mult_done;

    //sc_signal

};