#ifndef CONVOL_H
#define CONVOL_H

#define SIZE_BUFF   (2 * IMG_W + 3)

#include <systemc.h>
#include "image.h"

SC_MODULE(CONVOL)
{
    sc_in<bool>           clk;
	sc_in<bool>           reset_n;
	sc_in<bool>           h_in;
	sc_in<bool>           v_in;
	sc_in<unsigned char>  p_in;
    sc_out<bool>          h_out;
	sc_out<bool>          v_out;
	sc_out<unsigned char> p_out;

    SC_HAS_PROCESS(CONVOL);

	CONVOL(sc_module_name n, float * filter):sc_module(n)
	{
        this->filter = filter;
        contruct_init();
	}

    CONVOL(sc_module_name n, std::string filtername):sc_module(n)
	{
        filter = new float[9];
        if(!filtername.compare("mean")) {
            filter[0]=1./9;filter[1]=1./9;filter[2]=1./9;
            filter[3]=1./9;filter[4]=1./9;filter[6]=1./9;
            filter[6]=1./9;filter[7]=1./9;filter[8]=1./9;
        }
        else if(!filtername.compare("sobel")) {
            filter[0]=2./9;filter[1]=2./9;filter[2]=0;
            filter[3]=2./9;filter[4]=0./9;filter[6]=-2./9;
            filter[6]=0./9;filter[7]=-2./9;filter[8]=-2./9;
        }
        else {
            filter[0]=0;filter[1]=0;filter[2]=0;
            filter[3]=0;filter[4]=1;filter[6]=0;
            filter[6]=0;filter[7]=0;filter[8]=0;
        }
        contruct_init();
	}

    void contruct_init()
    {
        SC_METHOD(read_stream);
		sensitive << clk.pos();

        SC_CTHREAD(write_stream, clk);

        idx_w = 0;
        idx_h = 0;
        idx_buff = 0;
        image = {IMG_W, IMG_H, pixels};
    }

	private:

    /* For bordure, I just copy the previous value
    */
	void          read_stream();
	void          write_stream();
	void          init();
	void          init_write();
    unsigned char getBuff(int idx);
    unsigned char getWriteBuff(int idx);

	int                 idx_w;
	int                 idx_h;
	Image               image;
    unsigned char       buff[SIZE_BUFF];
    int                 idx_buff;
    int                 start_buff;
    unsigned char       pixels[IMG_W * IMG_H];
    unsigned char       write_buff[SIZE_BUFF];
    int                 start_write_buff;
    int                 idx_write_buff;
    int                 idx_w_write;
    int                 idx_h_write;
    int                 start_writing;
    float *             filter;
};

#endif // CONVOL_H
