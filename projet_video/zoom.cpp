#include <cstdio>
#include <sstream>
#include <iomanip>
#include "zoom.h"

void ZOOM::init()
{
    idx_h = 0;
}

void ZOOM::init_write()
{
    idx_w_write = 0;
    idx_h_write = 0;
}

void ZOOM::read_stream()
{
    if(!reset_n)
    {
        idx_w = 0;
        init();
        init_write();
        return;
    }
    if(!h_in && idx_w != 0)
    {
        idx_h++;
        idx_w = 0;
    }
    if(idx_h == IMG_H)
        init();
    if(!h_in)
        return;
    // borders
    if(idx_h < IMG_H / 4 || idx_h >= 3 * IMG_H / 4 || idx_w < IMG_W / 4 || idx_w >= 3 * IMG_W / 4)
    {
        idx_w++;
        return;
    }
    if(idx_h == IMG_H / 4 && idx_w == IMG_W / 4)
        start_writing = 1;
    unsigned char px = p_in;
    // buffer filling
    buff[(idx_h - IMG_H / 4) * IMG_W / 2 + idx_w - IMG_W / 4] = px;
    idx_w++;
}

void ZOOM::write_stream()
{
    while(1)
    {
        h_out = 0;
        v_out = 0;
        while(!start_writing)
            wait();
        h_out = 1;
        v_out = 1;
        while(idx_h_write != IMG_H)
        {
            p_out = buff[(int)(idx_h_write / 2) * IMG_W / 2 + (int)(idx_w_write / 2)];
            idx_w_write++;
            wait();
            if(idx_w_write == IMG_W)
            {
                h_out = 0;
                idx_w_write = 0;
                idx_h_write++;
                for(int i = 0; i < 154; i++)
                    wait();
                h_out = 1;
            }
            if(idx_h_write == 3)
                v_out = 0;
        }
        start_writing = 0;
        init_write();
    }
}
