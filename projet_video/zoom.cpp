#include <cstdio>
#include <sstream>
#include <iomanip>
#include "zoom.h"

unsigned char ZOOM::getBuff(int idx)
{
    return buff[(idx + IMG_W) % IMG_W];
}

unsigned char ZOOM::getWriteBuff(int idx)
{
    return write_buff[(idx + IMG_W / 2) % (IMG_W / 2)];
}

void ZOOM::init()
{
    idx_h = 0;
}

void ZOOM::init_write()
{
    idx_w_write = 0;
    idx_h_write = 0;
    start_writing = 0;
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
    if(idx_h < IMG_H / 4 || idx_h >= 3 * IMG_H / 4)
        return;
    printf("idx_h: %d, IMG_H: %d\n", idx_h, IMG_H);
    /*
    unsigned char px = p_in;
    // buffer filling
    buff[idx_buff] = px;
    if(++idx_buff == SIZE_BUFF)
        idx_buff = 0;
    // start writing
    if(idx_h == 1 && idx_w == 1)
        start_writing = 1;
    // image filtering
    if(idx_h > 1 || (idx_h == 1 && idx_w > 0))
    {
        write_buff[idx_write_buff] = getBuff(idx_buff - IMG_W - 2);
        if(idx_w > 1 && idx_h > 1)
        {
            // pixel filtered value
            int value = getBuff(start_buff) * filter[0];
            value += getBuff(start_buff + 1) * filter[1];
            value += getBuff(start_buff + 2) * filter[2];
            value += getBuff(start_buff + IMG_W) * filter[3];
            value += getBuff(start_buff + IMG_W + 1) * filter[4];
            value += getBuff(start_buff + IMG_W + 2) * filter[5];
            value += getBuff(start_buff + 2 * IMG_W) * filter[6];
            value += getBuff(start_buff + 2 * IMG_W + 1) * filter[7];
            value += getBuff(start_buff + 2 * IMG_W + 2) * filter[8];
            write_buff[idx_write_buff] = value;
        }
        if(idx_w != 0)
        {
            if(++idx_write_buff >= SIZE_BUFF)
                idx_write_buff = 0;
            if(idx_h > 2 || (idx_h == 2 && idx_w > 1))
                if(++start_buff == SIZE_BUFF)
                    start_buff = 0;
        }
        if(idx_w == IMG_W - 1)
        {
            write_buff[idx_write_buff] = getBuff(idx_buff + 1 - IMG_W - 2);
            if(++idx_write_buff >= SIZE_BUFF)
                idx_write_buff = 0;
            if(idx_h > 2 || (idx_h == 2 && idx_w > 1))
                if(++start_buff == SIZE_BUFF)
                    start_buff = 0;
        }
    }*/
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
        // code
        start_writing = 0;
        init_write();
    }
}
