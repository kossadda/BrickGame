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
      for (int j = 0; j < BL_MAX * SIZE; j++) {
        if (CELL(i, j)) {
          having *= cell_can_move_left(g, i, j);
        }
      }
    }
  } else if (button == Right) {
    for (int i = 0; i < BL_MAX; i++) {
      for (int j = 0; j < BL_MAX * SIZE; j++) {
        if (CELL(i, j)) {
          having *= cell_can_move_right(g, i, j);
        }
      }
    }
  }

  return having;
}

int have_rotate_space(game_t *g, int size) {
  int having = 1;

  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      if(CELL(i, j * SIZE)) {
        if(X(i, j * SIZE) + 1 >= ROW || Y(i, j * SIZE) < 0 || Y(i, j * SIZE) >= COL) {
          having = 0;
        } else if(FIELD(X(i, j * SIZE), Y(i, j * SIZE))) {
          having = 0;
        }
      }
    }
  }

  return having;
}

int have_down_space(game_t *g) {
  int having = 1;

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      if (CELL(i, j)) {
        if(X(i, j) + 1 >= ROW) {
          having = 0;
        } else if(i + 1 == BL_MAX) {
          if(FIELD(X(i, j) + 1, Y(i, j))) {
            having = 0;
          }
        } else {
          if(FIELD(X(i, j) + 1, Y(i, j)) && !CELL(i + 1, j)) {
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

  if (Y(i, j) == 0) {
    can = 0;
  } else if (j == 0) {
    if (FIELD(X(i, j), Y(i, j) - 1)) {
      can = 0;
    }
  } else {
    if (!CELL(i, j - 1) && FIELD(X(i, j), Y(i, j) - 1)) {
      can = 0;
    }
  }

  return can;
}

static int cell_can_move_right(game_t *g, int i, int j) {
  int can = 1;

  if (Y(i, j) + 1 >= COL) {
    can = 0;
  } else if (j == BL_MAX * SIZE - 1) {
    if(FIELD(X(i, j), Y(i, j) + 1)) {
      can = 0;
    }
  } else {
    if (!CELL(i, j + 1) && FIELD(X(i, j), Y(i, j) + 1)) {
      can = 0;
    }
  }

  return can;
}