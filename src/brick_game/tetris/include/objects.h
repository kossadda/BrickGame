/**
 * @file objects.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Contains a declaration of types and lists for working with the game
 * @version 1.0
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./fsm.h"

/// @brief Representation of position and occupancy of cells of moving figure
typedef struct {
  int cell;  ///< Cell occupancy
  int x;     ///< Coordinate of the cell along the X-axis
  int y;     ///< Coordinate of the cell along the Y-axis
} block_t;

/// @brief List of all tetris figures
typedef enum {
  BL_I,      ///< Figure in the form of "I"
  BL_L,      ///< Figure in the form of "L"
  BL_ML,     ///< Figure in the form of mirror "L"
  BL_Z,      ///< Figure in the form of "Z"
  BL_MZ,     ///< Figure in the form of mirror "Z"
  BL_T,      ///< Figure in the form of upside down "T"
  BL_SQ,     ///< Figure in the form of square
  BLOCK_CNT  /// Determine the number of enum members
} figure;

/// @brief List of colors used
typedef enum {
  BLACK,   ///< Black background color
  RED,     ///< "I" shape color
  GREEN,   ///< "Z" shape color
  YELLOW,  ///< "ML" shape color
  BLUE,    ///< "T" shape color
  PURPLE,  ///< "MZ" shape color
  PINK,    ///< Square shape color
  WHITE,   ///< White background color
  ORANGE,  ///< "L" shape color
} color_pairs_t;

/// @brief Main type. Contains all game data
typedef struct {
  GameInfo_t info;      ///< Contains the basic information regarding the field
  block_t **block;      ///< An array reflecting the position of a moving figure
  figure current_name;  ///< Name of the moving figure
  figure next_name;     ///< Name of the next figure
  bool change;          ///< Signal of collising
  bool theme;           ///< Game color scheme
} game_t;

/**
 * @brief Referring to the cell X coordinate of a moving block
 *
 * @param i Array element row
 * @param j Array element col
 */
#define X(i, j) (g->block[i][j].x)

/**
 * @brief Referring to the cell Y coordinate of a moving block
 *
 * @param i Array element row
 * @param j Array element col
 */
#define Y(i, j) (g->block[i][j].y)

/**
 * @brief Determining cell occupancy of a moving block
 *
 * @param i Array element row
 * @param j Array element col
 */
#define CELL(i, j) g->block[i][j].cell

/**
 * @brief Determining cell occupancy of field
 *
 * @param i Array element row
 * @param j Array element col
 */
#define FIELD(i, j) g->info.field[i][j]

game_t *game();

#endif  // _OBJECTS_H_