#pragma once

#include <SDL2\SDL.h>

typedef struct Food
{
    SDL_Rect food_cell;
    SDL_Texture *food_texture;
    int xpos;
    int ypos;
} Food;

typedef struct Snake Snake;

Food *create_food(int x, int y);
void set_food_texture(Food *food, SDL_Renderer *renderer, const char *tex_path);
void destroy_food(Food *food);
void draw_food(SDL_Renderer *renderer, Food *food);
void update_food(Food *food, Snake *snake);
