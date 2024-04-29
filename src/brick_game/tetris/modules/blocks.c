/**
 * @file blocks.c
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/common.h"

void fill_next_block(game_t *g) {
  g->next_name = rand() % BLOCK_CNT;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4 * CELL; j++) g->gi.next[i][j] = EMPTY;

  switch (g->next_name) {
    default:
    case BL_I:
      for (int j = 0; j < 4 * CELL; j++) g->gi.next[1][j] = FILL;
      break;
    case BL_L:
      for (int j = 0; j < CELL; j++) g->gi.next[0][j] = FILL;
      for (int j = 0; j < 3 * CELL; j++) g->gi.next[1][j] = FILL;
      break;
    case BL_ML:
      for (int j = 2 * CELL; j < 3 * CELL; j++)
        g->gi.next[0][j] = FILL;
      for (int j = 0; j < 3 * CELL; j++) g->gi.next[1][j] = FILL;
      break;
    case BL_Z:
      for (int j = 0; j < 2 * CELL; j++) g->gi.next[0][j] = FILL;
      for (int j = CELL; j < 3 * CELL; j++) g->gi.next[1][j] = FILL;
      break;
    case BL_MZ:
      for (int j = 1 * CELL; j < 3 * CELL; j++)
        g->gi.next[0][j] = FILL;
      for (int j = 0; j < 2 * CELL; j++) g->gi.next[1][j] = FILL;
      break;
    case BL_T:
      for (int j = CELL; j < 2 * CELL; j++) g->gi.next[0][j] = FILL;
      for (int j = 0; j < 3 * CELL; j++) g->gi.next[1][j] = FILL;
      break;
    case BL_SQ:
      for (int j = CELL; j < 3 * CELL; j++) {
        g->gi.next[0][j] = FILL;
        g->gi.next[1][j] = FILL;
      }
  }
  
}

void spawn_block(game_t *g) {
  int y_pos = COL / 2 - 2 * CELL;

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * CELL; j++) {
      g->bl[i][j].cell = g->gi.next[i][j];
      BL_X = i;
      BL_Y = y_pos + j;
    }
  }

  g->current_name = g->next_name;
  update_current_state(g);
  fill_next_block(g);
}