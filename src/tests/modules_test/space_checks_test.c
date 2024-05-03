/**
 * @file space_checks_test.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Module for test space_checks module functions
 * @version 1.0
 * @date 2024-05-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include_test/space_checks_test.h"

//  ============================================================================

START_TEST(have_space_to_move_right_test) {
  game_t *g = game();
  init_game();

  ck_assert_int_eq(have_space_to_move(g, Right), YES);

  for(int i = 0; i < BL_MAX; i++) {
    for(int j = 0; j < COL; j++) {
      FIELD(i, j) = 1;
    }
  }

  updateCurrentState();

  ck_assert_int_eq(have_space_to_move(g, Right), NO);
}

START_TEST(have_space_to_move_left_test) {
  game_t *g = game();
  init_game();

  ck_assert_int_eq(have_space_to_move(g, Left), YES);

  for(int i = 0; i < BL_MAX; i++) {
    for(int j = 0; j < COL; j++) {
      FIELD(i, j) = 1;
    }
  }
  
  updateCurrentState();

  ck_assert_int_eq(have_space_to_move(g, Left), NO);
}

START_TEST(have_space_to_fall_test) {
  game_t *g = game();
  init_game();

  ck_assert_int_eq(have_down_space(g), YES);

  for(int i = 0; i < BL_MAX; i++) {
    for(int j = 0; j < COL; j++) {
      FIELD(i, j) = 1;
    }
  }
  
  updateCurrentState();

  ck_assert_int_eq(have_down_space(g), NO);
}

START_TEST(have_space_to_rotate_test_1) {
  game_t *g = game();
  init_game();
  while(g->current_name == BL_MAX) {
    destroy_game();
    init_game();
  }

  for(int i = 0; i < BL_MAX; i++) {
    for(int j = 0; j < COL; j++) {
      FIELD(i, j) = 0;
    }
  }
 
  int have_space = have_rotate_space(g, (g->current_name == BL_I) ? BL_MAX : BL_MAX - 1);

  ck_assert_int_eq(have_space, YES);

  for(int i = 0; i < BL_MAX; i++) {
    for(int j = 0; j < COL; j++) {
      FIELD(i, j) = 1;
    }
  }
  
  have_space = have_rotate_space(g, (g->current_name == BL_I) ? BL_MAX : BL_MAX - 1);

  ck_assert_int_eq(have_space, NO);
}

START_TEST(have_space_to_rotate_test_2) {
  game_t *g = game();
  init_game();
  while(g->current_name == BL_SQ) {
    destroy_game();
    init_game();
  }

  for(int i = 0; i < BL_MAX; i++) {
    for(int j = 0; j < COL; j++) {
      X(i, j) += 18;
    }
  }
  
  int have_space = have_rotate_space(g, BL_MAX);

  ck_assert_int_eq(have_space, NO);
}

START_TEST(have_down_space_test) {
  game_t *g = game();
  init_game();
  while(g->current_name == BL_SQ) {
    destroy_game();
    init_game();
  }

  for(int i = 0; i < BL_MAX; i++) {
    for(int j = 0; j < COL; j++) {
      X(i, j) += 18;
    }
  }
  
  int have_space = have_down_space(g);

  ck_assert_int_eq(have_space, NO);
}

//  ============================================================================

Suite *space_checks_test(void) {
  Suite *tetris = suite_create("\nspace_checks tests \n");

  TCase *tc_space_checks_test = tcase_create("space_checks test");
  tcase_add_test(tc_space_checks_test, have_space_to_move_right_test);
  tcase_add_test(tc_space_checks_test, have_space_to_move_left_test);
  tcase_add_test(tc_space_checks_test, have_space_to_fall_test);
  tcase_add_test(tc_space_checks_test, have_space_to_rotate_test_1);
  tcase_add_test(tc_space_checks_test, have_space_to_rotate_test_2);
  tcase_add_test(tc_space_checks_test, have_down_space_test);
  suite_add_tcase(tetris, tc_space_checks_test);

  return tetris;
}