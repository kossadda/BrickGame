/**
 * @file shifts.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header with shifts.c module function declarations
 * @version 1.0
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _SHIFTS_H_
#define _SHIFTS_H_

#include "./objects.h"

void move_block(game_t *g, UserAction_t button);
void move_down(game_t *g);
void rotate_block(game_t *g);

#endif  // _SHIFTS_H_
