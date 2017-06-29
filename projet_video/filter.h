#ifndef FILTER_H
#define FILTER_H

#include <systemc.h>
#include "image.h"

SC_MODULE(FILTER)
{
    sc_in<bool>           clk;
	sc_in<bool>           reset_n;
	sc_in<bool>           h_in;
	sc_in<bool>           v_in;
	sc_in<unsigned char>  p_in;
    sc_out<bool>          h_out;
	sc_out<bool>          v_out;
	sc_out<unsigned char> p_out;

    SC_CTOR(FILTER)
    {

    }

    void contruct_init()
    {
        SC_METHOD(read_stream);
		sensitive << clk.pos();

        SC_CTHREAD(write_stream, clk);

        idx_w = 0;
        idx_h = 0;
    }

    protected:

	virtual void       read_stream() = 0;
	virtual void       write_stream() = 0;

    int                idx_w;
	int                idx_h;
};

#endif // FILTER_H
