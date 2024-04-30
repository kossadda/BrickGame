/**
 * @file fsm.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef FSM_H
#define FSM_H

#include "./objects.h"

typedef enum {
  Start = 'e',
  Pause = 't',
  Terminate = 'q',
  Down = 258,
  Up = 259,
  Left = 260,
  Right = 261,
  Action = 32
} UserAction_t;

typedef enum { EMPTY, FILL, YES, NO } common_t;

#define SIZE 2
#define BL_MAX 4
#define COL 10 * SIZE
#define ROW 20

#define LEVEL_MAX 10
#define LEVEL_CHANGE 600
#define LEVEL_SPEED 5

#define ONE_LINE 100
#define TWO_LINE 300
#define THREE_LINE 700
#define FOUR_LINE 1500

void user_input(UserAction_t action, game_t *g, double *lut, bool hold);
void update_current_state(game_t *game);
double current_time();

#endif  // FSM_H