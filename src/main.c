#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <stdio.h>
#include <time.h>

#include "snake.h"
#include "food.h"
#include "constants.h"

int init_SDL();
SDL_Window *create_window();

int handle_input();
void draw_grid();

SDL_Texture *set_score_texture(SDL_Renderer *renderer, SDL_Rect *text_rect, int score);

int main(int argc, char *args[])
{
    srand(time(NULL));

    int running = TRUE;

    Snake *snake = create_snake(13, 12);
    Food *food = create_food(30, 30);

    if (!init_SDL())
        return 1;

    SDL_Window *window = create_window();
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Rect text_rect;
    SDL_Texture *score_texture = set_score_texture(renderer, &text_rect, snake->size);

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
            score_texture = set_score_texture(renderer, &text_rect, snake->size);
        }

        // clear window
        SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
        SDL_RenderClear(renderer);

        // draw_grid(renderer);
        draw_snake(renderer, snake);
        draw_food(renderer, food);

        SDL_RenderCopy(renderer, score_texture, NULL, &text_rect);

        SDL_RenderPresent(renderer);
    }

    // cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(score_texture);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // free allocated memory
    destroy_snake(snake);
    destroy_food(food);

    return 0;
}

int init_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return FALSE;
    }

    return TRUE;
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

SDL_Texture *set_score_texture(SDL_Renderer *renderer, SDL_Rect *text_rect, int score)
{
    char str[100];
    sprintf(str, "score: %d", score);
    TTF_Font *font = TTF_OpenFont("fonts\\arial.ttf", 18);
    SDL_Color text_color = {0, 0, 0, 255};
    SDL_Surface *text_surface = TTF_RenderText_Shaded(font, str, text_color, BACKGROUND_COLOR);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    text_rect->x = 0;
    text_rect->y = 0;
    text_rect->w = text_surface->w;
    text_rect->h = text_surface->h;

    SDL_FreeSurface(text_surface);

    return text_texture;
}
