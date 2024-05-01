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

  init_game(&game);
  init_screen();
  init_all_game_fields(&game);
  
  game_loop(&game);
  endwin();

  return 0;
}
