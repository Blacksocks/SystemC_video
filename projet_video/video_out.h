#ifndef VIDEO_OUT_H
#define VIDEO_OUT_H

#include <systemc.h>
#include "image.h"

SC_MODULE(VIDEO_OUT)
{
    sc_in<bool>          clk;
	sc_in<bool>          reset_n;
	sc_in<bool>          href;
	sc_in<bool>          vref;
	sc_in<unsigned char> pixel_in;

	SC_CTOR(VIDEO_OUT)
	{
		SC_METHOD(read_stream);
		sensitive << clk.pos();

        current_image_number = 0;
        idx_w = 0;
        idx_h = 0;
        image = {IMG_W, IMG_H, pixels};
	}

	private:

	void read_stream();

	int                 current_image_number;
	int                 idx_w;
	int                 idx_h;
	Image               image;
    unsigned char       pixels[IMG_W * IMG_H];
};

#endif // VIDEO_OUT_H
