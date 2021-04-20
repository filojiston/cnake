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
    LinkNode *iter = snake->head;
    while (iter != NULL)
    {
        destroy_node(iter);
        iter = iter->next;
    }
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

int eat_food(Snake *s, int xpos, int ypos)
{
    // if snake's head position is same with food's, snake will eat it
    if ((s->head->xpos == xpos) && (s->head->ypos == ypos))
    {
        LinkNode *before_tail = s->tail->prev;
        LinkNode *node;
        if (before_tail->xpos == s->tail->xpos)
        {
            if (s->direction == UP)
            {
                node = new_node(before_tail->xpos, before_tail->ypos + 1);
            }
            else if (s->direction == DOWN)
            {
                node = new_node(before_tail->xpos, before_tail->ypos - 1);
            }
        }
        else if (before_tail->ypos == s->tail->ypos)
        {
            if (s->direction == LEFT)
            {
                node = new_node(before_tail->xpos + 1, before_tail->ypos);
            }
            else if (s->direction == RIGHT)
            {
                node = new_node(before_tail->xpos - 1, before_tail->ypos);
            }
        }

        s->tail->next = node;
        node->prev = s->tail;
        s->tail = node;
        return TRUE;
    }

    return FALSE;
}
