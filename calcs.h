#ifndef CALCS_H
#define CALCS_H

#include "graphics.h"

int blend_imgs (sf::Image *new_img, sf::Image *front_img, sf::Image *back_img,
                int front_img_width, int front_img_height, int start_x, int start_y);

#endif /*CALCS_H*/
