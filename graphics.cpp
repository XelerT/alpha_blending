#include <assert.h>
#include <emmintrin.h>
#include <immintrin.h>

#include "graphics.h"

#define check_button(stdn_name, my_name)         if (sf::Keyboard::isKeyPressed(sf::Keyboard::stdn_name))    \
                                                        return my_name;

int get_pressed_key ()
{
        check_button(Left,    LEFT_BUTTON);
        check_button(Right,  RIGHT_BUTTON);
        check_button(Up,        UP_BUTTON);
        check_button(Down,    DOWN_BUTTON);
        check_button(Add,      ADD_BUTTON);
        check_button(Subtract, SUB_BUTTON);

        return 0;
}
#undef check_button

void change_scale (int pressed_button, coordinates_t *coords)
{
        switch (pressed_button) {
        case 0:
                return;
        case LEFT_BUTTON:
                coords->start_x -= 10;
                break;
        case RIGHT_BUTTON:
                coords->start_x += 10;
                break;
        case UP_BUTTON:
                coords->start_y -= 10;
                break;
        case DOWN_BUTTON:
                coords->start_y += 10;
                break;
        case ADD_BUTTON:
                coords->max_x *= 0.9f;
                coords->max_y *= 0.9f;
                break;
        case SUB_BUTTON:
                coords->max_x *= 1.1f;
                coords->max_y *= 1.1f;
                break;
        default:
                assert(0 && "UNKNOWN BUTTON\n");
        }

        return;
}
