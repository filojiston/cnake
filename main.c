#include <SDL.h>
#include <stdio.h>

#include "snake.h"
#include "food.h"

#define TRUE 1
#define FALSE 0

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SCALE = 20;
const int RECT_SIZE = 21;
const char *TITLE = "Snake Game";

void init_SDL();
SDL_Window *create_window();

void draw_grid();

int main(int argc, char *args[])
{
    int running = TRUE;

    Snake *snake = create_snake(13, 12, RECT_SIZE, SCALE);
    Food *food = create_food(30, 30, RECT_SIZE, SCALE);

    init_SDL();
    SDL_Window *window = create_window();
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    while (running)
    {
        SDL_Delay(10);
        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            running = FALSE;
            break;
            // TODO input handling goes below
        }

        // clear window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // TODO rendering goes below
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        draw_grid(renderer);

        draw_snake(renderer, snake);
        draw_food(renderer, food);

        SDL_RenderPresent(renderer);
    }

    // cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    destroy_snake(snake);
    destroy_food(food);

    return 0;
}

void init_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    printf("SDL successfully initialized!\n");
}

SDL_Window *create_window()
{
    return SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
}

void draw_grid(SDL_Renderer *renderer)
{
    // draw vertical lines
    for (int i = 1; i < SCREEN_HEIGHT / SCALE; i++)
    {
        SDL_RenderDrawLine(renderer, i * SCALE, 0, i * SCALE, SCREEN_HEIGHT);
    }
    // draw horizontal lines
    for (int i = 1; i < SCREEN_WIDTH / SCALE; i++)
    {
        SDL_RenderDrawLine(renderer, 0, i * SCALE, SCREEN_WIDTH, i * SCALE);
    }
    return;
}
