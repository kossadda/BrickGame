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

void fill_next_block(Game *game) {
  switch (game->current) {
  default:
  case BL_I:
    for(int j = 0; j < 4 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_L:
    for(int j = 0; j < BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    for(int j = 0; j < 3 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_ML:
    for(int j = 2 * BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    for(int j = 0; j < 3 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_Z:
    for(int j = 0; j < 2 * BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    for(int j = BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_MZ:
    for(int j = 1 * BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    for(int j = 0; j < 2 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_T:
    for(int j = BLOCK_SIZE; j < 2 * BLOCK_SIZE; j++)
      game->info.next[0][j] = FILL;
    for(int j = 0; j < 3 * BLOCK_SIZE; j++)
      game->info.next[1][j] = FILL;
    break;
  case BL_SQ:
    for(int j = BLOCK_SIZE; j < 3 * BLOCK_SIZE; j++) {
      game->info.next[0][j] = FILL;
      game->info.next[1][j] = FILL;
    }
    break;
  }
}

