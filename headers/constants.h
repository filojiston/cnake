/**
 * @file constants.h
 * @author Seyitahmet Genç
 * @brief This file contains constant variables used across all source files
 * @date 2021-04-21
 *
 * @copyright Copyright (c) 2021
 */

#pragma once

#define TRUE 1
#define FALSE 0

#include <SDL2\SDL.h>

/**
 * @brief SCREEN_WIDTH must be same with SCREEN_HEIGHT
 */
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCALE;      /** used for scaling positions, makes drawing easy */
extern const int RECT_SIZE;  /** size of the rectangles (1 block in grid) */
extern const int GRID_COUNT; /** SCREEN_WIDTH / scale  */
extern const SDL_Color BACKGROUND_COLOR;
extern const SDL_Color SNAKE_COLOR; /** used for drawing snake rect, if there is no textures */
extern const SDL_Color FOOD_COLOR;  /** same as snake color           */
extern const char *TITLE;
