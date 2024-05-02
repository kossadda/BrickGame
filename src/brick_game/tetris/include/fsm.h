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

#include <stdbool.h>

typedef enum {
  Start = 's',
  Pause = 'p',
  Terminate = 'x',
  Down = 258,
  Up = 259,
  Left = 260,
  Right = 261,
  Action = 32,
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  int block_size;
  int cols;
  int rows;
} field_t;

typedef enum {
  EMPTY,
  FILL,
  YES,
  NO,
  GAME_OVER = -Terminate,
  GUIDE = 'g',
  THEME = 't',
  CHANGE_SIZE = 'v',
  CHANGE_BLOCK = 'b'
} common_t;

void userInput(UserAction_t action, bool hold);
void updateCurrentState();
double current_time();
field_t *field();

#define SIZE (field()->block_size)
#define COL (field()->cols)
#define ROW (field()->rows)
#define BL_MAX 4

#define START_SPEED 65.0
#define LEVEL_MAX 10
#define LEVEL_CHANGE 600
#define LEVEL_SPEED 5

#define ONE_LINE 100
#define TWO_LINE 300
#define THREE_LINE 700
#define FOUR_LINE 1500

#define GET_TIME (clock() * 1000 / CLOCKS_PER_SEC)

#endif  // FSM_H