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
        start_writing = 0;
	}

	private:

    void                read_stream();
    void                write_stream();
	void                init();
	void                init_write();

	int                 idx_w;
	int                 idx_h;
    unsigned char       buff[IMG_W / 2 * IMG_H / 2];
    int                 idx_buff;
    int                 start_buff;
    int                 idx_w_write;
    int                 idx_h_write;
    int                 start_writing;
};

#endif // ZOOM_H
