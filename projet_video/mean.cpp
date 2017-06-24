#include <cstdio>
#include <sstream>
#include <iomanip>
#include "mean.h"

unsigned char MEAN::getBuff(int idx)
{
    return buff[(idx + SIZE_BUFF) % SIZE_BUFF];
}

unsigned char MEAN::getWriteBuff(int idx)
{
    return write_buff[(idx + SIZE_BUFF) % SIZE_BUFF];
}

void MEAN::init()
{
    idx_h = 0;
    start_buff = 0;
    idx_buff = 0;
}

void MEAN::init_write()
{
    start_write_buff = 0;
    idx_write_buff = 0;
    idx_w_write = 0;
    idx_h_write = 0;
    start_writing = 0;
}

void MEAN::read_stream()
{
    if(!reset_n)
    {
        idx_w = 0;
        idx_h = 0;
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
    {
        // send all buffer into write_buffer
        while(start_buff != idx_buff)
        {
            write_buff[idx_write_buff] = getBuff(start_buff + IMG_W + 1);
            if(++idx_write_buff >= SIZE_BUFF)
                idx_write_buff = 0;
            if(++start_buff >= SIZE_BUFF)
                start_buff = 0;
        }
        init();
    }
    if(!h_in)
        return;
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
            // pixel mean value
            int value = getBuff(start_buff);
            value += getBuff(start_buff + 1);
            value += getBuff(start_buff + 2);
            value += getBuff(start_buff + IMG_W);
            value += getBuff(start_buff + IMG_W + 1);
            value += getBuff(start_buff + IMG_W + 2);
            value += getBuff(start_buff + 2 * IMG_W);
            value += getBuff(start_buff + 2 * IMG_W + 1);
            value += getBuff(start_buff + 2 * IMG_W + 2);
            write_buff[idx_write_buff] = value / 9;
        }
        if(++idx_write_buff >= SIZE_BUFF)
            idx_write_buff = 0;
        if(idx_h > 2 || (idx_h == 2 && idx_w > 1))
            if(++start_buff == SIZE_BUFF)
                start_buff = 0;
    }
    idx_w++;
}

void MEAN::write_stream()
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
            p_out = getWriteBuff(start_write_buff++);
            if(start_write_buff == SIZE_BUFF)
                start_write_buff = 0;
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
