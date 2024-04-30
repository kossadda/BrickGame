/**
 * @file info_field_gui.h
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef INFO_FIELD_GUI_H
#define INFO_FIELD_GUI_H

#include "./../../../brick_game/tetris/include/common.h"

#define PRINT_ROW (ROW + 1)
#define PRINT_COL (COL + 1)

#define BEGIN_INFO_COL (PRINT_COL + 2)
#define END_INFO_COL (BEGIN_INFO_COL + ROW + 5)

#define LEVEL_ROW 0
#define SCORE_ROW (PRINT_ROW / 5 + 1)
#define HSCORE_ROW (PRINT_ROW / 5 * 2 + 2)
#define BLOCK_ROW (PRINT_ROW / 5 * 3 + 3)
#define BLOCK_ROW (PRINT_ROW / 5 * 3 + 3)

#define FIGURE_ROW (BLOCK_ROW + (PRINT_ROW - BLOCK_ROW) / 2)
#define FIGURE_COL (BEGIN_INFO_COL + (END_INFO_COL - BEGIN_INFO_COL - BL_MAX * SIZE) / 2)

void init_info_field(int begin_row, int end_row, int begin_col, int end_col);
void print_info(int begin_row, int begin_col, int end_col, char *text);
void refresh_next_block(const game_info_t *info);
void refresh_info(game_t *g);

#endif // INFO_FIELD_GUI_H