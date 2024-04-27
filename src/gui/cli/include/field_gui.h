/**
 * @file field.h
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef FIELD_H
#define FIELD_H

#include <ncurses.h>

#define ROWS 20
#define COLS 10 * BLOCK_SIZE
#define BLOCK_SIZE 3

void init_screen();
void print_field();

#endif // FIELD_H