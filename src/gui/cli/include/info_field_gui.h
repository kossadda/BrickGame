/**
 * @file info_field_gui.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header with info_field_gui.c module function declarations
 * @version 1.0
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _INFO_FIELD_GUI_H_
#define _INFO_FIELD_GUI_H_

#include "./../../../brick_game/tetris/include/common.h"

/// @brief Number of rows of the playing field
#define PRINT_ROW (ROW + 1)

/// @brief Number of cols of the playing field
#define PRINT_COL (COL + 1)

/// @brief Information column start position
#define BEGIN_INFO_COL (PRINT_COL + 2)

/// @brief Information column end position
#define END_INFO_COL (BEGIN_INFO_COL + ROW + 5)

/// @brief Level field start row
#define LEVEL_ROW 0

/// @brief Score field start row
#define SCORE_ROW (PRINT_ROW / 5 + 1)

/// @brief High score field start row
#define HSCORE_ROW (PRINT_ROW / 5 * 2 + 2)

/// @brief Next figure field start row
#define BLOCK_ROW (PRINT_ROW / 5 * 3 + 3)

/// @brief Next figure start row
#define FIGURE_ROW (BLOCK_ROW + (PRINT_ROW - BLOCK_ROW) / 2)

/// @brief Next figure start col
#define FIGURE_COL \
  (BEGIN_INFO_COL + (END_INFO_COL - BEGIN_INFO_COL - BL_MAX * SIZE) / 2)

void init_info_field(int begin_row, int end_row, int begin_col, int end_col);
void print_info(int begin_row, int begin_col, int end_col, char *text);
void refresh_next_block(const game_t *g);
void refresh_info(game_t *g);

#endif  // _INFO_FIELD_GUI_H_