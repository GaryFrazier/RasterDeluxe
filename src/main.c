#define SDL_MAIN_HANDLED

#include <stdio.h>
#include "SDL/SDL.h"

#define UNUSED(x) (void)(x)

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    while (1) {
    }
}
