#define SDL_MAIN_HANDLED

#include <stdio.h>
#include "external/SDL_FontCache/SDL_Fontcache.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define UNUSED(x) (void)(x)

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    int quit = 0;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // Init font
    FC_Font* font = FC_CreateFont();  
    FC_LoadFont(font, renderer, "Courier New.ttf", 20, FC_MakeColor(0,0,0,255), TTF_STYLE_NORMAL);

    long currentTick = SDL_GetTicks64();
    long frameRate = 0;

    // Main loop
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = 1;
            }
        }

        // Update tick info
        long newTick = SDL_GetTicks64();
        long numTicksInFrame = newTick - currentTick;

        if (numTicksInFrame > 0) {
            frameRate = 1000 / (newTick - currentTick); // 1000 ms / ms in last frame
        } else {
            frameRate = 0;
        }

        FC_Draw(font, renderer, 0, 0, "This is %s.\n It works.", "example text");

        currentTick = newTick;
        
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    FC_FreeFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
