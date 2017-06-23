#ifndef MEAN_H
#define MEAN_H

#define SIZE_BUFF 2 * IMG_W + 3

#include <systemc.h>
#include "image.h"

SC_MODULE(MEAN)
{
    sc_in<bool>           clk;
	sc_in<bool>           reset_n;
	sc_in<bool>           h_in;
	sc_in<bool>           v_in;
	sc_in<unsigned char>  p_in;
    /*sc_out<bool>          h_out;
	sc_out<bool>          v_out;
	sc_out<unsigned char> p_out;*/

	SC_CTOR(MEAN)
	{
		SC_METHOD(read_stream);
		sensitive << clk.pos();

        current_image_number = 0;
        idx_w = 0;
        idx_h = 0;
        idx_buff = 0;
        image = {IMG_W, IMG_H, pixels};
	}

	private:

    /* For bordure, I just copy the previous value
    */
	void          read_stream();
    unsigned char getBuff(int idx);

	int                 current_image_number;
	int                 idx_w;
	int                 idx_h;
	Image               image;
    unsigned char       buff[2 * IMG_W + 3];
    int                 idx_buff;
    int                 start_buff;
    unsigned char       pixels[IMG_W * IMG_H];
};

#endif // MEAN_H
