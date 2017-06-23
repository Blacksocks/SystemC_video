#include <cstdio>
#include <sstream>
#include <iomanip>
#include "video_out.h"

void VIDEO_OUT::read_stream()
{
    if(!reset_n)
    {
        current_image_number = 0;
        idx_w = 0;
        idx_h = 0;
        return;
    }
    if(!href && idx_w != 0)
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
    if(!href)
        return;
    unsigned char px = pixel_in;
    image.pixel[idx_w + idx_h * IMG_W] = px;
    idx_w++;
}
