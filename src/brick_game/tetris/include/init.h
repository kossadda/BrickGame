/**
 * @file init.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header with init.c module function declarations
 * @version 1.0
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef INIT_H
#define INIT_H

#include "./objects.h"

void init_game();
void set_high_score(GameInfo_t *info);
void get_txt_file_path(char *path_score);
void destroy_game();

#endif  // INIT_H
