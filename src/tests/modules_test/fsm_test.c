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

START_TEST(userInput_left_test) {
  game_t *g = game();
  init_game();
  int difference = NO;

  int cell_Y[BL_MAX][BL_MAX * SIZE];

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      cell_Y[i][j] = Y(i, j);
    }
  }

  userInput(Left, 0);

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      if (Y(i, j) != cell_Y[i][j] - SIZE) {
        difference = YES;
      }
    }
  }

  ck_assert_int_eq(difference, NO);
  destroy_game();
}

START_TEST(userInput_right_test) {
  game_t *g = game();
  init_game();
  int difference = NO;

  int cell_Y[BL_MAX][BL_MAX * SIZE];

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      cell_Y[i][j] = Y(i, j);
    }
  }

  userInput(Right, 0);

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      if (Y(i, j) != cell_Y[i][j] + SIZE) {
        difference = YES;
      }
    }
  }

  ck_assert_int_eq(difference, NO);
  destroy_game();
}

START_TEST(userInput_down_test) {
  game_t *g = game();
  init_game();
  int difference = NO;

  int cell_X[BL_MAX][BL_MAX * SIZE];

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      cell_X[i][j] = X(i, j);
    }
  }

  userInput(Down, 0);

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      if (X(i, j) != cell_X[i][j] + 1) {
        difference = YES;
      }
    }
  }

  ck_assert_int_eq(difference, NO);
  destroy_game();
}

START_TEST(userInput_action_test) {
  game_t *g = game();
  init_game();
  int difference = NO;

  int rotate_blocks[][BL_MAX][BL_MAX] = {
      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
      {{0, 8, 8, 0}, {0, 8, 0, 0}, {0, 8, 0, 0}, {0, 0, 0, 0}},
      {{0, 3, 0, 0}, {0, 3, 0, 0}, {0, 3, 3, 0}, {0, 0, 0, 0}},
      {{0, 0, 2, 0}, {0, 2, 2, 0}, {0, 2, 0, 0}, {0, 0, 0, 0}},
      {{0, 5, 0, 0}, {0, 5, 5, 0}, {0, 0, 5, 0}, {0, 0, 0, 0}},
      {{0, 4, 0, 0}, {0, 4, 4, 0}, {0, 4, 0, 0}, {0, 0, 0, 0}},
      {{0, 6, 6, 0}, {0, 6, 6, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

  userInput(Action, 0);

  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j += 2) {
      if (CELL(i, j) != rotate_blocks[g->current_name][i][j / 2]) {
        difference = YES;
      }
    }
  }

  ck_assert_int_eq(difference, NO);
  destroy_game();
}

START_TEST(userInput_test) {
  game_t *g = game();
  init_game();

  userInput(Terminate, 0);
  ck_assert_int_eq(g->info.pause, Terminate);
  userInput(Pause, 0 );
  ck_assert_int_eq(g->info.pause, Pause);
  userInput(Start, 0);
  ck_assert_int_eq(g->info.pause, 0);

  destroy_game();
}


//  ============================================================================

Suite *fsm_test(void) {
  Suite *tetris = suite_create("\nfsm tests \n");

  TCase *tc_fsm_test = tcase_create("fsm test");
  tcase_add_test(tc_fsm_test, updateCurrentState_test);
  tcase_add_test(tc_fsm_test, userInput_left_test);
  tcase_add_test(tc_fsm_test, userInput_right_test);
  tcase_add_test(tc_fsm_test, userInput_down_test);
  tcase_add_test(tc_fsm_test, userInput_action_test);
  tcase_add_test(tc_fsm_test, userInput_test);
  suite_add_tcase(tetris, tc_fsm_test);

  return tetris;
}