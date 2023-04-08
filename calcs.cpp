#include <stdio.h>
#include <assert.h>
#include <emmintrin.h>
#include <immintrin.h>

#include "calcs.h"

void slow_blend_imgs (sf::Image *new_img, sf::Image *front_img, sf::Image *back_img, floating_img_t floating_img)
{
        assert(new_img);
        assert(front_img);
        assert(back_img);

        sf::Color front_pixel_color =   RED_COLOR;
        sf::Color  back_pixel_color = BLACK_COLOR;
        sf::Color       pixel_color = BLACK_COLOR;

        for (unsigned int fr_y = 0, bk_y = floating_img.start_y; fr_y < floating_img.height; fr_y++, bk_y++) {
                for (unsigned int fr_x = 0, bk_x = floating_img.start_x; fr_x < floating_img.width; fr_x++, bk_x++) {
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
}

void avx_blend_imgs (sf::Image *new_img, sf::Image *front_img, sf::Image *back_img, floating_img_t floating_img)
{
        assert(new_img);
        assert(front_img);
        assert(back_img);

        __m256i avx_FF = _mm256_set1_epi16(0xFF);
        unsigned int max_x = floating_img.width - 4;

        for (unsigned int fr_y = 0, bk_y = floating_img.start_y; fr_y < floating_img.height; fr_y++, bk_y++) {
                for (unsigned int fr_x = 0, bk_x = floating_img.start_x; fr_x < max_x; fr_x += 4, bk_x += 4) {
                        sf::Color front_pixel_color[4] = {front_img->getPixel(fr_x,     fr_y),
                                                          front_img->getPixel(fr_x + 1, fr_y),
                                                          front_img->getPixel(fr_x + 2, fr_y),
                                                          front_img->getPixel(fr_x + 3, fr_y)};

                        sf::Color back_pixel_color[4]  = {back_img->getPixel (bk_x,     bk_y),
                                                          back_img->getPixel (bk_x + 1, bk_y),
                                                          back_img->getPixel (bk_x + 2, bk_y),
                                                          back_img->getPixel (bk_x + 3, bk_y)};

                        __m256i fr = _mm256_cvtepi8_epi16(
                                        _mm_load_si128((__m128i*) front_pixel_color)
                        );
                        __m256i bk = _mm256_cvtepi8_epi16(
                                        _mm_load_si128((__m128i*) back_pixel_color)
                        );

                        __m256i maskA = _mm256_set_epi8(0x80, 14, 0x80, 14, 0x80, 14, 0x80, 14,
                                                        0x80,  6, 0x80,  6, 0x80,  6, 0x80,  6,
                                                        0x80, 14, 0x80, 14, 0x80, 14, 0x80, 14,
                                                        0x80,  6, 0x80,  6, 0x80,  6, 0x80,  6);

                        __m256i a = _mm256_shuffle_epi8(fr, maskA);

                        fr = _mm256_mullo_epi16(fr, a);
                        bk = _mm256_mullo_epi16(bk, _mm256_sub_epi16(avx_FF, a));

                        __m256i sum = _mm256_add_epi16(fr, bk);

                        __m256i maskSum = _mm256_set_epi8(15,   13,   11,    9,    7,    5,    3,    1,
                                                          0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                                                          0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                                                          15,   13,   11,    9,    7,    5,    3,    1);
                        sum = _mm256_shuffle_epi8(sum, maskSum);

                        __m128i color = _mm_add_epi8(
                                _mm256_extracti128_si256(sum, 1), _mm256_extracti128_si256(sum, 0));
                        uint32_t *pixel_color = (uint32_t*) &color;

                        for (int i = 0; i < 4; i++) {
                                new_img->setPixel(bk_x + i, bk_y, (const sf::Color&) *(pixel_color + i));
                        }
                }
        }

}
