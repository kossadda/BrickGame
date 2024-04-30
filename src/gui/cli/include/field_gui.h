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

void init_screen();
void print_field(game_info_t *info);
void refresh_field(const game_info_t *info);
void refresh_next_block(const game_info_t *info);
void print_info(int begin_row, int begin_col, int end_col, char *text);

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

#endif  // FIELD_H