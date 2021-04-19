#include "snake.h"

// create a snake at given position
Snake *create_snake(int x, int y)
{
    Snake *snake = (Snake *)malloc(sizeof(Snake));

    // create snake's head
    snake->head = new_node(x, y);
    snake->head->next = new_node(x - 1, y);
    snake->head->next->next = new_node(x - 2, y);
    snake->tail = snake->head->next->next;
    snake->tail->prev = snake->head->next;
    snake->tail->prev->prev = snake->head;

    snake->direction = RIGHT;

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

// set snake's direction
void move_snake(Snake *s, Direction dir)
{
    // user presses same direction
    if (dir == s->direction)
        return;

    // user presses exact opposite direction
    if (dir == UP && s->direction == DOWN)
        return;
    if (dir == DOWN && s->direction == UP)
        return;
    if (dir == LEFT && s->direction == RIGHT)
        return;
    if (dir == RIGHT && s->direction == LEFT)
        return;

    // set direction
    s->direction = dir;
}

// update snake's body cell coordinates
void update_snake(Snake *s)
{
    // set snake's body positions to next cells
    LinkNode *before = s->tail;
    while (before->prev != NULL)
    {
        update_node(before, before->prev->xpos, before->prev->ypos);
        before = before->prev;
    }

    // change head's position
    switch (s->direction)
    {
    case UP:
        update_node(s->head, s->head->xpos, s->head->ypos - 1);
        break;
    case DOWN:
        update_node(s->head, s->head->xpos, s->head->ypos + 1);
        break;
    case LEFT:
        update_node(s->head, s->head->xpos - 1, s->head->ypos);
        break;
    case RIGHT:
        update_node(s->head, s->head->xpos + 1, s->head->ypos);
        break;
    }
}
