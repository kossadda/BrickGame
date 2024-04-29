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

#endif  // FSM_H