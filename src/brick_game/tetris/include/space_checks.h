/**
 * @file space_checks.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header with space_checks.c module function declarations
 * @version 1.0
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _SPACE_CHECKS_H_
#define _SPACE_CHECKS_H_

#include "./objects.h"

int have_space_to_move(const game_t *g, UserAction_t button);
int have_rotate_space(const game_t *g, int size);
int have_down_space(const game_t *g);

#endif  // SPACE_CHECKS_H