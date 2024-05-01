/**
 * @file menu_gui.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MENU_GUI_H
#define MENU_GUI_H

#include "./../../../brick_game/tetris/include/common.h"

void pause(game_t *g);
void print_game_over(game_t *g);
void print_terminate(game_t *g);

#endif  // MENU_GUI_H