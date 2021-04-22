/**
 * @file linknode.h
 * @author Seyitahmet Genç
 * @brief function definitions and struct for linknode
 * used for snake's body cells
 * @date 2021-04-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <SDL2\SDL.h>

typedef struct LinkNode
{
    SDL_Rect body_cell;    /** rectangle of each body cells of the snake */
    int xpos;              /** x position of the cell */
    int ypos;              /** y position of the cell*/
    struct LinkNode *next; /** next body cell */
    struct LinkNode *prev; /** previous body cell */
} LinkNode;

/**
 * @brief creates new body cell for snake
 *
 * @param x x position of new cell
 * @param y y position of new cell
 * @return LinkNode*
 */
LinkNode *new_node(int x, int y);

/**
 * @brief updates the location of given node, used for moving snake
 *
 * @param node to be updated
 * @param x new x position
 * @param y new y position
 */
void update_node(LinkNode *node, int x, int y);

/**
 * @brief frees the memory allocated by node
 *
 * @param node  to be freed
 */
void destroy_node(LinkNode *node);
