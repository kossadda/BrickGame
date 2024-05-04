/**
 * @file fsm.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Contains general logical functions for working with the user and the
 * operating algorithm
 * @version 1.0
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/fsm.h"

#include "./../include/shifts.h"

/**
 * @brief Singleton pattern. Declaration of the structure for working with game
 * field size
 *
 * @return game_t* - address of the declared structure
 */
field_t *field() {
  static field_t field = {2, 20, 20};

  return &field;
}

/// @brief Updating field cells relative to a moving figure
GameInfo_t updateCurrentState() {
  game_t *g = game();
  
  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      if (CELL(i, j)) {
        FIELD(X(i, j), Y(i, j)) = CELL(i, j);
      }
    }
  }

  return g->info;
}

/**
 * @brief Handling user input
 *
 * @param[in] action pressed key
 * @param hold clamp information (not used in this game)
 */
void userInput(UserAction_t action, bool hold) {
  game_t *g = game();

  switch (action) {
    case Terminate:
      g->info.pause = Terminate;
      break;
    case Pause:
      g->info.pause = Pause;
      break;
    case Start:
      g->info.pause = 0;
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
      if (current_time() >= g->info.speed) {
        move_down(g);
        updateCurrentState();
      }
  }

  (void)hold;
}

/**
 * @brief Function for determining the time interval between iterations of a
 * moving block falling
 *
 * @return double - difference in time
 */
double current_time() {
  static double current = 0.0;
  static bool initialized = 0;
  double temp = 0.0;

  if (!initialized) {
    current = GET_TIME;
    initialized = true;
  } else {
    temp = GET_TIME - current;
    if (temp >= game()->info.speed) {
      current = GET_TIME;
    }
  }

  return temp;
}