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

void game_loop(game_t *g) {
  pause(g);

  UserAction_t action = ' ';
  double last_update_time = current_time();
  int score;

  while (g->gi.pause != GAME_OVER) {
    action = getch();

    if (action == 'p') {
      g->theme = (g->theme) ? false : true;
      change_theme((g->theme) ? WHITE : BLACK);
      init_all_game_fields(g, Pause);
      refresh_info(g);
    }

    if (!g->gi.pause) {
      score = g->gi.score;
      user_input(action, g, &last_update_time, 0);

      if (g->change) {
        refresh_next_block(g);
        g->change = false;
      }

      if (score != g->gi.score) {
        refresh_info(g);
      }

      if (!g->gi.pause) {
        refresh_field(g);
        refresh();
      }
    } else if (g->gi.pause == Terminate) {
      print_terminate(g);
      break;
    } else if (g->gi.pause == Pause) {
      pause(g);
    }

    if (g->gi.pause == GAME_OVER) {
      print_game_over(g);
    }

    napms(1);
  }
}