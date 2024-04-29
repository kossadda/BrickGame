/**
 * @file blocks.h
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef BLOCKS_H
#define BLOCKS_H

#include "./fsm.h"

void fill_next_block(game_t *g);
void spawn_block(game_t *g);

#endif // BLOCKS_H