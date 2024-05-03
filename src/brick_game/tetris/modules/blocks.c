/**
 * @file blocks.c
 * @author kossadda (https://github.com/kossadda)
 * @brief The module contains functions for working with blocks
 * @version 1.0
 * @date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/blocks.h"

#include "./../include/init.h"

static int scan_matrix(const game_t *g);

/**
 * @brief Fill the next shape with random
 *
 * @param[out] g main structure
 */
void fill_next_block(game_t *g) {
  g->next_name = rand() % BLOCK_CNT;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4 * SIZE; j++) {
      g->info.next[i][j] = EMPTY;
    }
  }

  switch (g->next_name) {
    default:
    case BL_I:
      for (int j = 0; j < 4 * SIZE; j++) g->info.next[1][j] = RED;
      break;
    case BL_L:
      for (int j = 0; j < SIZE; j++) g->info.next[0][j] = ORANGE;
      for (int j = 0; j < 3 * SIZE; j++) g->info.next[1][j] = ORANGE;
      break;
    case BL_ML:
      for (int j = 2 * SIZE; j < 3 * SIZE; j++) g->info.next[0][j] = YELLOW;
      for (int j = 0; j < 3 * SIZE; j++) g->info.next[1][j] = YELLOW;
      break;
    case BL_Z:
      for (int j = 0; j < 2 * SIZE; j++) g->info.next[0][j] = GREEN;
      for (int j = SIZE; j < 3 * SIZE; j++) g->info.next[1][j] = GREEN;
      break;
    case BL_MZ:
      for (int j = SIZE; j < 3 * SIZE; j++) g->info.next[0][j] = PURPLE;
      for (int j = 0; j < 2 * SIZE; j++) g->info.next[1][j] = PURPLE;
      break;
    case BL_T:
      for (int j = SIZE; j < 2 * SIZE; j++) g->info.next[0][j] = BLUE;
      for (int j = 0; j < 3 * SIZE; j++) g->info.next[1][j] = BLUE;
      break;
    case BL_SQ:
      for (int j = SIZE; j < 3 * SIZE; j++) {
        g->info.next[0][j] = PINK;
        g->info.next[1][j] = PINK;
      }
  }
}

/**
 * @brief Create a new block and fill the next one
 *
 * @param[out] g main structure
 */
void spawn_block(game_t *g) {
  int y_pos = COL / 2 - 2 * SIZE;
  int have_space = YES;

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      CELL(i, j) = g->info.next[i][j];
      X(i, j) = i;
      Y(i, j) = y_pos + j;

      if (CELL(i, j) && FIELD(X(i, j), Y(i, j))) {
        have_space = NO;
      }
    }
  }

  if (have_space == YES) {
    g->current_name = g->next_name;
    g->change = true;

    updateCurrentState(g);
    fill_next_block(g);
  } else {
    g->info.pause = GAME_OVER;

    if (g->info.score >= g->info.high_score) {
      char path_score[255];
      get_txt_file_path(path_score);
      FILE *f_score = fopen(path_score, "w");

      if (f_score) {
        fprintf(f_score, "%d", g->info.score);
        fclose(f_score);
      }
    }
  }
}

/**
 * @brief Clear all filled lines and award points to the player
 *
 * @param[out] g main structure
 */
void clean_line(game_t *g) {
  int current_level = g->info.level;
  int lines_count = 0;
  int line;

  while ((line = scan_matrix(g)) != NO) {
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
      g->info.score += ONE_LINE;
    } else if (lines_count == 2) {
      g->info.score += TWO_LINE;
    } else if (lines_count == 3) {
      g->info.score += THREE_LINE;
    } else if (lines_count == 4) {
      g->info.score += FOUR_LINE;
    }

    if(g->info.score > g->info.high_score) {
      g->info.high_score = g->info.score;
    }

    if (g->info.level <= LEVEL_MAX) {
      g->info.level = g->info.score / LEVEL_CHANGE + 1;
      if (g->info.level > LEVEL_MAX) {
        g->info.level = LEVEL_MAX;
      }

      if (current_level != g->info.level) {
        g->info.speed -= (g->info.level - current_level) * LEVEL_SPEED;
      }
    }
  }
}

/**
 * @brief Scans the matrix for filled lines
 *
 * @param[in] g main structure
 * @retval int    - number of the first line found
 * @retval NO (0) - no lines found
 */
static int scan_matrix(const game_t *g) {
  int cell_per_line = 0;
  int full_line = NO;

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
