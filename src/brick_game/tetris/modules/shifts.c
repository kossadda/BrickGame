/**
 * @file shifts.c
 * @author kossadda (https://github.com/kossadda)
 * @brief The module contains functions for working with figure movements
 * @version 1.0
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/common.h"

static void move_to_square_matrix(int size, int matrix[][size],
                                  int copy[][size], const game_t *g);
static void move_to_rectangular_matrix(int size, int matrix[][size], game_t *g);

/**
 * @brief Moving the figure to the sides
 *
 * @param[out] g main structure
 * @param[in] button  pressed key
 */
void move_block(game_t *g, UserAction_t button) {
  if ((button == Left || button == Right) && have_space_to_move(g, button)) {
    for (int i = 0; i < BL_MAX; i++) {
      for (int j = 0; j < BL_MAX * SIZE; j++) {
        if (CELL(i, j)) {
          FIELD(X(i, j), Y(i, j)) = EMPTY;
        }
        Y(i, j) += (button == Right) ? SIZE : -SIZE;
      }
    }
  }
}

/**
 * @brief Move a figure down
 *
 * @param[out] g main structure
 */
void move_down(game_t *g) {
  if (have_down_space(g)) {
    for (int i = 0; i < BL_MAX; i++) {
      for (int j = 0; j < BL_MAX * SIZE; j++) {
        if (CELL(i, j)) {
          FIELD(X(i, j), Y(i, j)) = EMPTY;
        }
        X(i, j)++;
      }
    }
  } else {
    clean_line(g);
    spawn_block(g);
  }
}

/**
 * @brief Rotate figure for 90 degrees
 *
 * @param[out] g main structure
 */
void rotate_block(game_t *g) {
  if (g->current_name == BL_SQ) return;

  int size = (g->current_name == BL_I) ? BL_MAX : 3;
  int rotate_matrix[size][size];
  int return_copy[size][size];

  move_to_square_matrix(size, rotate_matrix, return_copy, g);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size * SIZE; j++) {
      if (CELL(i, j)) {
        FIELD(X(i, j), Y(i, j)) = EMPTY;
      }
    }
  }

  move_to_rectangular_matrix(size, rotate_matrix, g);

  if (!have_rotate_space(g, size)) {
    move_to_rectangular_matrix(size, return_copy, g);
  }
}

/**
 * @brief Convert a rectangular box to its square counterpart for rotation
 *
 * @param[in] size max figure size
 * @param[out] matrix square matrix
 * @param[out] copy a copy of the original matrix (for return if necessary)
 * @param[out] g main structure
 */
static void move_to_square_matrix(int size, int matrix[][size],
                                  int copy[][size], const game_t *g) {
  int temp = 0;

  for (int i = 0, sq = 0; i < size; i++, sq = 0) {
    for (int j = 0; j < size * SIZE; j += SIZE) {
      matrix[i][sq] = CELL(i, j);
      copy[i][sq++] = CELL(i, j);
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      temp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = temp;
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size / 2; j++) {
      temp = matrix[i][j];
      matrix[i][j] = matrix[i][size - j - 1];
      matrix[i][size - j - 1] = temp;
    }
  }
}

/**
 * @brief Reverting a square matrix to its rectangular counterpart
 *
 * @param[in] size max figure size
 * @param[out] matrix square matrix
 * @param[out] g main structure
 */
static void move_to_rectangular_matrix(int size, int matrix[][size],
                                       game_t *g) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < SIZE; k++) {
        CELL(i, j * SIZE + k) = matrix[i][j];
      }
    }
  }
}
