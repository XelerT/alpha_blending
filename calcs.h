#ifndef CALCS_H
#define CALCS_H

#include "graphics.h"

struct floating_img_t {
        unsigned int width   = 0;
        unsigned int height  = 0;
                 int start_x = 0;
                 int start_y = 0;
};

void slow_blend_imgs (sf::Image *new_img, sf::Image *front_img, sf::Image *back_img, floating_img_t floating_img);
void avx_blend_imgs  (sf::Image *new_img, sf::Image *front_img, sf::Image *back_img, floating_img_t floating_img);

#endif /*CALCS_H*/
