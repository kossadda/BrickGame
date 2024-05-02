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
static void attrprint(game_t *g, const char *text[], int msize,
                      const char *dialog1, const char *dialog2, int color,
                      int shift);

void pause(game_t *g) {
  UserAction_t action = g->info.pause;
  nodelay(stdscr, FALSE);
  int field_size = 0;
  int theme;

  while (g->info.pause != 0) {
    theme = g->theme;

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
    } else if (g->info.pause == -Pause) {
      if (action == (UserAction_t)GUIDE) {
        print_guide(g, GREEN);
      } else if (action == (UserAction_t)CHANGE_SIZE) {
        destroy_game();
        int sizes[][2] = {{10, 20}, {10, 30}, {10, 40}, {20, 20},
                          {20, 30}, {20, 40}, {30, 20}, {30, 30},
                          {30, 40}, {40, 20}, {40, 30}, {40, 40}};
        field_size++;
        if(field_size > 11) {
          field_size = 0;
        }
        COL = sizes[field_size][0] * field()->block_size;
        ROW = sizes[field_size][1];
        init_game();
        g->theme = theme;
      } else if (action == (UserAction_t)CHANGE_BLOCK) {
        destroy_game();
        COL /=  field()->block_size;
        field()->block_size = (field()->block_size == 2) ? 3 : 2;
        COL *=  field()->block_size;
        init_game();
        g->theme = theme;
      }
    }
  }

  nodelay(stdscr, TRUE);
}

void print_game_over(game_t *g) {
  nodelay(stdscr, FALSE);
  clear();

  char dialog2[25];
  const char *text[] = {" ______  _______  __   __  ______ ",
                        "|   ___||       ||  |_|  ||   ___|",
                        "|  | __ |   _   ||       ||  |___ ",
                        "|  ||  ||  |_|  ||       ||   ___|",
                        "|  |_| ||   _   || ||_|| ||  |___ ",
                        "|______||__| |__||_|   |_||______|",
                        " _____  __   __  ______  ______   ",
                        "|  _  ||  | |  ||   ___||   _  |  ",
                        "| | | ||  |_|  ||  |___ |  |_| |_ ",
                        "| | | ||       ||   ___||   __   |",
                        "| |_| | |     | |  |___ |  |  |  |",
                        "|_____|  |___|  |______||__|  |__|"};
  char *dialog1 = " Press any key to exit";
  sprintf(dialog2, "Good game! Your score: %d", g->info.score);

  attrprint(g, text, 12, dialog1, dialog2, GREEN, 8);
  getch();
}

static void print_menu(game_t *g) {
  const char *text[] = {" ______  ______  ______  ______    __   ______ ",
                        "|_    _||   ___||_    _||   _  |  |  | |  ____|",
                        "  |  |  |  |___   |  |  |  |_| |_ |  | | |____ ",
                        "  |  |  |   ___|  |  |  |   __   ||  | |____  |",
                        "  |  |  |  |___   |  |  |  |  |  ||  |  ____| |",
                        "  |__|  |______|  |__|  |__|  |__||__| |______|"};
  const char *dialog1 = "Press \'s\' to start";
  const char *dialog2 = "\'g\' to view the button assignments";
  attrprint(g, text, 6, dialog1, dialog2, GREEN, 5);

  char block_size[25];
  char field_size[25];
  sprintf(block_size, "Block: %s", (SIZE == 2) ? "small" : "big");
  sprintf(field_size, "Field: %dx%d", COL / SIZE, ROW);

  attron(A_BOLD | COLOR_PAIR(g->theme ? BLACK : GREEN));

  int x_center = LINES / 2 + 8;
  int block_y_center = (COLS - strlen(block_size) - strlen(field_size)) / 2 - 3;
  int field_y_center = block_y_center + strlen(block_size) + 5;

  mvaddstr(x_center, block_y_center, block_size);
  mvaddstr(x_center, field_y_center, field_size);

  attroff(A_BOLD | COLOR_PAIR(g->theme ? BLACK : BLUE));
}

static void print_pause(game_t *g) {
  const char *text[] = {"  _______  _______  __   __  _______  _______ ",
                        " |       ||       ||  | |  ||       ||       |",
                        " |   |_| ||  |_|  ||  | |  || |_____ |   |___ ",
                        " |    ___||   _   ||  |_|  ||_____  ||    ___|",
                        " |   |    |  | |  ||       | _____| ||   |___ ",
                        " |___|    |__| |__||_______||_______||_______|"};
  const char *dialog = "Press \'s\' to continue";
  attrprint(g, text, 6, dialog, NULL, BLUE, 3);
}

void print_terminate(game_t *g) {
  nodelay(stdscr, FALSE);
  clear();
  const char *text[] = {"   ______   __   __   ___   ______ ",
                        "  |      | |  |_|  | |   | |      |",
                        "  |  |___  |       | |   |   |  |  ",
                        "  |   ___|  |     |  |   |   |  |  ",
                        "  |  |___  |   _   | |   |   |  |  ",
                        "  |______| |__| |__| |___|   |__|  "};
  const char *dialog = "Press any key to exit";
  attrprint(g, text, 6, dialog, NULL, RED, 3);
  getch();
}

static void print_guide(game_t *g, int color) {
  nodelay(stdscr, FALSE);
  clear();
  attron(A_BOLD | COLOR_PAIR(g->theme ? BLACK : color));
  init_info_field(LEVEL_ROW, PRINT_ROW, 0, END_INFO_COL);
  char *text[] = {"  \'s\'   -   start game", "  \'x\'   -   exit game",
                  "  \'p\'   -   pause game", "  \'t\'   -   switch theme",
                  "  \'v\'   -   swicth field", "  \'b\'   -   switch block",
                  "  \' \'   -   move left",  "  \' \'   -   move right",
                  "  \' \'   -   speed up",   " Space  -   rotate"};
  int x_center = LINES / 2 - 4;
  int y_center = (COLS - strlen(text[3])) / 2;

  for (int i = 0; i < 10; i += 1) {
    mvaddstr(x_center + i, y_center, text[i]);
  }
  mvaddch(x_center + 6, y_center + 3, ACS_LARROW);
  mvaddch(x_center + 7, y_center + 3, ACS_RARROW);
  mvaddch(x_center + 8, y_center + 3, ACS_DARROW);

  attroff(A_BOLD | COLOR_PAIR(g->theme ? BLACK : BLUE));

  getch();
}

static void attrprint(game_t *g, const char *text[], int msize,
                      const char *dialog1, const char *dialog2, int color,
                      int shift) {
  attron(A_BOLD | COLOR_PAIR(g->theme ? BLACK : color));
  init_info_field(LEVEL_ROW, PRINT_ROW, 0, END_INFO_COL);

  int x_center = LINES / 2 - shift;
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