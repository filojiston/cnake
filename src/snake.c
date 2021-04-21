#include <stdlib.h>
#include <SDL2\SDL_image.h>

#include "constants.h"
#include "snake.h"
#include "food.h"

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

    snake->size = 3;

    snake->head_texture = NULL;
    snake->body_texture = NULL;
    snake->tail_texture = NULL;

    snake->direction = RIGHT;

    return snake;
}

void set_snake_texture(Snake *s, SDL_Renderer *renderer, const char *p_head, const char *p_body, const char *p_tail)
{
    if (p_head != NULL)
    {
        s->head_texture = IMG_LoadTexture(renderer, p_head);
    }
    if (p_body != NULL)
    {
        s->body_texture = IMG_LoadTexture(renderer, p_body);
    }
    if (p_tail != NULL)
    {
        s->tail_texture = IMG_LoadTexture(renderer, p_tail);
    }
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
    SDL_SetRenderDrawColor(renderer, SNAKE_COLOR.r, SNAKE_COLOR.g, SNAKE_COLOR.b, SNAKE_COLOR.a);
    LinkNode *iter = s->head->next;

    // draw head
    if (s->head_texture == NULL)
    {
        SDL_RenderFillRect(renderer, &(s->head->body_cell));
    }
    else
    {
        switch (s->direction)
        {
        case UP:
            SDL_RenderCopy(renderer, s->head_texture, NULL, &(s->head->body_cell));
            break;
        case DOWN:
            SDL_RenderCopyEx(renderer, s->head_texture, NULL, &(s->head->body_cell), 180, NULL, SDL_FLIP_NONE);
            break;
        case LEFT:
            SDL_RenderCopyEx(renderer, s->head_texture, NULL, &(s->head->body_cell), 270, NULL, SDL_FLIP_NONE);
            break;
        case RIGHT:
            SDL_RenderCopyEx(renderer, s->head_texture, NULL, &(s->head->body_cell), 90, NULL, SDL_FLIP_NONE);
            break;
        }
    }

    // draw body
    if (s->body_texture == NULL)
    {
        while (iter->next != NULL)
        {
            SDL_RenderFillRect(renderer, &(iter->body_cell));
            iter = iter->next;
        }
    }
    else
    {
        while (iter->next != NULL)
        {
            SDL_RenderCopy(renderer, s->body_texture, NULL, &(iter->body_cell));
            iter = iter->next;
        }
    }

    // draw tail
    if (s->tail_texture == NULL)
    {
        SDL_RenderFillRect(renderer, &(s->tail->body_cell));
    }
    else
    {
        // SDL_RenderCopy(renderer, s->tail_texture, NULL, &(s->tail->body_cell));
        LinkNode *before_tail = s->tail->prev;

        // moving vertically
        if (before_tail->xpos == s->tail->xpos)
        {
            int diff = (s->tail->ypos - before_tail->ypos);
            if (diff < 0) // rotate 180
            {
                SDL_RenderCopyEx(renderer, s->tail_texture, NULL, &(s->tail->body_cell), 180, NULL, SDL_FLIP_NONE);
            }
            else
            {
                SDL_RenderCopy(renderer, s->tail_texture, NULL, &(s->tail->body_cell));
            }
        }
        else
        {
            int diff = (s->tail->xpos - before_tail->xpos);
            if (diff < 0) // rotate 90
            {
                SDL_RenderCopyEx(renderer, s->tail_texture, NULL, &(s->tail->body_cell), 90, NULL, SDL_FLIP_NONE);
            }
            else // rotate 270
            {
                SDL_RenderCopyEx(renderer, s->tail_texture, NULL, &(s->tail->body_cell), 270, NULL, SDL_FLIP_NONE);
            }
        }
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
        (s->head->ypos)--;
        if (s->head->ypos < 0)
            s->head->ypos = GRID_COUNT - 1;
        break;
    case DOWN:
        (s->head->ypos)++;
        if (s->head->ypos > GRID_COUNT - 1)
            s->head->ypos = 0;
        break;
    case LEFT:
        (s->head->xpos)--;
        if (s->head->xpos < 0)
            s->head->xpos = GRID_COUNT - 1;
        break;
    case RIGHT:
        (s->head->xpos)++;
        if (s->head->xpos > GRID_COUNT - 1)
            s->head->xpos = 0;
        break;
    }
    update_node(s->head, s->head->xpos, s->head->ypos);
}

int eat_food(Snake *s, Food *food)
{
    // if snake's head position is same with food's, snake will eat it
    if ((s->head->xpos == food->xpos) && (s->head->ypos == food->ypos))
    {
        LinkNode *before_tail = s->tail->prev;
        LinkNode *node = NULL;
        if (before_tail->xpos == s->tail->xpos)
        {
            node = new_node(s->tail->xpos, (s->tail->ypos) + (s->tail->ypos - before_tail->ypos));
        }
        else if (before_tail->ypos == s->tail->ypos)
        {
            node = new_node((s->tail->xpos) + (s->tail->xpos - before_tail->xpos), s->tail->ypos);
        }

        s->tail->next = node;
        node->prev = s->tail;
        s->tail = node;
        (s->size)++;
        return TRUE;
    }

    return FALSE;
}
