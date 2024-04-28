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

static double current_time() {
  return clock() * 1000 / CLOCKS_PER_SEC;
}

int main() {
  game_t game; 
  char button = ' ';
  double last_update_time = current_time();
  double update_interval = 50;

  init_screen();
  init_game(&game);
  print_field();
  refresh_field(&game.info);

  while (1) {
    button = getch();
    
    if(button == Terminate) {
      break;
    } else if(button != -1) {
      move_block(&game, button);
      refresh_matrix(&game);
      refresh_field(&game.info);
      refresh();
    } else {
      if(current_time() - last_update_time >= update_interval) {
        last_update_time = current_time();
        move_down(&game);
        refresh_matrix(&game);
        refresh_field(&game.info);
        refresh();
      }
    }

    napms(1);
  }
  
  endwin();

  return 0;
}