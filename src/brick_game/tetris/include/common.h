/**
 * @file common.h
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMMON_H
#define COMMON_H

#include "./fsm.h"
#include "./objects.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 3
#define COL 10 * BLOCK_SIZE
#define ROW 20

void init_game(game_t *game);
void set_high_score(game_info_t *info);

void fill_next_block(game_t *game);
void spawn_block(game_t *game);
void refresh_matrix(game_t *game);
void move_block(game_t *game, char button);
int have_space(game_t *game, char button);
void move_down(game_t *game);

#endif // COMMON_H