/**
 * @file field.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef FIELD_H
#define FIELD_H

#include "./../../../brick_game/tetris/include/common.h"

void init_screen();
void init_all_game_fields(game_t *g, UserAction_t act);
void refresh_field(const game_t *g);

#define COLOR_ORANGE 9
#define COLOR_PINK 10

#define RCENTER ((LINES - ROW) / 2)
#define CCENTER ((COLS - END_INFO_COL) / 2)

#endif  // FIELD_H