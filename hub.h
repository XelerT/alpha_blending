#ifndef HUB_H
#define HUB_H

#include "calcs.h"

#include <SFML/System/Vector2.hpp>

int combine_imgs (const char *front_img_way, const char *back_img_way,
                                                 int window_width, int window_height, const char *header, bool test_mode);
my_pixel_t* get_img_pixels (sf::Image *image);
void my_pixels2image(my_pixel_t *new_pixels, sf::Image *image);

#endif /*HUB_H*/
