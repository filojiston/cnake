#include "food.h"

Food *create_food(int x, int y)
{
    Food *new_food = (Food *)malloc(sizeof(Food));
    SDL_Rect food_rect;
    food_rect.h = food_rect.w = RECT_SIZE;
    food_rect.x = x * SCALE;
    food_rect.y = y * SCALE;
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
