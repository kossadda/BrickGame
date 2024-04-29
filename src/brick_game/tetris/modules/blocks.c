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
  g->current_name = rand() % BLOCK_CNT;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4 * BLOCK_SIZE; j++)
      g->gi.next[i][j] = EMPTY;

  switch (g->current_name) {
  default:
  case BL_I:
    for (int j = 0; j < 4 * BLOCK_SIZE; j++)
      g->gi.next[0][j] = FILL;
    break;
  case BL_L:
    for (int j = 0; j < BLOCK_SIZE; j++)
      g->gi.next[0][j] = FILL;
    for (int j = 0; j < 3 * BLOCK_SIZE; j++)
      g->gi.next[1][j] = FILL;
    break;
  case BL_ML:
    for (int j = 2 * BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++)
      g->gi.next[0][j] = FILL;
    for (int j = 0; j < 3 * BLOCK_SIZE; j++)
      g->gi.next[1][j] = FILL;
    break;
  case BL_Z:
    for (int j = 0; j < 2 * BLOCK_SIZE; j++)
      g->gi.next[0][j] = FILL;
    for (int j = BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++)
      g->gi.next[1][j] = FILL;
    break;
  case BL_MZ:
    for (int j = 1 * BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++)
      g->gi.next[0][j] = FILL;
    for (int j = 0; j < 2 * BLOCK_SIZE; j++)
      g->gi.next[1][j] = FILL;
    break;
  case BL_T:
    for (int j = BLOCK_SIZE; j < 2 * BLOCK_SIZE; j++)
      g->gi.next[0][j] = FILL;
    for (int j = 0; j < 3 * BLOCK_SIZE; j++)
      g->gi.next[1][j] = FILL;
    break;
  case BL_SQ:
    for (int j = BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++) {
      g->gi.next[0][j] = FILL;
      g->gi.next[1][j] = FILL;
    }
    break;
  }
}

void spawn_block(game_t *g) {
  int y_pos = COL / 2 - 2 * BLOCK_SIZE;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4 * BLOCK_SIZE; j++) {
      g->bl[i][j].cell = g->gi.next[i][j];
      g->bl[i][j].x = i;
      g->bl[i][j].y = y_pos + j;
    }
  }

  refresh_matrix(g);
  fill_next_block(g);
}

void refresh_matrix(game_t *g) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4 * BLOCK_SIZE; j++) {
      if(g->bl[i][j].cell) {
        g->gi.field[g->bl[i][j].x][g->bl[i][j].y] = g->bl[i][j].cell;
      }
    }
  }
}

void move_block(game_t *g, char button) {
  if ((button == Left || button == Right) && have_space(g, button)) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4 * BLOCK_SIZE; j++) {
        if (g->bl[i][j].cell) {
          g->gi.field[g->bl[i][j].x][g->bl[i][j].y] = EMPTY;
        }
        g->bl[i][j].y += (button == Right) ? BLOCK_SIZE : -BLOCK_SIZE;
      }
    }
  }
}

int have_space(game_t *g, char button) {
  int having = 1;

  if(button == Left) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4 * BLOCK_SIZE; j++)
        if (g->bl[i][j].cell) {
          if(g->bl[i][j].y == 0) {
            having = 0;
          } else if((j && !g->bl[i][j - 1].cell) && g->gi.field[g->bl[i][j].x][g->bl[i][j].y - 1]) {
            having = 0;
          }
        }
    }
  } else if(button == Right) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4 * BLOCK_SIZE; j++) {
        if (g->bl[i][j].cell) {
          if(g->bl[i][j].y + 1 == COL) {
            having = 0;
          } else if ((j != 4 * BLOCK_SIZE - 1 && !g->bl[i][j + 1].cell) && (g->bl[i][j].y + 1 != COL && g->gi.field[g->bl[i][j].x][g->bl[i][j].y + 1])) {
            having = 0;
          }
        }
      }
    }
  }

  return having;
}

int have_down_space(game_t *g) {
  int having = 1;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4 * BLOCK_SIZE; j++)
      if (g->bl[i][j].cell && (g->bl[i][j].x + 1 == ROW || (!g->bl[i + 1][j].cell && g->gi.field[g->bl[i][j].x + 1][g->bl[i][j].y])))
        having = 0;

  return having;
}

void move_down(game_t *g) {
  if (have_down_space(g)) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4 * BLOCK_SIZE; j++) {
        if (g->bl[i][j].cell) {
          g->gi.field[g->bl[i][j].x][g->bl[i][j].y] = EMPTY;
        }
        g->bl[i][j].x += 1;
      }
    }
  } else {
    spawn_block(g);
  }
}