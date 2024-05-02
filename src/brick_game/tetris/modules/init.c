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

game_t *game() {
  static game_t game;

  return &game;
}

void init_game() {
  game_t *g = game();
  srand(time(NULL));

  g->info.field = (int **)calloc(ROW, sizeof(int *));
  for (int i = 0; i < ROW; i++) {
    g->info.field[i] = (int *)calloc(COL, sizeof(int));
  }

  g->info.next = (int **)calloc(BL_MAX, sizeof(int *));
  g->block = (block_t **)calloc(BL_MAX, sizeof(block_t *));
  for (int i = 0; i < BL_MAX; i++) {
    g->info.next[i] = (int *)calloc(BL_MAX * SIZE, sizeof(int));
    g->block[i] = (block_t *)calloc(BL_MAX * SIZE, sizeof(block_t));
  }

  set_high_score(&g->info);
  g->info.score = 0;
  g->info.level = 1;
  g->info.speed = START_SPEED;
  g->info.pause = -Pause;
  g->theme = BLACK;

  fill_next_block(g);
  spawn_block(g);
}

static void free_double_ptr(void ***matrix, int size) {
  for (int i = 0; i < size; i++) {
    if ((*matrix)[i]) {
      free((*matrix)[i]);
      (*matrix)[i] = NULL;
    }
  }

  free(*matrix);
}

void destroy_game() {
  game_t *g = game();

  if (g->info.field) {
    free_double_ptr((void ***)&g->info.field, field()->rows);
  }
  if (g->info.next) {
    free_double_ptr((void ***)&g->info.next, BL_MAX);
  }
  if (g->block) {
    free_double_ptr((void ***)&g->block, BL_MAX);
  }
}

void set_high_score(GameInfo_t *info) {
  char path_score[255];
  get_txt_file_path(path_score);

  FILE *f_score = fopen(path_score, "rw");
  char str_score[15];

  if (fgets(str_score, 15, f_score)) {
    info->high_score = atoi(str_score);
  } else {
    info->high_score = 0;
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