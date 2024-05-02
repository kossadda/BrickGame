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
static void print_guide(game_t *g, int color);
static void print_with_attributes(game_t *g, const char *text[], int msize,
                                  const char *dialog1, const char *dialog2,
                                  int color);

void pause(game_t *g) {
  UserAction_t action = g->info.pause;
  nodelay(stdscr, FALSE);

  while (g->info.pause != 0) {
    clear();
    (g->info.pause == -Pause) ? print_menu(g) : print_pause(g);
    refresh();

    action = getch();

    if (action == Start) {
      init_all_game_fields(g, Start);
      g->info.pause = false;
    } else if (action == Terminate) {
      g->info.pause = Terminate;
      break;
    } else if (action == (UserAction_t)THEME) {
      g->theme = (g->theme) ? false : true;
      change_theme((g->theme) ? WHITE : BLACK);
      init_all_game_fields(g, Pause);
    } else if (action == (UserAction_t)GUIDE && g->info.pause == -Pause) {
      print_guide(g, GREEN);
    }
  }

  nodelay(stdscr, TRUE);
}

void print_game_over(game_t *g) {
  nodelay(stdscr, FALSE);
  clear();

  char dialog2[25];
  const char *text[] = {" ______  _______  __   __  ______ ",
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
                        "|_____|  |___|  |______||___|  |_|"};
  char *dialog1 = " Press any key to exit";
  sprintf(dialog2, "Good game! Your score: %d", g->info.score);

  print_with_attributes(g, text, 15, dialog1, dialog2, GREEN);
  getch();
}

static void print_menu(game_t *g) {
  const char *text[] = {" ______  ______  ______  _____    __   ______ ",
                        "|      ||      ||      ||   _ |  |  | |      |",
                        "|_    _||   ___||_    _||  | ||  |  | |  ____|",
                        "  |  |  |  |___   |  |  |  |_||_ |  | | |____ ",
                        "  |  |  |   ___|  |  |  |   __  ||  | |____  |",
                        "  |  |  |  |___   |  |  |  |  | ||  |  ____| |",
                        "  |__|  |______|  |__|  |__|  |_||__| |______|"};
  const char *dialog1 = "Press \'s\' to start";
  const char *dialog2 = "\'g\' to view the button assignments";
  print_with_attributes(g, text, 7, dialog1, dialog2, GREEN);
}

static void print_pause(game_t *g) {
  const char *text[] = {"  _______  _______  __   __  _______  _______ ",
                        " |       ||       ||  | |  ||       ||       |",
                        " |    _  ||   _   ||  | |  ||  _____||    ___|",
                        " |   |_| ||  |_|  ||  | |  || |_____ |   |___ ",
                        " |    ___||   _   ||  |_|  ||_____  ||    ___|",
                        " |   |    |  | |  ||       | _____| ||   |___ ",
                        " |___|    |__| |__||_______||_______||_______|"};
  const char *dialog = "Press \'s\' to continue";
  print_with_attributes(g, text, 7, dialog, NULL, BLUE);
}

void print_terminate(game_t *g) {
  nodelay(stdscr, FALSE);
  clear();
  const char *text[] = {"   ______   __   __   ___   ______ ",
                        "  |      | |  |_|  | |   | |      |",
                        "  |   ___| |       | |   | |_    _|",
                        "  |  |___  |       | |   |   |  |  ",
                        "  |   ___|  |     |  |   |   |  |  ",
                        "  |  |___  |   _   | |   |   |  |  ",
                        "  |______| |__| |__| |___|   |__|  "};
  const char *dialog = "Press any key to exit";
  print_with_attributes(g, text, 7, dialog, NULL, RED);
  getch();
}

static void print_guide(game_t *g, int color) {
  nodelay(stdscr, FALSE);
  clear();
  attron(A_BOLD | COLOR_PAIR(g->theme ? BLACK : color));
  init_info_field(LEVEL_ROW, PRINT_ROW, 0, END_INFO_COL);
  char *text[] = {"  \'s\'   -   start game", "  \'x\'   -   exit game",
                  "  \'p\'   -   pause game", "  \'t\'   -   switch theme",
                  "  \' \'   -   move left",  "  \' \'   -   move right",
                  "  \' \'   -   speed up",   " Space  -   rotate"};
  int x_center = LINES / 2 - 7;
  int y_center = (COLS - strlen(text[3])) / 2;

  for (int i = 0; i < 8; i += 1) {
    mvaddstr(x_center + i * 2, y_center, text[i]);
  }
  mvaddch(x_center + 4 * 2, y_center + 3, ACS_LARROW);
  mvaddch(x_center + 5 * 2, y_center + 3, ACS_RARROW);
  mvaddch(x_center + 6 * 2, y_center + 3, ACS_DARROW);

  attroff(A_BOLD | COLOR_PAIR(g->theme ? BLACK : BLUE));

  getch();
}

static void print_with_attributes(game_t *g, const char *text[], int msize,
                                  const char *dialog1, const char *dialog2,
                                  int color) {
  attron(A_BOLD | COLOR_PAIR(g->theme ? BLACK : color));
  init_info_field(LEVEL_ROW, PRINT_ROW, 0, END_INFO_COL);

  int x_center = LINES / 2 - ((msize == 15) ? 9 : 4);
  int y_center = (COLS - strlen(*text)) / 2;
  int i;

  for (i = 0; i < msize; i++) {
    mvaddstr(x_center + i, y_center, text[i]);
  }

  if (dialog2) {
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