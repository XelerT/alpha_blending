#include <stdio.h>

#include "hub.h"
#include "graphics.h"
#include "calcs.h"

int main (int argc, char *argv[])
{
        if (setvbuf(stdout, nullptr, _IONBF, 0))
                return VBUF_ERR;

        if (argc != 3)
                printf("You need to enter 2 arguments(Way to the front and back picture)\n");

        combine_imgs(argv[1], argv[2], 800, 600, "Some cats on the table.");

        return 0;
}
