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

START_TEST(fill_next_block_test) {
  bool differrence = NO;
  game_t *g = game();
  init_game();

  for(int i = 0; i < 50; i++) {
    fill_next_block(g);
  }

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

START_TEST(spawn_block_test) {
  bool differrence = NO;
  game_t *g = game();
  init_game();
  int matrix[BL_MAX][BL_MAX];

  for(int i = 0; i < BL_MAX; i++) {
    for(int j = 0; j < BL_MAX; j++) {
      matrix[i][j] = g->info.next[i][j * SIZE];
    }
  }

  spawn_block(g);

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX; j++) {
      if(g->block[i][j * SIZE].cell != matrix[i][j]) {
        differrence = YES;
      }
    }
  }

  ck_assert_int_eq(differrence, NO);
}

START_TEST(game_over_test) {
  game_t *g = game();
  init_game();
  
  for (int j = 0; j < COL; j++) {
    FIELD(0, j) = 1;
  }
  g->info.score = 10000;

  spawn_block(g);

  ck_assert_int_eq(g->info.pause, GAME_OVER);
}

START_TEST(clean_one_line_test) {
  game_t *g = game();
  init_game();
  
  for(int i = ROW - 1; i > ROW - 1 - 1; i--)  {
    for (int j = 0; j < COL; j++) {
      FIELD(i, j) = 1;
    }
  }

  clean_line(g);

  ck_assert_int_eq(g->info.score, ONE_LINE);
  ck_assert_int_eq(g->info.level, 1);
}

START_TEST(clean_two_line_test) {
  game_t *g = game();
  init_game();
  
  for(int i = ROW - 1; i > ROW - 1 - 2; i--)  {
    for (int j = 0; j < COL; j++) {
      FIELD(i, j) = 1;
    }
  }

  clean_line(g);

  ck_assert_int_eq(g->info.score, TWO_LINE);
  ck_assert_int_eq(g->info.level, 1);
}

START_TEST(clean_three_line_test) {
  game_t *g = game();
  init_game();
  
  for(int i = ROW - 1; i > ROW - 1 - 3; i--)  {
    for (int j = 0; j < COL; j++) {
      FIELD(i, j) = 1;
    }
  }

  clean_line(g);

  ck_assert_int_eq(g->info.score, THREE_LINE);
  ck_assert_int_eq(g->info.level, 2);
}

START_TEST(clean_four_line_test) {
  game_t *g = game();
  init_game();
  
  for(int i = ROW - 1; i > ROW - 1 - 4; i--)  {
    for (int j = 0; j < COL; j++) {
      FIELD(i, j) = 1;
    }
  }

  g->info.score = 4800;

  clean_line(g);

  ck_assert_int_eq(g->info.score, 4800 + FOUR_LINE);
  ck_assert_int_eq(g->info.level, 10);
}

//  ============================================================================

Suite *blocks_test(void) {
  Suite *tetris = suite_create("\nblocks_test\n");

  TCase *tc_blocks_test = tcase_create("blocks_test");
  tcase_add_test(tc_blocks_test, fill_next_block_test);
  tcase_add_test(tc_blocks_test, spawn_block_test);
  tcase_add_test(tc_blocks_test, game_over_test);
  tcase_add_test(tc_blocks_test, clean_one_line_test);
  tcase_add_test(tc_blocks_test, clean_two_line_test);
  tcase_add_test(tc_blocks_test, clean_three_line_test);
  tcase_add_test(tc_blocks_test, clean_four_line_test);
  suite_add_tcase(tetris, tc_blocks_test);

  return tetris;
}