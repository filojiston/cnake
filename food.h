#pragma once

#include <SDL.h>
#include <stdlib.h>
#include "constants.h"

typedef struct Food
{
    SDL_Rect food_cell;
} Food;

Food *create_food(int x, int y);
void destroy_food(Food *food);
void draw_food(SDL_Renderer *renderer, Food *food);
