/**
 * @file shifts.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./../include/common.h"

void move_block(game_t *g, UserAction_t button) {
  if ((button == Left || button == Right) && have_space(g, button)) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4 * BLOCK_SIZE; j++) {
        if (g->bl[i][j].cell) {
          g->gi.field[BL_X][BL_Y] = EMPTY;
        }
        BL_Y += (button == Right) ? BLOCK_SIZE : -BLOCK_SIZE;
      }
    }
  }
}

void move_down(game_t *g) {
  if (have_down_space(g)) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4 * BLOCK_SIZE; j++) {
        if (g->bl[i][j].cell) {
          g->gi.field[BL_X][BL_Y] = EMPTY;
        }
        BL_X++;
      }
    }
  } else {
    spawn_block(g);
  }
}