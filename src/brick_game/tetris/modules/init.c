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

void init_game() {
  game_t *g = game();
  srand(time(NULL));

  g->gi.field = (int **)calloc(ROW, sizeof(int *));
  for (int i = 0; i < ROW; i++) {
    g->gi.field[i] = (int *)calloc(COL, sizeof(int));
  }

  g->gi.next = (int **)calloc(BL_MAX, sizeof(int *));
  g->bl = (block_t **)calloc(BL_MAX, sizeof(block_t *));
  for (int i = 0; i < BL_MAX; i++) {
    g->gi.next[i] = (int *)calloc(BL_MAX * SIZE, sizeof(int));
    g->bl[i] = (block_t *)calloc(BL_MAX * SIZE, sizeof(block_t));
  }

  set_high_score(&g->gi);
  g->gi.score = 0;
  g->gi.level = 1;
  g->gi.speed = START_SPEED;
  g->gi.pause = -Pause;
  g->theme = BLACK;

  fill_next_block(g);
  spawn_block(g);
}

void set_high_score(GameInfo_t *gi) {
  char path_score[255];
  get_txt_file_path(path_score);

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

void get_txt_file_path(char *path_score) {
  char *filename = "score.txt";
  char path[strlen(__FILE__) + 1];
  strcpy(path, __FILE__);
  char *last_slash_ptr = strrchr(path, '/');
  *(++last_slash_ptr) = '\0';
  sprintf(path_score, "%s%s", path, filename);
}