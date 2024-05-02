/**
 * @file objects.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef OBJECTS_H
#define OBJECTS_H

#include "./fsm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int cell;
  int x;
  int y;
} block_t;

typedef enum {
  BL_I,
  BL_L,
  BL_ML,
  BL_Z,
  BL_MZ,
  BL_T,
  BL_SQ,
  BLOCK_CNT
} list_block_t;

typedef enum {
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  PURPLE,
  PINK,
  WHITE,
  ORANGE,
} color_pairs_t;

typedef struct {
  GameInfo_t info;
  block_t **block;
  list_block_t current_name;
  list_block_t next_name;
  bool change;
  bool theme;
} game_t;

#define X(i, j) (g->block[i][j].x)
#define Y(i, j) (g->block[i][j].y)
#define CELL(i, j) g->block[i][j].cell
#define FIELD(i, j) g->info.field[i][j]

game_t *game();

#endif  // OBJECTS_H