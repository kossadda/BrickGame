/**
 * @file space_checks.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./../include/space_checks.h"

static int cell_can_move_right(game_t *g, int i, int j);
static int cell_can_move_left(game_t *g, int i, int j);

int have_space(game_t *g, UserAction_t button) {
  int having = 1;

  if (button == Left) {
    for (int i = 0; i < BL_MAX; i++) {
      for (int j = 0; j < BL_MAX * CELL; j++) {
        if (g->bl[i][j].cell) {
          having *= cell_can_move_left(g, i, j);
        }
      }
    }
  } else if (button == Right) {
    for (int i = 0; i < BL_MAX; i++) {
      for (int j = 0; j < BL_MAX * CELL; j++) {
        if (g->bl[i][j].cell) {
          having *= cell_can_move_right(g, i, j);
        }
      }
    }
  }

  return having;
}

int have_down_space(game_t *g) {
  int having = 1;

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * CELL; j++) {
      if (g->bl[i][j].cell) {
        if(BL_X + 1 >= ROW) {
          having = 0;
        } else if(i + 1 == BL_MAX) {
          if(g->gi.field[BL_X + 1][BL_Y]) {
            having = 0;
          }
        } else {
          if(g->gi.field[BL_X + 1][BL_Y] && !g->bl[i + 1][j].cell) {
            having = 0;
          }
        }
      }
    }
  }

  return having;
}

static int cell_can_move_left(game_t *g, int i, int j) {
  int can = 1;

  if (BL_Y == 0) {
    can = 0;
  } else if (j == 0) {
    if (g->gi.field[BL_X][BL_Y - 1]) {
      can = 0;
    }
  } else {
    if (!g->bl[i][j - 1].cell &&
        g->gi.field[BL_X][BL_Y - 1]) {
      can = 0;
    }
  }

  return can;
}

static int cell_can_move_right(game_t *g, int i, int j) {
  int can = 1;

  if (BL_Y + 1 >= COL) {
    can = 0;
  } else if (j == BL_MAX * CELL - 1) {
    if(g->gi.field[BL_X][BL_Y + 1]) {
      can = 0;
    }
  } else {
    if (!g->bl[i][j + 1].cell && g->gi.field[BL_X][BL_Y + 1]) {
      can = 0;
    }
  }

  return can;
}