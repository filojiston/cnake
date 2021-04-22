/**
 * @file snake.h
 * @author Seyitahmet Genç
 * @brief function definitions and snake struct
 * @date 2021-04-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <SDL2\SDL.h>

#include "linknode.h"
#include "direction.h"

typedef struct Snake
{
    LinkNode *head;      /** head node of the snake */
    LinkNode *tail;      /** tail node of the snake */
    Direction direction; /** current direction of snake's head*/
    int size;            /** snake's size (count of body cells) - used for score */

    SDL_Texture *head_texture; /** texture used for drawing snake's head */
    SDL_Texture *body_texture; /** texture used for drawing snake's body cells */
    SDL_Texture *tail_texture; /** texture used for drawing snake's tail */
} Snake;

typedef struct Food Food;

/**
 * @brief create a snake at given x,y positions
 *
 * @param x x position of new snake
 * @param y y position of new snake
 * @return Snake*
 */
Snake *create_snake(int x, int y);

/**
 * @brief set the snake's textures (head, body, tail)
 *
 * @param s the snake which the textures is to be applied
 * @param renderer used for loading image files
 * @param p_head path of head texture
 * @param p_body path of body texture
 * @param p_tail path of tail texture
 */
void set_snake_texture(Snake *s, SDL_Renderer *renderer, const char *p_head, const char *p_body, const char *p_tail);

/**
 * @brief frees allocated memory for snake object and all it's body cells
 *
 * @param snake the snakewhich is to be freed
 */
void destroy_snake(Snake *snake);

/**
 * @brief draws snake to the screen
 *
 * @param renderer used for drawing to screen
 * @param s the snake which is to be drawed
 */
void draw_snake(SDL_Renderer *renderer, Snake *s);

/**
 * @brief sets snake's head's direction
 *
 * @param s the snake which is to be moved
 * @param dir which direction it's gonna be
 */
void move_snake(Snake *s, Direction dir);

/**
 * @brief updates snakes body cell locations (moves the snake)
 *
 * @param s which is to be moved
 */
void update_snake(Snake *s);

/**
 * @brief checks if snake's head and food in same location
 * if so, snake will be eat the food.
 *
 * @param s snake who eats the food
 * @param food who's eaten by the snake
 * @return int if snake eats the food, return TRUE
 * false otherwise
 */
int eat_food(Snake *s, Food *food);
