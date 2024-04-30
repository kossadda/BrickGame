/**
 * @file field_gui.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./../include/common_gui.h"

static void print_info_field(int begin_row, int end_row, int begin_col, int end_col);
static void print_main_field(int rows, int cols);

void init_screen() {
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

void print_field(game_info_t *info) {

  char high_score[25];
  sprintf(high_score, "High score: %d", info->high_score);

  attron(A_BOLD);
  print_main_field(PRINT_ROW, PRINT_COL);
  print_info_field(LEVEL_ROW, SCORE_ROW - 1, BEGIN_INFO_COL, END_INFO_COL);
  print_info_field(SCORE_ROW, HSCORE_ROW - 1, BEGIN_INFO_COL, END_INFO_COL);
  print_info_field(HSCORE_ROW, BLOCK_ROW - 1, BEGIN_INFO_COL, END_INFO_COL);
  print_info_field(BLOCK_ROW, PRINT_ROW, BEGIN_INFO_COL, END_INFO_COL);

  print_info(LEVEL_ROW + (SCORE_ROW - LEVEL_ROW) / 2 - 1, BEGIN_INFO_COL, END_INFO_COL, "Level: 0");
  print_info(SCORE_ROW + (HSCORE_ROW - SCORE_ROW) / 2 - 1, BEGIN_INFO_COL, END_INFO_COL, "Score: 0");
  print_info(HSCORE_ROW + (BLOCK_ROW - HSCORE_ROW) / 2 - 1, BEGIN_INFO_COL, END_INFO_COL, high_score);
  print_info(BLOCK_ROW, BEGIN_INFO_COL, END_INFO_COL, "Next:");
  attroff(A_BOLD);
  refresh_next_block(info);
}

void print_info(int begin_row, int begin_col, int end_col, char *text) {
  int center = begin_col + (end_col - begin_col - strlen(text)) / 2 + 1;

  for(int i = begin_col + 1; i < end_col; i++) {
    mvaddch(begin_row + 1, i, ' ');
  }

  mvaddstr(begin_row + 1, center, text);
}

static void print_main_field(int rows, int cols) {
  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(0, cols, ACS_URCORNER);
  mvaddch(rows, 0, ACS_LLCORNER);
  mvaddch(rows, cols, ACS_LRCORNER);
  for (int i = 1; i < cols; i++) {
    mvaddch(0, i, ACS_HLINE);
    mvaddch(rows, i, ACS_HLINE);
  }
  for (int i = 1; i < rows; i++) {
    mvaddch(i, 0, ACS_VLINE);
    mvaddch(i, cols, ACS_VLINE);
  }
}

static void print_info_field(int begin_row, int end_row, int begin_col, int end_col) {
  mvaddch(begin_row, begin_col, ACS_ULCORNER);
  mvaddch(begin_row, end_col, ACS_URCORNER);
  mvaddch(end_row, begin_col, ACS_LLCORNER);
  mvaddch(end_row, end_col, ACS_LRCORNER);
  for (int i = begin_col + 1; i < end_col; i++) {
    mvaddch(begin_row, i, ACS_HLINE);
    mvaddch(end_row, i, ACS_HLINE);
  }
  for (int i = begin_row + 1; i < end_row; i++) {
    mvaddch(i, begin_col, ACS_VLINE);
    mvaddch(i, end_col, ACS_VLINE);
  }
}

void refresh_next_block(const game_info_t *info) {
  char ch;

  for (int i = 0; i < BL_MAX - 2; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      if (info->next[i][j]) {
        if (j % SIZE == 0)
          ch = '[';
        else if (j % SIZE == SIZE - 1)
          ch = ']';
        else
          ch = 'o';
        mvaddch(i + FIGURE_ROW, j + 1 + FIGURE_COL, ch);
      } else {
        mvaddch(i + FIGURE_ROW, j + 1 + FIGURE_COL, ' ');
      }
    }
  }
}

void refresh_field(const game_info_t *info) {
  char ch;

  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      if (info->field[i][j]) {
        if (j % SIZE == 0) {
          ch = '[';
        } else if (j % SIZE == SIZE - 1) {
          ch = ']';
        } else {
          ch = 'o';
        }
        mvaddch(i + 1, j + 1, ch);
      } else {
        mvaddch(i + 1, j + 1, ' ');
      }
    }
  }
}
