/**
 * @file fsm.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Contains a declaration of general logical functions for working with
 * the user and the operating algorithm
 * @version 1.0
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _FSM_H_
#define _FSM_H_

#include <stdbool.h>

/// @brief Common enumeration of main buttons assignment
typedef enum {
  Start = 's',      ///< Start game
  Pause = 'p',      ///< Pause game
  Terminate = 'x',  ///< Exit game
  Down = 258,       ///< Move figure down
  Up = 259,         ///< Not used in this game
  Left = 260,       ///< Move figure left
  Right = 261,      ///< Move figure right
  Action = 32,      ///< Rotate figure for 90 degree
} UserAction_t;

/// @brief Common type contains the basic information regarding the field
typedef struct {
  int **field;     ///< Array containing the playing field
  int **next;      ///< Array containing the following figure
  int score;       ///< Current game score
  int high_score;  ///< Record game score
  int level;       ///< Current level
  int speed;       ///< Current speed
  int pause;       ///< Information about the game state (play/pause, etc.)
} GameInfo_t;

/// @brief Additionally. Information about the size of the playing field
typedef struct {
  int block_size;  ///< Width of one cell (default 2)
  int cols;        ///< Number of columns (default 10)
  int rows;        ///< Number of rows (default 20)
} field_t;

/// @brief Auxiliary list. Contains additional buttons or states
typedef enum {
  EMPTY = 0,               ///< Empty cell
  NO = 0,                  ///< For the status of any signals
  YES = 1,                 ///< For the status of any signals
  GAME_OVER = -Terminate,  ///< End of game signal
  GUIDE = 'g',             ///< Button to display key assignments
  THEME = 't',             ///< Button to change color scheme
  CHANGE_SIZE = 'v',       ///< Button to change field size
  CHANGE_BLOCK = 'b'       ///< Button to change cell size
} common_t;

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
double current_time();
field_t *field();

/// @brief Referring to a field with cell dimension
#define SIZE (field()->block_size)

/// @brief Referring to a field with number of columns
#define COL (field()->cols)

/// @brief Referring to a field with number of rows
#define ROW (field()->rows)

/// @brief Maximum width/length of any figure
#define BL_MAX 4

/// @brief Initial speed of standard field
#define START_SPEED 60

/// @brief Maximum possible level
#define LEVEL_MAX 10

/// @brief Number of points to overcome one level
#define LEVEL_CHANGE 600

/// @brief Speed difference with adding one level
#define LEVEL_SPEED 5

/// @brief The number of points for simultaneously filling one line
#define ONE_LINE 100

/// @brief The number of points for simultaneously filling two lines
#define TWO_LINE 300

/// @brief Number of points for simultaneously filling three lines
#define THREE_LINE 700

/// @brief The number of points for simultaneously filling four lines
#define FOUR_LINE 1500

/// @brief Determine the time from the start of program execution
#define GET_TIME (clock() * 1000 / CLOCKS_PER_SEC)

#endif  // _FSM_H_