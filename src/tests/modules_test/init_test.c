/**
 * @file init_test.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Module for test init module functions
 * @version 1.0
 * @date 2024-05-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include_test/blocks_test.h"

//  ============================================================================

START_TEST(init_game_test) {
  game_t *g = game();
  init_game();
  int allocate = YES;

  if (!g->info.field || !g->info.next || !g->block) {
    allocate = NO;
  }
  for (int i = 0; i < ROW; i++) {
    if (!g->info.field[i]) {
      allocate = NO;
    }
  }
  for (int i = 0; i < BL_MAX; i++) {
    if (!g->info.next || !g->block) {
      allocate = NO;
    }
  }

  ck_assert_int_eq(allocate, YES);
  ck_assert_int_eq(g->info.score, 0);
  ck_assert_int_eq(g->info.level, 1);
  ck_assert_int_eq(g->info.speed, START_SPEED);
  ck_assert_int_eq(g->info.pause, -Pause);
  ck_assert_int_eq(g->theme, BLACK);
  destroy_game();
}

START_TEST(destroy_game_test) {
  game_t *g = game();
  destroy_game();
  int allocate = NO;
  init_game();
  destroy_game();

  if (g->info.field || g->info.next || g->block) {
    allocate = YES;
  }

  ck_assert_int_eq(allocate, NO);
}

START_TEST(set_high_score_test) {
  game_t *g = game();
  int check = 2500;

  char path[255];
  get_txt_file_path(path);
  FILE *score = fopen(path, "w");
  if (score) {
    fprintf(score, "%d", check);
    fclose(score);
  }
  init_game();

  ck_assert_int_eq(g->info.high_score, check);

  destroy_game();
}

//  ============================================================================

Suite *init_test(void) {
  Suite *tetris = suite_create("\ninit tests \n");

  TCase *tc_init_test = tcase_create("init test");
  tcase_add_test(tc_init_test, init_game_test);
  tcase_add_test(tc_init_test, destroy_game_test);
  tcase_add_test(tc_init_test, set_high_score_test);
  suite_add_tcase(tetris, tc_init_test);

  return tetris;
}