#include <stdio.h>
#include <cstdint>
#include <SFML/Graphics.hpp>

#include "hub.h"
#include "graphics.h"
#include "calcs.h"

int main (int argc, char *argv[])
{
        if (setvbuf(stdout, nullptr, _IONBF, 0))
                return VBUF_ERR;

        if (argc != 4)
                printf("You need to enter 3 arguments(Way to the front and back picture) and mode(1 - test mode)\n");

        combine_imgs(argv[1], argv[2], 800, 600, "Some cats on the table.", (*argv[3] - '0'));

        return 0;
}
