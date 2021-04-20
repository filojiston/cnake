#include <stdlib.h>

#include "constants.h"
#include "linknode.h"

#include "food.h"
#include "snake.h"

Food *create_food(int x, int y)
{
    Food *new_food = (Food *)malloc(sizeof(Food));
    SDL_Rect food_rect;
    food_rect.h = food_rect.w = RECT_SIZE;
    food_rect.x = x * SCALE;
    food_rect.y = y * SCALE;
    new_food->food_cell = food_rect;
    new_food->xpos = x;
    new_food->ypos = y;

    return new_food;
}

void destroy_food(Food *food)
{
    free(food);
}

void draw_food(SDL_Renderer *renderer, Food *food)
{
    SDL_SetRenderDrawColor(renderer, FOOD_COLOR.r, FOOD_COLOR.g, FOOD_COLOR.b, FOOD_COLOR.a);
    SDL_RenderFillRect(renderer, &(food->food_cell));
}

// re-locate the food when snake eats it
void update_food(Food *food, Snake *snake)
{
    int unique = TRUE;
    int rand_xpos, rand_ypos;
    LinkNode *iter = snake->head;

    do
    {
        unique = TRUE;
        // select a random position in grid
        rand_xpos = (rand() % ((GRID_COUNT - 1) - 1 + 1)) + 1;
        rand_ypos = (rand() % ((GRID_COUNT - 1) - 1 + 1)) + 1;

        // if snake is in that position, re-locate the food
        while (iter != NULL)
        {
            if (rand_xpos == iter->xpos && rand_ypos == iter->ypos)
            {
                unique = FALSE;
                break;
            }
            iter = iter->next;
        }
    } while (!unique);

    food->food_cell.x = rand_xpos * SCALE;
    food->food_cell.y = rand_ypos * SCALE;
    food->xpos = rand_xpos;
    food->ypos = rand_ypos;
}
