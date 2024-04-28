/**
 * @file tetris.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./../../gui/cli/include/common_gui.h"

int main() {
  Game game; 
  char button = ' ';

  init_game(&game);

  init_screen();
  print_field();
  getch();
  
  for(;button != 'q'; button = getch()) {
    scan_matrix(&game.info);  
  }
  
  endwin();

  return 0;
}