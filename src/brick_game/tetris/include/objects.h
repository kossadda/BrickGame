/**
 * @file objects.h
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef OBJECTS_H
#define OBJECTS_H

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct
{
  int x;
  int y;
} Position;

typedef enum {
  BL_I, BL_L, BL_ML, BL_Z, BL_MZ, BL_T, BL_SQ, BLOCK_CNT
} Block;

typedef struct {
  GameInfo_t info;
  Position cursor;
  Block current;
} Game;


typedef enum {
  EMPTY, FILL
} Filling;

#endif // OBJECTS_H