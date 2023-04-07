#include <assert.h>
#include <SFML/System/Vector2.hpp>
#include "graphics.h"
#include "calcs.h"
#include "hub.h"

int combine_imgs (const char *front_img_way, const char *back_img_way,
                                        int window_width, int window_height, const char *header)
{
        assert(front_img_way);
        assert(back_img_way);
        assert(header);

        sf::RenderWindow window(sf::VideoMode(window_width, window_height), header);
        sf::Sprite  screen{};
        sf::Texture texture{};

        sf::Clock clock;
        sf::Time current_time = clock.getElapsedTime();
        sf::Time previous_time = current_time;
        double fps = 0.f;

        sf::Image front_img{};
        if (!front_img.loadFromFile(front_img_way))
                return LOAD_IMG_ERR;

        sf::Image back_img{};
        if (!back_img.loadFromFile(back_img_way))
                return LOAD_IMG_ERR;

        sf::Image new_img = back_img;

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

        sf::Event event;
        while (window.isOpen()) {
                while (window.pollEvent(event))
                        if (event.type == sf::Event::Closed) {
                                window.close();
                        }
                blend_imgs(&new_img, &front_img, &back_img, front_img_size.x, front_img_size.y, 250, 200);

                texture.loadFromImage(new_img);
                screen.setTexture(texture);
                window.draw(screen);
                window.display();

                current_time = clock.getElapsedTime();
                fps = 1.0f / (current_time.asSeconds() - previous_time.asSeconds());

                printf("fps = %lf\n", fps);
                previous_time = current_time;
        }
        return 0;
}
