/**
 * @file blocks.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header with blocks.c module function declarations
 * @version 1.0
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include "./objects.h"

void clean_line(game_t *g);
void fill_next_block(game_t *g);
void spawn_block(game_t *g);

#endif  // _BLOCKS_H_