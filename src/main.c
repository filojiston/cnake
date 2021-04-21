#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>
#include <time.h>

#include "snake.h"
#include "food.h"
#include "constants.h"

int init_SDL();
SDL_Window *create_window();

int handle_input();
void draw_grid();

void pause_game(int *paused);

SDL_Texture *set_score_texture(SDL_Renderer *renderer, SDL_Rect *score_rect, int score);
SDL_Texture *set_pause_texture(SDL_Renderer *renderer, SDL_Rect *pause_rect);

int main(int argc, char *args[])
{
    srand(time(NULL));

    int running = TRUE;
    int paused = FALSE;

    Snake *snake = create_snake(13, 12);
    Food *food = create_food(20, 20);

    if (!init_SDL())
        return 1;

    SDL_Window *window = create_window();
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Rect score_rect;
    SDL_Rect paused_rect;
    SDL_Texture *score_texture = set_score_texture(renderer, &score_rect, snake->size);
    SDL_Texture *paused_texture = set_pause_texture(renderer, &paused_rect);

    // set_snake_texture(snake, renderer, NULL, NULL, NULL);
    set_snake_texture(snake, renderer, "res\\head.png", "res\\body.png", "res\\tail.png");
    // set_snake_texture(snake, renderer, "res\\head.png", NULL, "res\\tail.png");
    // set_food_texture(food, renderer, NULL);
    set_food_texture(food, renderer, "res\\food.png");

    while (running)
    {
        SDL_Delay(100);

        // handle inputs
        running = handle_input(snake, &paused);

        if (!paused)
        {
            // update game
            update_snake(snake);
            if (eat_food(snake, food))
            {
                update_food(food, snake);
                score_texture = set_score_texture(renderer, &score_rect, snake->size);
            }
        }

        // clear window
        SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
        SDL_RenderClear(renderer);

        // draw_grid(renderer);
        draw_snake(renderer, snake);
        draw_food(renderer, food);

        SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
        if (paused)
        {
            SDL_RenderCopy(renderer, paused_texture, NULL, &paused_rect);
        }

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

    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
    {
        printf("SDL_image could not initialize! SDL_Image Error: %s\n", IMG_GetError());
    }

    return TRUE;
}

SDL_Window *create_window()
{
    return SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
}

int handle_input(Snake *snake, int *paused)
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
            if (!(*paused))
                move_snake(snake, UP);
            break;
        case SDLK_DOWN:
            if (!(*paused))
                move_snake(snake, DOWN);
            break;
        case SDLK_LEFT:
            if (!(*paused))
                move_snake(snake, LEFT);
            break;
        case SDLK_RIGHT:
            if (!(*paused))
                move_snake(snake, RIGHT);
            break;
        case SDLK_p:
            pause_game(paused);
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

SDL_Texture *set_score_texture(SDL_Renderer *renderer, SDL_Rect *score_rect, int score)
{
    char str[100];
    sprintf(str, "score: %d", score);
    TTF_Font *font = TTF_OpenFont("fonts\\arial.ttf", 18);
    SDL_Color text_color = {0, 0, 0, 255};
    SDL_Surface *text_surface = TTF_RenderText_Shaded(font, str, text_color, BACKGROUND_COLOR);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    score_rect->x = 0;
    score_rect->y = 0;
    score_rect->w = text_surface->w;
    score_rect->h = text_surface->h;

    SDL_FreeSurface(text_surface);

    return text_texture;
}

SDL_Texture *set_pause_texture(SDL_Renderer *renderer, SDL_Rect *pause_rect)
{
    TTF_Font *font = TTF_OpenFont("fonts\\arial.ttf", 30);
    SDL_Color text_color = {0, 0, 0, 255};
    SDL_Surface *pause_surface = TTF_RenderText_Shaded(font, "Game Paused.", text_color, BACKGROUND_COLOR);
    SDL_Texture *pause_texture = SDL_CreateTextureFromSurface(renderer, pause_surface);

    pause_rect->x = (SCREEN_WIDTH - pause_surface->w) * 0.5;
    pause_rect->y = (SCREEN_HEIGHT - pause_surface->h) * 0.5;
    pause_rect->w = pause_surface->w;
    pause_rect->h = pause_surface->h;

    SDL_FreeSurface(pause_surface);

    return pause_texture;
}

void pause_game(int *paused)
{
    if (*(paused) == FALSE)
        *paused = TRUE;
    else
        *paused = FALSE;
}
