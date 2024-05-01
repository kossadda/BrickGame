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

static void init_main_field(int rows, int cols);

void init_screen() {
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  start_color();
  init_color(COLOR_ORANGE, 1000, 500, 0);
  init_color(COLOR_PINK, 1000, 500, 1000);
  init_pair(WHITE, COLOR_BLACK, COLOR_WHITE);
  init_pair(BLACK, COLOR_WHITE, COLOR_BLACK);
  change_theme(BLACK);
}

void init_all_game_fields(game_t *g) {
  clear();
  char high_score[25];
  sprintf(high_score, "High score: %d", g->gi.high_score);

  attron(A_BOLD);

  init_main_field(PRINT_ROW, PRINT_COL);
  init_info_field(LEVEL_ROW, SCORE_ROW - 1, BEGIN_INFO_COL, END_INFO_COL);
  init_info_field(SCORE_ROW, HSCORE_ROW - 1, BEGIN_INFO_COL, END_INFO_COL);
  init_info_field(HSCORE_ROW, BLOCK_ROW - 1, BEGIN_INFO_COL, END_INFO_COL);
  init_info_field(BLOCK_ROW, PRINT_ROW, BEGIN_INFO_COL, END_INFO_COL);

  print_info(LEVEL_ROW + (SCORE_ROW - LEVEL_ROW) / 2 - 1, BEGIN_INFO_COL,
             END_INFO_COL, "Level: 1");
  print_info(SCORE_ROW + (HSCORE_ROW - SCORE_ROW) / 2 - 1, BEGIN_INFO_COL,
             END_INFO_COL, "Score: 0");
  print_info(HSCORE_ROW + (BLOCK_ROW - HSCORE_ROW) / 2 - 1, BEGIN_INFO_COL,
             END_INFO_COL, high_score);
  print_info(BLOCK_ROW, BEGIN_INFO_COL, END_INFO_COL, "Next figure: ");

  attroff(A_BOLD);
  refresh_next_block(g);
  refresh_field(g);
}

void refresh_field(const game_t *g) {
  char ch;

  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      if (FIELD(i, j)) {
        if (j % SIZE == 0) {
          ch = '[';
        } else if (j % SIZE == SIZE - 1) {
          ch = ']';
        } else {
          ch = '#';
        }
        color_attribut(FIELD(i, j), 1);
        mvaddch(RCENTER + i + 1, CCENTER + j + 1, ch);
        color_attribut(FIELD(i, j), 0);
      } else {
        mvaddch(RCENTER + i + 1, CCENTER + j + 1, ' ');
      }
    }
  }
}

static void init_main_field(int rows, int cols) {
  mvaddch(RCENTER, CCENTER + 0, ACS_ULCORNER);
  mvaddch(RCENTER, CCENTER + cols, ACS_URCORNER);
  mvaddch(RCENTER + rows, CCENTER, ACS_LLCORNER);
  mvaddch(RCENTER + rows, CCENTER + cols, ACS_LRCORNER);

  for (int i = 1; i < cols; i++) {
    mvaddch(RCENTER, CCENTER + i, ACS_HLINE);
    mvaddch(RCENTER + rows, CCENTER + i, ACS_HLINE);
  }

  for (int i = 1; i < rows; i++) {
    mvaddch(RCENTER + i, CCENTER, ACS_VLINE);
    mvaddch(RCENTER + i, CCENTER + cols, ACS_VLINE);
  }
}

void change_theme(short theme) {
  bkgd(COLOR_PAIR(theme));

  init_pair(RED, COLOR_RED, theme);
  init_pair(ORANGE, COLOR_ORANGE, theme);
  init_pair(YELLOW, COLOR_YELLOW, theme);
  init_pair(PINK, COLOR_PINK, theme);
  init_pair(GREEN, COLOR_GREEN, theme);
  init_pair(BLUE, COLOR_BLUE, theme);
  init_pair(PURPLE, COLOR_MAGENTA, theme);
}