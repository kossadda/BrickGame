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
