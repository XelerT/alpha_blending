#include <stdio.h>
#include <assert.h>
#include <emmintrin.h>
#include <immintrin.h>

#include "calcs.h"

int blend_imgs (sf::Image *new_img, sf::Image *front_img, sf::Image *back_img,
                int front_img_width, int front_img_height, int start_x, int start_y)
{
        assert(new_img);
        assert(front_img);
        assert(back_img);

        sf::Color front_pixel_color  =   RED_COLOR;
        sf::Color  back_pixel_color  = BLACK_COLOR;
        sf::Color       pixel_color  = BLACK_COLOR;

        for (int fr_y = 0, bk_y = start_y; fr_y < front_img_height; fr_y++, bk_y++) {
                for (int fr_x = 0, bk_x = start_x; fr_x < front_img_width; fr_x++, bk_x++) {
                        front_pixel_color = front_img->getPixel(fr_x, fr_y);
                         back_pixel_color =  back_img->getPixel(bk_x, bk_y);
                        pixel_color.r = (sf::Uint8) ((back_pixel_color.r * (255 - front_pixel_color.a) +
                                        front_pixel_color.r * front_pixel_color.a) >> 8);

                        pixel_color.g = (sf::Uint8) ((back_pixel_color.g * (255 - front_pixel_color.a) +
                                        front_pixel_color.g * front_pixel_color.a) >> 8);

                        pixel_color.b = (sf::Uint8) ((back_pixel_color.b * (255 - front_pixel_color.a) +
                                        front_pixel_color.b * front_pixel_color.a) >> 8);

                        pixel_color.a = (sf::Uint8) ((back_pixel_color.a * (255 - front_pixel_color.a) +
                                        front_pixel_color.a * front_pixel_color.a) >> 8);
                        new_img->setPixel(bk_x, bk_y, pixel_color);
                }
        }
        return 0;
}
