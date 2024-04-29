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

static void move_to_square_matrix(int size, int matrix[][size], game_t *g);

void move_block(game_t *g, UserAction_t button) {
  if ((button == Left || button == Right) && have_space(g, button)) {
    for (int i = 0; i < BL_MAX; i++) {
      for (int j = 0; j < BL_MAX * CELL; j++) {
        if (g->bl[i][j].cell) {
          g->gi.field[BL_X][BL_Y] = EMPTY;
        }
        BL_Y += (button == Right) ? CELL : -CELL;
      }
    }
  }
}

void move_down(game_t *g) {
  if (have_down_space(g)) {
    for (int i = 0; i < BL_MAX; i++) {
      for (int j = 0; j < BL_MAX * CELL; j++) {
        if (g->bl[i][j].cell) {
          g->gi.field[BL_X][BL_Y] = EMPTY;
        }
        BL_X++;
      }
    }
  } else {
    clean_line(g);
    spawn_block(g);
  }
}

void rotate_block(game_t *g) {
  if(g->current_name == BL_SQ) return;

  int size = (g->current_name == BL_I) ? BL_MAX : 3;
  int square_matrix[size][size];

  move_to_square_matrix(size, square_matrix, g);
  
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size * CELL; j++) {
      if(g->bl[i][j].cell) {
        g->gi.field[BL_X][BL_Y] = EMPTY;
      }
    }
  }

  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      for(int k = 0; k < CELL; k++) {
        g->bl[i][j * CELL + k].cell = square_matrix[i][j];
      }
    }
  }
}

static void move_to_square_matrix(int size, int matrix[][size], game_t *g) {
  int temp = 0;

  for(int i = 0, sq = 0; i < size; i++, sq = 0) {
    for(int j = 0; j < size * CELL; j += CELL) {
      matrix[i][sq++] = g->bl[i][j].cell;
    }
  }

  for(int i = 0; i < size; i++) {
    for(int j = i + 1; j < size; j++) {
      temp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = temp;
    }
  }

  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size / 2; j++) {
      temp = matrix[i][j];
      matrix[i][j] = matrix[i][size - j - 1];
      matrix[i][size - j - 1] = temp;
    }
  }
}