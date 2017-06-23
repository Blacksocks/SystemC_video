#include <cstdio>
#include <sstream>
#include <iomanip>
#include "mean.h"

unsigned char MEAN::getBuff(int idx)
{
    while(idx > SIZE_BUFF)
        idx -= SIZE_BUFF;
    return buff[idx];
}

void MEAN::read_stream()
{
    if(!reset_n)
    {
        current_image_number = 0;
        idx_w = 0;
        idx_h = 0;
        start_buff = 0;
        idx_buff = 0;
        return;
    }
    if(!h_in && idx_w != 0)
    {
        idx_h++;
        idx_w = 0;
    }
    if(idx_h == IMG_H)
    {
        std::ostringstream name_s;
        name_s << "img_" << std::setfill('0') << std::setw(2) << current_image_number++ << "_out.png";
        cout << "Saving image: " << name_s.str() << endl;
        image_write(&image, name_s.str().c_str());
        idx_h = 0;
    }
    if(!h_in)
        return;
    unsigned char px = p_in;
    // buffer filling
    buff[idx_buff++] = px;
    if(idx_buff == SIZE_BUFF)
        idx_buff = 0;
    // border
    if(idx_h == 0 || idx_h == IMG_H - 1 || idx_w == 0 || idx_w == IMG_W - 1)
        image.pixel[idx_w + idx_h * IMG_W] = px;
    // image filtering
    if(idx_h > 2 || (idx_h == 2 && idx_w > 1))
    {
        // remove border
        if(idx_w > 1)
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
            image.pixel[(idx_w - 1) + (idx_h - 1) * IMG_W] = value / 9;
        }
        if(++start_buff == SIZE_BUFF)
            start_buff = 0;
    }
    idx_w++;
}
