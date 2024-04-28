#include "./../include/common_gui.h"

void scan_matrix(const GameInfo_t *info) {
  for (int i = 0; i < ROW; i++) {
    for(int j = 0; j < COL; j++) {
      mvaddch(i + 1, j + 1, (info->field[i][j]) ? '.' : ' ');
    }
  }
}

void print_field() {
  int rows = ROW + 1;
  int cols = COL + 1;

  attron(A_BOLD);
  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(0, cols, ACS_URCORNER);
  mvaddch(rows, 0, ACS_LLCORNER);
  mvaddch(rows, cols, ACS_LRCORNER);
  for(int i = 1; i < cols; i++) {
    mvaddch(0, i, ACS_HLINE);
    mvaddch(rows, i, ACS_HLINE);
  }
  for(int i = 1; i < rows; i++) {
    mvaddch(i, 0, ACS_VLINE);
    mvaddch(i, cols, ACS_VLINE);
  }
  attroff(A_BOLD);
}

void init_screen() {
  initscr();
  raw();
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();
}