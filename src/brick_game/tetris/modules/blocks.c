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

void fill_next_block(game_t *game) {
  game->current_name = rand() % BLOCK_CNT;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4 * BLOCK_SIZE; j++)
      game->info.next[i][j] = EMPTY;

  switch (game->current_name) {
  default:
  case BL_I:
    for (int j = 0; j < 4 * BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    break;
  case BL_L:
    for (int j = 0; j < BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    for (int j = 0; j < 3 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_ML:
    for (int j = 2 * BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    for (int j = 0; j < 3 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_Z:
    for (int j = 0; j < 2 * BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    for (int j = BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_MZ:
    for (int j = 1 * BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    for (int j = 0; j < 2 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_T:
    for (int j = BLOCK_SIZE; j < 2 * BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    for (int j = 0; j < 3 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_SQ:
    for (int j = BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++) {
      game->info.next[0][j] = FILL;
      game->info.next[1][j] = FILL;
    }
    break;
  }
}

void spawn_block(game_t *game) {
  int y_pos = COL / 2 - 2 * BLOCK_SIZE;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4 * BLOCK_SIZE; j++) {
      game->crnt[i][j].cell = game->info.next[i][j];
      game->crnt[i][j].x = i;
      game->crnt[i][j].y = y_pos + j;
    }
  }

  refresh_matrix(game);
  fill_next_block(game);
}

void refresh_matrix(game_t *game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4 * BLOCK_SIZE; j++) {
      if(game->crnt[i][j].cell) {
        game->info.field[game->crnt[i][j].x][game->crnt[i][j].y] = game->crnt[i][j].cell;
      }
    }
  }
}

void move_block(game_t *game, char button) {
  if (have_space(game, button)) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4 * BLOCK_SIZE; j++) {
        if (game->crnt[i][j].cell) {
          game->info.field[game->crnt[i][j].x][game->crnt[i][j].y] = EMPTY;
        }
        if (button == 4) {
          game->crnt[i][j].y -= BLOCK_SIZE;
        } else if (button == 5) {
          game->crnt[i][j].y += BLOCK_SIZE;
        }
      }
    }
  }
}

int have_space(game_t *game, char button) {
  int having = 1;
  int empty_left = 0;
  int empty_right = 0;

  for(int i = 0; i < 4; i++) {
    if(button == 4 && game->crnt[i][0].cell) {
      empty_left++;
      if(game->crnt[i][0].y == 0) {
        having = 0;
      }
    } else if(button == 5 && game->crnt[i][4 * BLOCK_SIZE - 1].cell) {
      empty_right++;
      if(game->crnt[i][4 * BLOCK_SIZE - 1].y == COL - 1) {
        having = 0;
      }
    }
  }

  if(button == 4 && !empty_left) {
    for(int i = 0; i < 4; i++) {
      if(button == 4 && game->crnt[i][BLOCK_SIZE].cell && game->crnt[i][BLOCK_SIZE].y == 0) {
        having = 0;
      }
    }
  } else if(button == 5 && !empty_right) {
    for(int i = 0; i < 4; i++) {
      if(game->crnt[i][3 * BLOCK_SIZE - 1].cell && game->crnt[i][3 * BLOCK_SIZE - 1].y == COL - 1) {
        having = 0;
      }
    }
  }

  return having;
}