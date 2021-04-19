#pragma once

#include <SDL.h>
#include <stdlib.h>
#include "linknode.h"

typedef struct Snake
{
    LinkNode *head;
    LinkNode *tail;
} Snake;

Snake *create_snake(int x, int y, int size, int scale);
void destroy_snake(Snake *snake);
void draw_snake(SDL_Renderer *renderer, Snake *s);
