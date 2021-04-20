#pragma once

#include <SDL.h>
#include <stdlib.h>
#include "constants.h"
#include "linknode.h"
#include "snake.h"
typedef struct Food
{
    SDL_Rect food_cell;
    int xpos;
    int ypos;
} Food;

Food *create_food(int x, int y);
void destroy_food(Food *food);
void draw_food(SDL_Renderer *renderer, Food *food);
void update_food(Food *food, Snake *snake);
