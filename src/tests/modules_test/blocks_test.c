/**
 * @file
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-05-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include_test/blocks_test.h"

//  ============================================================================

START_TEST(fill_next_block_test_1) {
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
  ck_assert_int_eq(differrence, NO);
}

// START_TEST(spawn_block_test_1) {

// }


//  ============================================================================

Suite *fill_next_block_test(void) {
  Suite *tetris = suite_create("\nfill next block\n");

  TCase *tc_test_fill_next_block = tcase_create("test fill next block");
  tcase_add_test(tc_test_fill_next_block, fill_next_block_test_1);
  suite_add_tcase(tetris, tc_test_fill_next_block);

  return tetris;
}