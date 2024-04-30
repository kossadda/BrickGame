/**
 * @file space_checks.h
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SPACE_CHECKS_H
#define SPACE_CHECKS_H

#include "./fsm.h"

int have_space(game_t *g, UserAction_t button);
int have_rotate_space(game_t *g, int size);
int have_down_space(game_t *g);

#endif // SPACE_CHECKS_H