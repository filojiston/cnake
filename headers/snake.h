#pragma once

#include <SDL2\SDL.h>

#include "linknode.h"
#include "direction.h"

typedef struct Snake
{
    LinkNode *head;
    LinkNode *tail;
    Direction direction;
    int size;

    SDL_Texture *head_texture;
    SDL_Texture *body_texture;
    SDL_Texture *tail_texture;
} Snake;

typedef struct Food Food;

Snake *create_snake(int x, int y);
void set_snake_texture(Snake *s, SDL_Renderer *renderer, const char *p_head, const char *p_body, const char *p_tail);
void destroy_snake(Snake *snake);
void draw_snake(SDL_Renderer *renderer, Snake *s);
void move_snake(Snake *s, Direction dir);
void update_snake(Snake *s);
int eat_food(Snake *s, Food *food);
