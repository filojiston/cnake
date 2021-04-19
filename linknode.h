#pragma once

#include <SDL.h>
#include <stdlib.h>

typedef struct LinkNode
{
    SDL_Rect body_cell;
    struct LinkNode *next;
} LinkNode;

LinkNode *new_node(int x, int y, int size);
