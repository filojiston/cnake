#include <stdlib.h>
#include "constants.h"

#include "linknode.h"

LinkNode *new_node(int x, int y)
{
    LinkNode *node = (LinkNode *)malloc(sizeof(LinkNode));
    SDL_Rect body_rect;
    body_rect.h = body_rect.w = RECT_SIZE;
    body_rect.x = x * SCALE;
    body_rect.y = y * SCALE;
    node->body_cell = body_rect;
    node->next = NULL;
    node->prev = NULL;
    node->xpos = x;
    node->ypos = y;

    return node;
}

void update_node(LinkNode *node, int x, int y)
{
    node->xpos = x;
    node->ypos = y;
    node->body_cell.x = x * SCALE;
    node->body_cell.y = y * SCALE;
}

void destroy_node(LinkNode *node)
{
    free(node);
}
