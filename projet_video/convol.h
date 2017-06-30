#ifndef CONVOL_H
#define CONVOL_H

#define SIZE_BUFF   (2 * IMG_W + 3)

#include <systemc.h>
#include "image.h"
#include "filter.h"

struct CONVOL : FILTER
{
    SC_HAS_PROCESS(CONVOL);

	CONVOL(sc_module_name n, float * filter):FILTER(n)
	{
        this->filter = filter;
        contruct_init();
	}

    CONVOL(sc_module_name n, std::string filtername):FILTER(n)
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

	private:

    void                read_stream();
    void                write_stream();
	void                init();
	void                init_write();
    unsigned char       getBuff(int idx);
    unsigned char       getWriteBuff(int idx);

    unsigned char       buff[SIZE_BUFF];
    int                 idx_buff;
    int                 start_buff;
    unsigned char       write_buff[SIZE_BUFF];
    int                 start_write_buff;
    int                 idx_write_buff;
    int                 idx_w_write;
    int                 idx_h_write;
    int                 start_writing;
    float *             filter;
};

#endif // CONVOL_H
