/**
 * @file fsm.c
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/fsm.h"

#include "./../include/shifts.h"

game_t *game() {
  static game_t game;

  return &game;
}

void updateCurrentState() {
  game_t *g = game();
  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      if (CELL(i, j)) {
        FIELD(X(i, j), Y(i, j)) = CELL(i, j);
      }
    }
  }
}

void userInput(UserAction_t action, bool hold) {
  game_t *g = game();
  switch (action) {
    case Terminate:
      g->gi.pause = Terminate;
      break;
    case Pause:
      g->gi.pause = Pause;
      break;
    case Start:
      g->gi.pause = 0;
      break;
    case Right:
    case Left:
      move_block(g, action);
      updateCurrentState();
      break;
    case Down:
      move_down(g);
      updateCurrentState();
      break;
    case Action:
      rotate_block(g);
      updateCurrentState();
      break;
    default:
      if (current_time() >= g->gi.speed) {
        move_down(g);
        updateCurrentState();
      }
  }
  (void)hold;
}

double current_time() {
  static double current = 0.0;
  static bool initialized = 0;
  double temp;

  if (!initialized) {
    current = clock() * 1000 / CLOCKS_PER_SEC;
    initialized = true;
  } else {
    temp = clock() * 1000 / CLOCKS_PER_SEC - current;
    if(temp >= game()->gi.speed) {
      current = clock() * 1000 / CLOCKS_PER_SEC;
    }
  }

  return temp;
}