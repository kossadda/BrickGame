/**
 * @file field.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header with field_gui.c module function declarations
 * @version 1.0
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _FIELD_GUI_H_
#define _FIELD_GUI_H_

#include "./../../../brick_game/tetris/include/common.h"

void init_screen();
void init_all_game_fields(const game_t *g, UserAction_t act);
void refresh_field(const game_t *g);

/// @brief Additional color (orange)
#define COLOR_ORANGE 9

/// @brief Additional color (pink)
#define COLOR_PINK 10

/// @brief Determining the center row relative to the size of the console window
#define RCENTER ((LINES - ROW) / 2)

/// @brief Determining the center col relative to the size of the console window
#define CCENTER ((COLS - END_INFO_COL) / 2)

#endif  // _FIELD_GUI_H_