/**
 * @file food.h
 * @author Seyitahmet Genç
 * @brief function definitions about food and food structure
 * @date 2021-04-21
 *
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <SDL2\SDL.h>

typedef struct Food
{
    SDL_Rect food_cell;        /** food's body rectangle */
    SDL_Texture *food_texture; /** food's texture */
    int xpos;                  /** x position of food */
    int ypos;                  /** y position of food */
} Food;

typedef struct Snake Snake;

/**
 * @brief create a food at given x,y position
 *
 * @param x x position of new food
 * @param y y position of new food
 * @return Food*
 */
Food *create_food(int x, int y);

/**
 * @brief set food's texture
 *
 * @param food food to which the texture is to be applied
 * @param renderer SDL_Renderer used for loading image
 * @param tex_path path of the image file
 */
void set_food_texture(Food *food, SDL_Renderer *renderer, const char *tex_path);

/**
 * @brief free memory allocated for food
 *
 * @param food food to which is to be freed
 */
void destroy_food(Food *food);

/**
 * @brief draw given food to the window
 *
 * @param renderer used for drawing to the window
 * @param food which is to be drawed
 */
void draw_food(SDL_Renderer *renderer, Food *food);

/**
 * @brief re-locate given food if snake eats it
 *
 * @param food which is to be relocated
 * @param snake for checking if snake eats the food
 */
void update_food(Food *food, Snake *snake);
