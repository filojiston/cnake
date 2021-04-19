#include "snake.h"

// create a snake at given position
Snake *create_snake(int x, int y, int size, int scale)
{
    Snake *snake = (Snake *)malloc(sizeof(Snake));

    // create snake's head
    snake->head = new_node(x * scale, y * scale, size);
    snake->head->next = new_node((x - 1) * scale, (y * scale), size);
    snake->head->next->next = new_node((x - 2) * scale, (y * scale), size);
    snake->tail = snake->head->next->next;

    return snake;
}

void destroy_snake(Snake *snake)
{
    free(snake);
}

void draw_snake(SDL_Renderer *renderer, Snake *s)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    LinkNode *iter = s->head;

    while (iter != NULL)
    {
        SDL_RenderFillRect(renderer, &(iter->body_cell));
        iter = iter->next;
    }
}
