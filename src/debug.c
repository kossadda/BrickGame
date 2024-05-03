#include "./brick_game/tetris/include/common.h"

int main() {
  game_t *g = game();
  init_game();
  
  for(int i = ROW - 1; i > ROW - 1 - 2; i--) {
    for (int j = 0; j < COL; j++) {
      FIELD(i, j) = 1;
    }
  }

  clean_line(g);
}