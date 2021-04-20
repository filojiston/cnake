#pragma once

#include <SDL2\SDL.h>
#include <stdlib.h>
#include "constants.h"

typedef struct LinkNode
{
    SDL_Rect body_cell;
    int xpos;
    int ypos;
    struct LinkNode *next;
    struct LinkNode *prev;
} LinkNode;

LinkNode *new_node(int x, int y);
void update_node(LinkNode *node, int x, int y);
void destroy_node(LinkNode *node);
