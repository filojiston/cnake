#include "linknode.h"

LinkNode *new_node(int x, int y, int size)
{
    LinkNode *node = (LinkNode *)malloc(sizeof(LinkNode));
    SDL_Rect body_rect;
    body_rect.h = body_rect.w = size;
    body_rect.x = x;
    body_rect.y = y;
    node->body_cell = body_rect;
    node->next = NULL;

    return node;
}
