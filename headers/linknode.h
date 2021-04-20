#pragma once

#include <SDL2\SDL.h>

typedef struct LinkNode
{
    SDL_Rect body_cell;
    SDL_Texture *head_texture;
    SDL_Texture *body_texture;
    SDL_Texture *tail_texture;
    int xpos;
    int ypos;
    struct LinkNode *next;
    struct LinkNode *prev;
} LinkNode;

LinkNode *new_node(int x, int y);
void update_node(LinkNode *node, int x, int y);
void destroy_node(LinkNode *node);
