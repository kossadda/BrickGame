/**
 * @file fsm.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./../include/fsm.h"
#include "./../include/shifts.h"

void update_current_state(game_t *g) {
  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * CELL; j++) {
      if (g->bl[i][j].cell) {
        g->gi.field[BL_X][BL_Y] = g->bl[i][j].cell;
      }
    }
  }
}

void user_input(UserAction_t action, game_t *g, double *lut, bool hold) {
  (void)hold;
  switch (action) {
    case Terminate:
      g->gi.pause = Terminate;
      break;
    case Pause:
      g->gi.pause = Pause;
      break;
    case Start:
      g->gi.pause = 0;
      break;
    case Right:
    case Left:
      move_block(g, action);
      update_current_state(g);
      break;
    case Down:
      move_down(g);
      update_current_state(g);
      break;
    case Up:
      rotate_block(g);
      update_current_state(g);
      break;
    default:
      if(current_time() - *lut >= g->gi.speed) {
        *lut = current_time();
        move_down(g);
        update_current_state(g);
    }
  }
}

double current_time() {
  return clock() * 1000 / CLOCKS_PER_SEC;
}