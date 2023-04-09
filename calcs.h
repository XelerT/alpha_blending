#ifndef CALCS_H
#define CALCS_H

#include "graphics.h"

struct floating_img_t {
        unsigned int width   = 0;
        unsigned int height  = 0;
                 int start_x = 0;
                 int start_y = 0;
};

struct my_pixel_t {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        uint8_t a = 0;
};

void slow_blend_imgs (my_pixel_t *new_img, my_pixel_t *front_img, my_pixel_t *back_img,
                                                 floating_img_t floating_img, int back_width);
void avx_blend_imgs (my_pixel_t *new_img, my_pixel_t *front_img, my_pixel_t *back_img,
                                                 floating_img_t floating_img, int back_width);
#endif /*CALCS_H*/
