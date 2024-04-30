/**
 * @file info_field_gui.c
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/common_gui.h"

void init_info_field(int begin_row, int end_row, int begin_col, int end_col) {
  mvaddch(RCENTER + begin_row, CCENTER + begin_col, ACS_ULCORNER);
  mvaddch(RCENTER + begin_row, CCENTER + end_col, ACS_URCORNER);
  mvaddch(RCENTER + end_row, CCENTER + begin_col, ACS_LLCORNER);
  mvaddch(RCENTER + end_row, CCENTER + end_col, ACS_LRCORNER);

  for (int i = begin_col + 1; i < end_col; i++) {
    mvaddch(RCENTER + begin_row, CCENTER + i, ACS_HLINE);
    mvaddch(RCENTER + end_row, CCENTER + i, ACS_HLINE);
  }

  for (int i = begin_row + 1; i < end_row; i++) {
    mvaddch(RCENTER + i, CCENTER + begin_col, ACS_VLINE);
    mvaddch(RCENTER + i, CCENTER + end_col, ACS_VLINE);
  }
}

void print_info(int begin_row, int begin_col, int end_col, char *text) {
  attron(A_BOLD);
  int center = begin_col + (end_col - begin_col - strlen(text)) / 2 + 1;

  for (int i = begin_col + 1; i < end_col; i++) {
    mvaddch(RCENTER + begin_row + 1, CCENTER + i, ' ');
  }

  mvaddstr(RCENTER + begin_row + 1, CCENTER + center, text);
  attroff(A_BOLD);
}

void refresh_next_block(const game_t *g) {
  char ch;

  for (int i = 0; i < BL_MAX - 2; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      if (g->gi.next[i][j]) {
        if (j % SIZE == 0)
          ch = '[';
        else if (j % SIZE == SIZE - 1)
          ch = ']';
        else
          ch = 'o';

        color_attribut(g->gi.next[i][j], 1);
        mvaddch(RCENTER + i + FIGURE_ROW, CCENTER + j + 1 + FIGURE_COL, ch);
        color_attribut(g->gi.next[i][j], 0);
      } else {
        mvaddch(RCENTER + i + FIGURE_ROW, CCENTER + j + 1 + FIGURE_COL, ' ');
      }
    }
  }
}

void refresh_info(game_t *g) {
  char temp[25];
  sprintf(temp, "Level: %d", g->gi.level);
  print_info(LEVEL_ROW + (SCORE_ROW - LEVEL_ROW) / 2 - 1, BEGIN_INFO_COL,
             END_INFO_COL, temp);
  sprintf(temp, "Score: %d", g->gi.score);
  print_info(SCORE_ROW + (HSCORE_ROW - SCORE_ROW) / 2 - 1, BEGIN_INFO_COL,
             END_INFO_COL, temp);
}

void color_attribut(int cell, int mode) {
  switch (cell) {
  case RED:
    (mode) ? attron(COLOR_PAIR(RED)) : attroff(COLOR_PAIR(RED));
    break;
  case ORANGE:
    (mode) ? attron(COLOR_PAIR(ORANGE)) : attroff(COLOR_PAIR(ORANGE));
    break;
  case YELLOW:
    (mode) ? attron(COLOR_PAIR(YELLOW)) : attroff(COLOR_PAIR(YELLOW));
    break;
  case GREEN:
    (mode) ? attron(COLOR_PAIR(GREEN)) : attroff(COLOR_PAIR(GREEN));
    break;
  case PURPLE:
    (mode) ? attron(COLOR_PAIR(PURPLE)) : attroff(COLOR_PAIR(PURPLE));
    break;
  case BLUE:
    (mode) ? attron(COLOR_PAIR(BLUE)) : attroff(COLOR_PAIR(BLUE));
    break;
  case PINK:
    (mode) ? attron(COLOR_PAIR(PINK)) : attroff(COLOR_PAIR(PINK));
  }
}