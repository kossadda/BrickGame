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

int main() {
  game_t game; 
  char button = ' ';

  init_screen();
  init_game(&game);
  print_field();
  refresh_field(&game.info);
  refresh();

  while (1) {
    button = getch();
    
    if(button == 'q') {
      break;
    } else if(button != -1) {
      move_block(&game, button);
    }

    refresh_matrix(&game);
    refresh_field(&game.info);
    refresh();
    napms(20);
  }
  
  endwin();

  return 0;
}