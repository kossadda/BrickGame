#include "./../include/common_gui.h"

void init_screen() {
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

void print_field() {
  int rows = ROW + 1;
  int cols = COL + 1;

  attron(A_BOLD);
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
  attroff(A_BOLD);
}

void refresh_field(const game_info_t *info) {
  char ch;

  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      if (info->field[i][j]) {
        if (j % BLOCK_SIZE == 0)
          ch = '[';
        else if (j % BLOCK_SIZE == BLOCK_SIZE - 1)
          ch = ']';
        else
          ch = 'o';
        mvaddch(i + 1, j + 1, ch);
      } else {
        mvaddch(i + 1, j + 1, ' ');
      }
    }
  }
}
