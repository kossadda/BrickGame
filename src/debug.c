#include "./brick_game/tetris/include/common.h"

int main() {
  bool differrence = NO;
  game_t *g = game();
  init_game();
  fill_next_block(g);

  int blocks[][4][4] = {
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{8, 0, 0, 0}, {8, 8, 8, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 3, 0}, {3, 3, 3, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{2, 2, 0, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 5, 5, 0}, {5, 5, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 4, 0, 0}, {4, 4, 4, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 6, 6, 0}, {0, 6, 6, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX; j++) {
      if (g->info.next[i][j * SIZE] != blocks[g->next_name][i][j]) {
        differrence = YES;
      }
    }
  }
}