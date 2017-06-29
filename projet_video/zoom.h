#ifndef ZOOM_H
#define ZOOM_H

#include <systemc.h>
#include "image.h"
#include "filter.h"

struct ZOOM : FILTER
{
    SC_HAS_PROCESS(ZOOM);

    ZOOM(sc_module_name n):FILTER(n)
	{
        contruct_init();
	}

	private:

    void                read_stream();
    void                write_stream();
	void                init();
	void                init_write();
    unsigned char       getBuff(int idx);
    unsigned char       getWriteBuff(int idx);

	int                 idx_w;
	int                 idx_h;
    unsigned char       buff[IMG_W];
    int                 idx_buff;
    int                 start_buff;
    unsigned char       pixels[IMG_W * IMG_H];
    unsigned char       write_buff[IMG_W / 2];
    int                 idx_w_write;
    int                 idx_h_write;
    int                 start_writing;
};

#endif // ZOOM_H
