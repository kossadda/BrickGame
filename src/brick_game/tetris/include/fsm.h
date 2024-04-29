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
  Left = 4,
  Right = 5,
  Up = 3,
  Down = 2,
  Action
} UserAction_t;

#endif  // FSM_H