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

#include "./../include/blocks.h"

static int scan_matrix(game_t *g);

void fill_next_block(game_t *g) {
  g->next_name = rand() % BLOCK_CNT;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4 * SIZE; j++) {
      g->gi.next[i][j] = EMPTY;
    }
  }

  switch (g->next_name) {
    default:
    case BL_I:
      for (int j = 0; j < 4 * SIZE; j++) g->gi.next[1][j] = RED;
      break;
    case BL_L:
      for (int j = 0; j < SIZE; j++) g->gi.next[0][j] = ORANGE;
      for (int j = 0; j < 3 * SIZE; j++) g->gi.next[1][j] = ORANGE;
      break;
    case BL_ML:
      for (int j = 2 * SIZE; j < 3 * SIZE; j++) g->gi.next[0][j] = YELLOW;
      for (int j = 0; j < 3 * SIZE; j++) g->gi.next[1][j] = YELLOW;
      break;
    case BL_Z:
      for (int j = 0; j < 2 * SIZE; j++) g->gi.next[0][j] = GREEN;
      for (int j = SIZE; j < 3 * SIZE; j++) g->gi.next[1][j] = GREEN;
      break;
    case BL_MZ:
      for (int j = 1 * SIZE; j < 3 * SIZE; j++) g->gi.next[0][j] = PURPLE;
      for (int j = 0; j < 2 * SIZE; j++) g->gi.next[1][j] = PURPLE;
      break;
    case BL_T:
      for (int j = SIZE; j < 2 * SIZE; j++) g->gi.next[0][j] = BLUE;
      for (int j = 0; j < 3 * SIZE; j++) g->gi.next[1][j] = BLUE;
      break;
    case BL_SQ:
      for (int j = SIZE; j < 3 * SIZE; j++) {
        g->gi.next[0][j] = PINK;
        g->gi.next[1][j] = PINK;
      }
  }
}

void spawn_block(game_t *g) {
  int y_pos = COL / 2 - 2 * SIZE;
  int have_space = 1;

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      CELL(i, j) = g->gi.next[i][j];
      X(i, j) = i;
      Y(i, j) = y_pos + j;
      if (CELL(i, j) && FIELD(X(i, j), Y(i, j))) {
        have_space = 0;
      }
    }
  }

  if (have_space) {
    g->current_name = g->next_name;
    g->change = true;
    update_current_state(g);
    fill_next_block(g);
  } else {
    g->gi.pause = GAME_OVER;
  }
}

void clean_line(game_t *g) {
  int current_level = g->gi.level;
  int lines_count = 0;
  int line;

  while ((line = scan_matrix(g)) != -1) {
    lines_count++;

    for (int i = line; i > 0; i--) {
      for (int j = 0; j < COL; j++) {
        FIELD(i, j) = FIELD(i - 1, j);
      }
    }

    for (int j = 0; j < COL; j++) {
      FIELD(0, j) = 0;
    }
  }


  if (lines_count) {
    if (lines_count == 1) {
      g->gi.score += ONE_LINE;
    } else if (lines_count == 2) {
      g->gi.score += TWO_LINE;
    } else if (lines_count == 3) {
      g->gi.score += THREE_LINE;
    } else if (lines_count == 4) {
      g->gi.score += FOUR_LINE;
    }

    if (g->gi.level <= LEVEL_MAX) {
      g->gi.level = g->gi.score / LEVEL_CHANGE + 1;
      if(g->gi.level > 10) {
        g->gi.level = 10;
      }

      if (current_level != g->gi.level) {
        g->gi.speed -= (g->gi.level - current_level) * LEVEL_SPEED;
      }
    }
  }
}

static int scan_matrix(game_t *g) {
  int cell_per_line = 0;
  int full_line = -1;

  for (int i = 0; i < ROW; i++, cell_per_line = 0) {
    for (int j = 0; j < COL; j++) {
      if (!FIELD(i, j)) {
        cell_per_line++;
        break;
      }
    }

    if (cell_per_line == 0) {
      full_line = i;
      break;
    }
  }

  return full_line;
}
