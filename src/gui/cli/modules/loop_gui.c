/**
 * @file loop.c
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/common_gui.h"

void game_loop() {
  game_t *g = game();
  pause(g);

  UserAction_t action = ' ';
  int score;

  while (g->info.pause != GAME_OVER) {
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

    napms(1);
  }
}