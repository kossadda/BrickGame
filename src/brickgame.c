/**
 * @file brickgame.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./gui/cli/include/common_gui.h"
#include <time.h>

static void user_input(UserAction_t action, game_t *g, double *lut, bool hold);
static void refresh_all(game_t *game);
static double current_time();

int main() {
  game_t game; 
  UserAction_t action = ' ';
  double last_update_time = current_time();
  // double update_interval = 50;

  init_screen();
  init_game(&game);
  print_field();
  refresh_field(&game.gi);

  while (1) {
    action = getch();
    if(game.gi.pause == Pause) {
      continue;
    } else if(game.gi.pause == Terminate) {
      break;
    } else {
      user_input(action, &game, &last_update_time, 0);
    }
    // napms(1);
  }
  
  endwin();

  return 0;
}

static void user_input(UserAction_t action, game_t *g, double *lut, bool hold) {
  (void)hold;
  switch (action) {
  case Terminate:
    g->gi.pause = Terminate;
    break;
  case Pause:
    g->gi.pause = Pause;
    break;
  case Start:
    g->gi.pause = FALSE;
    break;
  case Right:
  case Left:
    move_block(g, action);
    refresh_all(g);
    break;
  case Down:
    move_down(g);
    refresh_all(g);
    break;
  default:
    if(current_time() - *lut >= g->gi.speed) {
      *lut = current_time();
      move_down(g);
      refresh_all(g);
    }
    break;
  }
}

static void refresh_all(game_t *game) {
  refresh_matrix(game);
  refresh_field(&game->gi);
  refresh();
}

static double current_time() {
  return clock() * 1000 / CLOCKS_PER_SEC;
}