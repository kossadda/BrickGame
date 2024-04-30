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
  // init_screen();
  // attron(COLOR_PAIR(GREEN));
  // menu();
  // attroff(COLOR_PAIR(GREEN));
  // getch();

  game_t game; 

  init_screen();
  init_game(&game);
  init_all_game_fields(&game.gi);
  
  game_loop(&game);
  
  endwin();

  return 0;
}