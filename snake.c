#include "snake.h"

#define WINDOW_X 0 
#define WINDOW_Y 0 
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_INIT_VIDEO < 0) {
        fprintf(stderr, "ERROR: SDL_INIT_VIDEO %s", SDL_GetError());
    }

    window = SDL_CreateWindow(
            "Snake",
            WINDOW_X,
            WINDOW_Y,
            WINDOW_HEIGHT,
            WINDOW_WIDTH,
            SDL_WINDOW_BORDERLESS
    );


    if (!window) {
        fprintf(stderr, "ERROR: SDL_CreateWindow %s", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        fprintf(stderr, "ERROR: SDL_CreateRenderer %s", SDL_GetError());
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
                                               

    return 0;
}
