/**
 * @file fsm_test.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Module for test fsm module functions
 * @version 1.0
 * @date 2024-05-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include_test/fsm_test.h"

//  ============================================================================

START_TEST(updateCurrentState_test) {
  int y_pos = COL / 2 - 2 * SIZE;
  game_t *g = game();
  init_game();
  updateCurrentState();
  int difference = NO;

  int blocks[][BL_MAX][BL_MAX] = {
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{8, 0, 0, 0}, {8, 8, 8, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 3, 0}, {3, 3, 3, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{2, 2, 0, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 5, 5, 0}, {5, 5, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 4, 0, 0}, {4, 4, 4, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 6, 6, 0}, {0, 6, 6, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j += 2) {
      if (FIELD(i, y_pos + j) != blocks[g->current_name][i][j / 2]) {
        difference = YES;
      }
    }
  }

  ck_assert_int_eq(difference, NO);
  destroy_game();
}

START_TEST(userInput_test_1) {
  game_t *g = game();
  init_game();

  userInput(Terminate, 0);
  ck_assert_int_eq(g->info.pause, Terminate);
  userInput(Pause, 0 );
  ck_assert_int_eq(g->info.pause, Pause);
  userInput(Start, 0);
  ck_assert_int_eq(g->info.pause, 0);

  g->info.speed = 0;
  userInput('n', 0);

  destroy_game();
}

START_TEST(userInput_test_2) {
  init_game();

  userInput('n', 0);

  destroy_game();
}

START_TEST(current_time_test) {
  current_time();
  current_time();
}

//  ============================================================================

Suite *fsm_test(void) {
  Suite *tetris = suite_create("\nfsm tests \n");

  TCase *tc_fsm_test = tcase_create("fsm test");
  tcase_add_test(tc_fsm_test, updateCurrentState_test);
  tcase_add_test(tc_fsm_test, userInput_test_1);
  tcase_add_test(tc_fsm_test, userInput_test_2);
  tcase_add_test(tc_fsm_test, current_time_test);
  suite_add_tcase(tetris, tc_fsm_test);

  return tetris;
}