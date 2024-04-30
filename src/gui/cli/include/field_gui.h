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
void init_all_game_fields(game_info_t *info);
void refresh_field(const game_info_t *info);

#endif  // FIELD_H