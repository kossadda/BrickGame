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

static void print_menu(game_t *g);
static void print_pause(game_t *g);
static void print_with_attributes(game_t *g, const char *text[], const char *dialog1, const char *dialog2, int color);

void pause(game_t *g) {
  UserAction_t action = g->gi.pause;
  nodelay(stdscr, FALSE);

  while (g->gi.pause != 0) {
    clear();
    (g->gi.pause == -Pause) ? print_menu(g) : print_pause(g);
    refresh();

    action = getch();

    if(action == Start) {
      init_all_game_fields(g, Start);
      g->gi.pause = false;
    } else if(action == Terminate) {
      g->gi.pause = Terminate;
      break;
    } else if(action == 'p') {
      g->theme = (g->theme) ? false : true;
      change_theme((g->theme) ? WHITE : BLACK);
      init_all_game_fields(g, Pause);
    }
  }

  nodelay(stdscr, TRUE);
}

void print_game_over(game_t *g) {
  nodelay(stdscr, FALSE);
  clear();

  const char *text[] =
  {
      " ______  _______  __   __  ______ ",
      "|      ||   _   ||  |_|  ||      |",
      "|   ___||  |_|  ||       ||   ___|",
      "|  | __ |       ||       ||  |___ ",
      "|  ||  ||       ||       ||   ___|",
      "|  |_| ||   _   || ||_|| ||  |___ ",
      "|______||__| |__||_|   |_||______|",
      "                                  ",
      " _____  __   __  ______  ______   ",
      "|     ||  | |  ||      ||    _ |  ",
      "|  _  ||  |_|  ||   ___||   | ||  ",
      "| | | ||       ||  |___ |   |_||_ ",
      "| |_| ||       ||   ___||    __  |",
      "|     | |     | |  |___ |   |  | |",
      "|_____|  |___|  |______||___|  |_|"
  };
  char *dialog1 = "Press any key to exit";
  char dialog2[25];
  sprintf(dialog2, "Good game! Your score: %d", g->gi.score);

  print_with_attributes(g, text, dialog1, dialog2, RED);
  getch();
}

static void print_menu(game_t *g) {
  const char *text[] =
  {
      " ______  ______  ______  _____    __   ______ ",
      "|      ||      ||      ||   _ |  |  | |      |",
      "|_    _||   ___||_    _||  | ||  |  | |  ____|",
      "  |  |  |  |___   |  |  |  |_||_ |  | | |____ ",
      "  |  |  |   ___|  |  |  |   __  ||  | |____  |",
      "  |  |  |  |___   |  |  |  |  | ||  |  ____| |",
      "  |__|  |______|  |__|  |__|  |_||__| |______|"
  };
  const char *dialog = "Press \'e\' to start";
  print_with_attributes(g, text, dialog, NULL, GREEN);
}

static void print_pause(game_t *g) {
  const char *text[] =
  {
    "  _______  _______  __   __  _______  _______ ",
    " |       ||       ||  | |  ||       ||       |",
    " |    _  ||   _   ||  | |  ||  _____||    ___|",
    " |   |_| ||  |_|  ||  | |  || |_____ |   |___ ",
    " |    ___||   _   ||  |_|  ||_____  ||    ___|",
    " |   |    |  | |  ||       | _____| ||   |___ ",
    " |___|    |__| |__||_______||_______||_______|"
  };
  const char *dialog = "Press \'e\' to continue";
  print_with_attributes(g, text, dialog, NULL, BLUE);
}

static void print_with_attributes(game_t *g, const char *text[], const char *dialog1, const char *dialog2, int color) {
  attron(A_BOLD | COLOR_PAIR(g->theme ? BLACK : color));
  init_info_field(LEVEL_ROW, PRINT_ROW, 0, END_INFO_COL);

  int x_center = LINES / 2 - ((dialog2) ? 9 : 4);
  int y_center = (COLS - strlen(*text)) / 2;
  int i;

  for(i = 0; i < ((dialog2) ? 15 : 7); i++) {
    mvaddstr(x_center + i, y_center, text[i]);
  }
  
  if(dialog2) {
    mvaddstr(x_center + i + 2, (COLS - strlen(dialog2)) / 2, dialog2);
    attron(A_BLINK);
    mvaddstr(x_center + i + 4, (COLS - strlen(dialog1)) / 2, dialog1);
    attroff(A_BLINK);
  } else {
    attron(A_BLINK);
    mvaddstr(x_center + i + 2, (COLS - strlen(dialog1)) / 2, dialog1);
    attroff(A_BLINK);
  }

  attroff(A_BOLD | COLOR_PAIR(g->theme ? BLACK : BLUE));
}