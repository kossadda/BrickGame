#include "./../include/field_gui.h"

void print_field() {
  int rows = ROWS + 1;
  int cols = COLS + 1;
  
  initscr();
  raw();
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();
  
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