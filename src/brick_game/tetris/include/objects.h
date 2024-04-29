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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} game_info_t;

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

typedef struct {
  game_info_t gi;
  block_t **bl;
  list_block_t current_name;
  list_block_t next_name;
} game_t;

typedef enum { EMPTY, FILL } fill_l;

#define BL_X (g->bl[i][j].x)
#define BL_Y (g->bl[i][j].y)

#endif  // OBJECTS_H