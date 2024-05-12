/**
 * @file brickgame.c
 * @author kossadda (https://github.com/kossadda)
 * @brief The main module that starts the game
 * @version 1.0
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./gui/cli/include/common_gui.h"

static void game_loop();

/**
 * @brief Start of the program
 * 
 * @return int 
 */
int main() {
  init_game();

  init_screen();
  
  game_loop();

  destroy_game();

  endwin();

  return 0;
}

/// @brief Main game loop
static void game_loop() {
  game_t *g = game();
  pause(g);

  UserAction_t action = ' ';
  int score;

  while (g->info.pause != GAME_OVER) {
    int lines = LINES;
    int cols = COLS;

    action = getch();

    if (action == (UserAction_t)THEME) {
      g->theme = (g->theme) ? false : true;
      change_theme((g->theme) ? WHITE : BLACK);
      init_all_game_fields(g, Pause);
      refresh_info(g);
    }

    if (!g->info.pause) {
      score = g->info.score;
      userInput(action, 0);

      if (g->change) {
        refresh_next_block(g);
        g->change = false;
      }

      if (score != g->info.score) {
        refresh_info(g);
      }

      if (!g->info.pause) {
        refresh_field(g);
        refresh();
      }
    } else if (g->info.pause == Terminate) {
      print_terminate(g);
      break;
    } else if (g->info.pause == Pause) {
      pause(g);
    }

    if (g->info.pause == GAME_OVER) {
      print_game_over(g);
    }

    if (lines != LINES || cols != COLS) {
      init_all_game_fields(g, Pause);
      refresh_info(g);
    }

    napms(1);
  }
}