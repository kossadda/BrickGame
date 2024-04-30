/**
 * @file init.c
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/init.h"

#include <time.h>

#include "./../include/blocks.h"

void init_game(game_t *game) {
  srand(time(NULL));

  game->gi.field = (int **)calloc(ROW, sizeof(int *));
  for (int i = 0; i < ROW; i++) {
    game->gi.field[i] = (int *)calloc(COL, sizeof(int));
  }

  game->gi.next = (int **)calloc(BL_MAX, sizeof(int *));
  game->bl = (block_t **)calloc(BL_MAX, sizeof(block_t *));
  for (int i = 0; i < BL_MAX; i++) {
    game->gi.next[i] = (int *)calloc(BL_MAX * SIZE, sizeof(int));
    game->bl[i] = (block_t *)calloc(BL_MAX * SIZE, sizeof(block_t));
  }

  set_high_score(&game->gi);
  game->gi.score = 0;
  game->gi.level = 1;
  game->gi.speed = START_SPEED;
  game->gi.pause = 0;

  fill_next_block(game);
  spawn_block(game);
}

void set_high_score(game_info_t *gi) {
  char *filename = "score.txt";
  char path[strlen(__FILE__) + 1];
  strcpy(path, __FILE__);
  char *last_slash_ptr = strrchr(path, '/');
  *(++last_slash_ptr) = '\0';
  char path_score[strlen(path) + strlen(filename) + 1];
  sprintf(path_score, "%s%s", path, filename);

  FILE *f_score = fopen(path_score, "rw");
  char str_score[15];

  if (fgets(str_score, 15, f_score)) {
    gi->high_score = atoi(str_score);
  } else {
    gi->high_score = 0;
  }

  if (f_score) {
    fclose(f_score);
  }
}