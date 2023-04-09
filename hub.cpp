#include <assert.h>
#include "graphics.h"
#include "calcs.h"
#include "hub.h"

static const int N_TEST_ITERATIONS = 10000;

int combine_imgs (const char *front_img_way, const char *back_img_way,
                                        int window_width, int window_height, const char *header, bool test_mode)
{
        assert(front_img_way);
        assert(back_img_way);
        assert(header);

        sf::Sprite  screen{};
        sf::Texture texture{};

        sf::Clock clock;
        sf::Time current_time = clock.getElapsedTime();
        sf::Time previous_time = current_time;
        double fps = 0.f;

        sf::Image front_img{};
        if (!front_img.loadFromFile(front_img_way))
                return LOAD_IMG_ERR;
        my_pixel_t *front_pixels = get_img_pixels(&front_img);

        sf::Image back_img{};
        if (!back_img.loadFromFile(back_img_way))
                return LOAD_IMG_ERR;
        my_pixel_t *back_pixels = get_img_pixels(&back_img);

        sf::Image new_img = back_img;
        my_pixel_t *new_pixels = get_img_pixels(&new_img);

        sf::Vector2u front_img_size{};
        front_img_size = front_img.getSize();

        sf::Vector2u back_img_size{};
        back_img_size = back_img.getSize();

        if (front_img_size.x > back_img_size.x) {
                fprintf(stderr, "Your width of the front image is greater than back image.\n");
                return IMG_SIZE_ERROR;
        }
        if (front_img_size.y > back_img_size.y) {
                fprintf(stderr, "Your height of the front image is greater than back image.\n");
                return IMG_SIZE_ERROR;
        }

        floating_img_t fl_img = {
                .width   = front_img_size.x,
                .height  = front_img_size.y,
                .start_x = 250,
                .start_y = 200
        };

        if (!test_mode) {
                sf::RenderWindow window(sf::VideoMode(window_width, window_height), header);
                sf::Event event;
                while (window.isOpen()) {
                        while (window.pollEvent(event))
                                if (event.type == sf::Event::Closed) {
                                        window.close();
                                }
                        avx_blend_imgs(new_pixels, front_pixels, back_pixels, fl_img, back_img_size.x);
                        my_pixels2image(new_pixels, &new_img);

                        texture.loadFromImage(new_img);
                        screen.setTexture(texture);
                        window.draw(screen);
                        window.display();

                        current_time = clock.getElapsedTime();
                        fps = 1.0f / (current_time.asSeconds() - previous_time.asSeconds());

                        printf("fps = %lf\n", fps);
                        previous_time = current_time;
                }
        } else {
                sf::Time start_time = clock.getElapsedTime();
                for (int  i = 0; i < N_TEST_ITERATIONS; i++) {
                        slow_blend_imgs(new_pixels, front_pixels, back_pixels, fl_img, back_img_size.x);
                }
                sf::Time finish_time = clock.getElapsedTime();

                float delta_slow = finish_time.asSeconds() - start_time.asSeconds();
                printf("Time for %d iterations is %f\n", N_TEST_ITERATIONS, delta_slow);

                start_time = clock.getElapsedTime();
                for (int i = 0; i < N_TEST_ITERATIONS; i++) {
                        avx_blend_imgs(new_pixels, front_pixels, back_pixels, fl_img, back_img_size.x);
                }
                finish_time = clock.getElapsedTime();

                float delta_avx = finish_time.asSeconds() - start_time.asSeconds();
                printf("Time for %d avx iterations is %f\n", N_TEST_ITERATIONS, delta_avx);

                printf("Without avx optimisation time to calculate is %f slower.\n", delta_slow / delta_avx);
        }
        return 0;
}

my_pixel_t* get_img_pixels (sf::Image *image)
{
        assert(image);

        sf::Vector2u img_size{};
        img_size = image->getSize();

        my_pixel_t *pixels = (my_pixel_t*) calloc(img_size.x * img_size.y, sizeof(my_pixel_t));
        if (!pixels)
                return nullptr;
        my_pixel_t *new_pixels = pixels;

        for (unsigned int y = 0; y < img_size.y; y++)
                for (unsigned int x = 0; x < img_size.x; x++, new_pixels++) {
                        sf::Color color = image->getPixel(x, y);
                        new_pixels->r = (sf::Uint8) color.r;
                        new_pixels->g = (sf::Uint8) color.g;
                        new_pixels->b = (sf::Uint8) color.b;
                        new_pixels->a = (sf::Uint8) color.a;
                }
        return pixels;
}

void my_pixels2image(my_pixel_t *new_pixels, sf::Image *image)
{
        assert(new_pixels);
        assert(image);

        sf::Color color{};
        sf::Vector2u img_size{};
        img_size = image->getSize();

        for (unsigned int y = 0; y < img_size.y; y++)
                for (unsigned int x = 0; x < img_size.x; x++, new_pixels++) {
                        color.r = new_pixels->r;
                        color.g = new_pixels->g;
                        color.b = new_pixels->b;
                        color.a = new_pixels->a;

                        image->setPixel(x, y, color);
                }
}
