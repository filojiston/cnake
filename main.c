#include <SDL.h>
#include <stdio.h>
#include <time.h>

#include "snake.h"
#include "food.h"
#include "constants.h"

void init_SDL();
SDL_Window *create_window();

int handle_input();
void draw_grid();

int main(int argc, char *args[])
{
    srand(time(NULL));

    int running = TRUE;

    Snake *snake = create_snake(13, 12);
    Food *food = create_food(30, 30);

    init_SDL();
    SDL_Window *window = create_window();
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    while (running)
    {
        SDL_Delay(100);

        // handle inputs
        running = handle_input(snake);

        // update game
        update_snake(snake);
        if (eat_food(snake, food->xpos, food->ypos))
        {
            update_food(food, snake);
        }

        // clear window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // render game
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

    // free allocated memory
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
}

SDL_Window *create_window()
{
    return SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
}

int handle_input(Snake *snake)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        return FALSE;
        break;
        // TODO input handling goes below
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            move_snake(snake, UP);
            break;
        case SDLK_DOWN:
            move_snake(snake, DOWN);
            break;
        case SDLK_LEFT:
            move_snake(snake, LEFT);
            break;
        case SDLK_RIGHT:
            move_snake(snake, RIGHT);
            break;
        }
    }

    return TRUE;
}

void draw_grid(SDL_Renderer *renderer)
{
    // draw vertical lines
    for (int i = 1; i < GRID_COUNT; i++)
    {
        SDL_RenderDrawLine(renderer, i * SCALE, 0, i * SCALE, SCREEN_HEIGHT);
    }
    // draw horizontal lines
    for (int i = 1; i < GRID_COUNT; i++)
    {
        SDL_RenderDrawLine(renderer, 0, i * SCALE, SCREEN_WIDTH, i * SCALE);
    }
    return;
}
