/**
 * @file menu_gui.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header with menu_gui.c module function declarations
 * @version 1.0
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _MENU_GUI_H_
#define _MENU_GUI_H_

#include "./../../../brick_game/tetris/include/common.h"

void pause(game_t *g);
void print_game_over(const game_t *g);
void print_terminate(const game_t *g);

#endif  // _MENU_GUI_H_