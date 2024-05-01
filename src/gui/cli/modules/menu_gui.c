/**
 * @file menu_gui.c
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/common_gui.h"

void menu() {

}

void print_pause() {
  attron(A_BOLD | COLOR_PAIR(GREEN));
  init_info_field(LEVEL_ROW, PRINT_ROW, 0, END_INFO_COL);
  const char *text[] =
  {
    " _______  _______  __   __  _______  _______ ",
    "|       ||       ||  | |  ||       ||       |",
    "|    _  ||   _   ||  | |  ||  _____||    ___|",
    "|   |_| ||  |_|  ||  | |  || |_____ |   |___ ",
    "|    ___||   _   ||  |_|  ||_____  ||    ___|",
    "|   |    |  | |  ||       | _____| ||   |___ ",
    "|___|    |__| |__||_______||_______||_______|"
  };
  const char *dialog = "Press \'e\' to continue";

  int x_center = LINES / 2 - 4;
  int y_center = (COLS - strlen(*text)) / 2;
  int i;

  for(i = 0; i < 7; i++) {
    mvaddstr(x_center + i, y_center, text[i]);
  }
  
  attron(A_BLINK);
  mvaddstr(x_center + i + 2, y_center + strlen(dialog) / 2 + 1, dialog);
  attroff(A_BLINK);

  attroff(A_BOLD | COLOR_PAIR(GREEN));
}

void pause(game_t *g) {
  UserAction_t ch;

  nodelay(stdscr, FALSE);

  while (g->gi.pause == Pause) {
    clear();
    print_pause();
    refresh();

    ch = getch();

    if(ch == Start) {
      g->gi.pause = false;
      init_all_game_fields(g);
    } else if(ch == Terminate) {
      g->gi.pause = Terminate;
    }
  }

  nodelay(stdscr, TRUE);
}