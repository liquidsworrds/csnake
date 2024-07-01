#include "snake.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#define WINDOW_X 0 
#define WINDOW_Y 0 
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

#define GRID_SIZE 20
#define GRID_DIM 800

enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT
};

struct snake {
    int x;
    int y;
    int dir;

    struct snake *next;
};

typedef struct snake Snake;

Snake *head;
Snake *tail;

void init_snake() {
    Snake *new = malloc(sizeof(Snake));
    new->x = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new->y = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new->dir = SNAKE_UP;
    new->next = NULL;
    head = new;
    tail = new;

    return;
}

void grow_snake() {
    Snake *new = malloc(sizeof(Snake));
    new->x = tail->x;
    new->y = tail->y - 1;
    new->dir = tail->dir;

    new->next = NULL;
    tail->next = new;

    tail = new;

    return;
}


void render_grid(SDL_Renderer *renderer, int x, int y) {

    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);
    int cell_size = GRID_DIM / GRID_SIZE;

    SDL_Rect cell;

    cell.w = cell_size;
    cell.h = cell_size;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cell.x = x + (i * cell_size);
            cell.y = y + (j * cell_size);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
    return;
}

void render_snake(SDL_Renderer *renderer, int x, int y) {
    
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);
    int seg_size =  GRID_DIM / GRID_SIZE;
    SDL_Rect seg;
    seg.w = seg_size;
    seg.h = seg_size;
    
    Snake *track = head;

    while(track != NULL) {
        seg.x = x + track->x * seg_size;
        seg.y = y + track->y * seg_size;
        SDL_RenderFillRect(renderer, &seg);
        track = track->next;
    }

    return;
}

int main() {

    init_snake();
    grow_snake();
    grow_snake();
    grow_snake();
    grow_snake();

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


    int grid_x = (WINDOW_WIDTH / 2) - (GRID_DIM / 2);
    int grid_y = (WINDOW_HEIGHT / 2) - (GRID_DIM / 2);

    bool quit = false;
    SDL_Event event;

    while(!quit) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                    }
            }
        }

        SDL_RenderClear(renderer);
        //Render loop start
        render_grid(renderer, grid_x, grid_y);
        render_snake(renderer, grid_x, grid_y);
        //Render loop end
        SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 255);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
                                               

    return 0;
}
