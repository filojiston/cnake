#include "food.h"

Food *create_food(int x, int y, int size, int scale)
{
    Food *new_food = (Food *)malloc(sizeof(Food));
    SDL_Rect food_rect;
    food_rect.h = food_rect.w = size;
    food_rect.x = x * scale;
    food_rect.y = y * scale;
    new_food->food_cell = food_rect;
    return new_food;
}

void destroy_food(Food *food)
{
    free(food);
}

void draw_food(SDL_Renderer *renderer, Food *food)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &(food->food_cell));
}
